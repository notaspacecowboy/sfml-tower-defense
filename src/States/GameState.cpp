//
// Created by Zheng Yang on 13/11/22.
//

#include <States.h>
#include <Core/GameManager.h>
#include <boost/bind/bind.hpp>
#include <functional>
#include <Utils/Logger.h>
#include <Utils/Time.h>
#include <Utils/TransformUtility.h>
#include <Input/InputManager.h>
#include <Renderer/RenderLayer.h>
#include <Data.h>
#include <math.h>
#include <Audio.h>
#include <Components.h>
#include <Prefabs.h>
#include <Resource/ResourceManager.h>
#include <Grids.h>

using namespace game::core;
using namespace game::utils;
using namespace boost::placeholders;
using namespace game::input;
using namespace game::data;
using namespace game::renderer;
using namespace game::components;
using namespace game::grid;
using namespace game::prefabs;
using namespace game::resource;
using namespace game::audio;
using namespace game::grid;

namespace game::states {
    float GameState::scrollSpeed = 5.f;
    float GameState::cameraMoveSpeed = 60.f;
    const std::string MAP_HP_FIELD          = "PlayerInitialHP";
    const std::string MAP_POINT_FIELD       = "PlayerInitialPoint";

    GameState::GameState(game::states::StateMachine *owner)
    : State(owner)
    , mGameWorld(DataManager::getInstance().getGridProject().getWorld())
    , mEnemyCount(0) {
        utils::Logger::log("Game State Pushed", 5);

        mGameCamera = GameManager::getInstance().getGameCamera();
        auto resolution = GameManager::getInstance().getRenderer().ReferencedResolution;
        mGameCamera->setSize(resolution.x, resolution.y);

        mGameRoot = GameManager::getInstance().instantiateGameObject();
        mGridSystem = std::make_unique<GridSystem>();
        mEnemySpawner = mGameRoot->addComponent<EnemySpawner>(mGridSystem.get());
        mEnemySpawner->onEnemySpawned.connect(boost::bind(&GameState::onEnemySpawned, this, _1));
        mEnemySpawner->onAllEnemiesSpawned.connect(boost::bind(&GameState::onAllEnemiesSpawned, this));

        mTowerShop = mGameRoot->addComponent<TowerShop>(mGridSystem.get(), GameManager::getInstance().getGameWindow(), mGameCamera);
    }

    GameState::~GameState() noexcept {
        utils::Logger::log("Game State Poped", 5);

        mLoadingTaskListener.disconnect();
        mWheelScrolledListener.disconnect();
        mMouseDragListener.disconnect();
        if(mGameRoot)
            mGameRoot->setState(components::GameObject::GoState::MARK_TO_DESTROY);
    }

    void GameState::init() {
        mOwner->push<LoadingState>();

        auto task = GameManager::getInstance().registerAsyncTask(std::bind(&GameState::loadGameWord, this));
        mLoadingTaskListener = task->onTaskCompleted.connect(boost::bind(&GameState::onMapLoadCompleted, this));
        task->execute();
    }

    void GameState::loadGameWord() {
        mGridSystem->registerLayer(grid::Layer::BACKGROUND , "Background" , RenderLayer::BACKGROUND, 0, true);
        mGridSystem->registerLayer(grid::Layer::PATH       , "Path"       , RenderLayer::BACKGROUND, 1, false);
        mGridSystem->registerLayer(grid::Layer::SLOTS      , "Slots"      , RenderLayer::BACKGROUND, 2, false);
        mGridSystem->registerLayer(grid::Layer::DECORATIONS, "Decorations", RenderLayer::ENTITY    , 0, false);

        int levelNumber = GameManager::getInstance().getPlayerState()->getGameLevel();
        std::string levelName = "Level_" + std::to_string(levelNumber);
        const auto& level = mGameWorld.getLevel(levelName);
        mGridSystem->loadLevel(&level);
        mEnemySpawner->loadLevel(&level);
        mTowerShop->loadLevel(&level);

        int initialHP = level.getField<int>(MAP_HP_FIELD).value();
        int initialPoint = level.getField<int>(MAP_POINT_FIELD).value();
        GameManager::getInstance().getPlayerState()->setHP(initialHP);
        GameManager::getInstance().getPlayerState()->setPoint(initialPoint);

        const auto worldSize = mGridSystem->getWorldSize();
        mGameRoot->getTransform()->setSize(worldSize.x, worldSize.y);

        //spawn button
        GameObject* go = GameManager::getInstance().instantiateGameObject().get();
        Transform* transform = go->getTransform();
        transform->setParent(mRoot->getTransform());
        transform->setAnchor(components::ANCHOR_TOP_MIDDLE);
        transform->setPivot(components::PIVOT_TOP_MIDDLE);
        transform->setLocalPosition(0, 20);
        mEnemySpawnButton = go->addComponent<Button>(DataManager::getInstance().get<ButtonDefine>(data::DataType::BUTTON, 2), UI, 1);
        mEnemySpawnButton->getText()->setText("START", true);
        mSpawnButtonClickListener = mEnemySpawnButton->onClick.connect(boost::bind(&GameState::onSpawnButtonClicked, this));
        mEnemySpawnButton->getGameObject().setState(components::GameObject::GoState::DISABLED);


        //pause button
        go = instantiateGO(ANCHOR_TOP_RIGHT, PIVOT_TOP_RIGHT);
        transform = go->getTransform();
        transform->setLocalPosition(-40, 40);
        transform->setScale(0.5, 0.5);
        auto sprite = go->addComponent<Sprite>(UI, 0);
        sprite->setTexture(TEXTURE_BUTTON_FRAME_RED);
        sprite->setSpriteNativeSize();

        auto iconGO = GameManager::getInstance().instantiateGameObject().get();
        transform = iconGO->getTransform();
        transform->setParent(go->getTransform());
        transform->setPivot(components::PIVOT_CENTER);
        transform->setAnchor(components::ANCHOR_CENTER);
        transform->setLocalPosition(0, 0);
        transform->setScale(0.5, 0.5);
        sprite = iconGO->addComponent<Sprite>(UI, 1);
        sprite->setTexture(TEXTURE_ICON_HOME);
        sprite->setSpriteNativeSize();
        mPauseButton = go->addComponent<SimpleButton>();
        mPauseButtonClickListener = mPauseButton->onClick.connect(boost::bind(&GameState::onPauseButtonClicked, this));
        mPauseButton->getGameObject().setState(components::GameObject::GoState::DISABLED);

        go = GameManager::getInstance().instantiateGameObject(components::GameObject::GoState::DISABLED).get();
        transform = go->getTransform();
        transform->setParent(mGameRoot->getTransform());

        mEnemyCount = 0;

        sleep(2);
    }

    void GameState::onMapLoadCompleted() {
        adjustGameCamera();

        PlayerHudPrefab prefab;
        auto go = prefab.getGoHandle().get();
        go->getTransform()->setParent(mRoot->getTransform());
        mPlayerHud = go->addComponent<PlayerHud>(prefab);

        mGridSystem->setActive(true);
        mOwner->pop();

        //mWheelScrolledListener = InputManager::getInstance().GameWheelScrolledEvent.connect(boost::bind(&GameState::onWheelScrolled, this, _1));
        mMouseDragListener = InputManager::getInstance().GameMouseDragEvent.connect(boost::bind(&GameState::onMouseDrag, this, _1, _2));

        mEnemySpawnButton->getSprite()->setColor(sf::Color::White);
        mEnemySpawnButton->getText()->setColor(sf::Color::White);
        mEnemySpawnButton->getText()->setText(std::to_string(mEnemySpawner->getCurrentFightIndex() + 1) +
                                              "/" +
                                              std::to_string(mEnemySpawner->getTotalFights()), true);
        mEnemySpawnButton->getGameObject().setState(components::GameObject::GoState::ACTIVE);
        mEnemySpawnButton->setRaycastable(true);

        mPauseButton->getGameObject().setState(components::GameObject::GoState::ACTIVE);
        mPauseButton->setRaycastable(true);

        mTowerShop->getGameObject().setState(components::GameObject::GoState::ACTIVE);
        MusicManager::getInstance().play(MusicType::MUSIC_BATTLE);
    }

    void GameState::onSpawnButtonClicked() {
        mEnemySpawnButton->getSprite()->setColor(sf::Color(128, 128, 128, 255));
        mEnemySpawnButton->getText()->setColor(sf::Color(128, 128, 128, 255));
        mEnemySpawnButton->setRaycastable(false);

        mEnemySpawner->Spawn();
    }

    void GameState::onPauseButtonClicked() {
        MusicManager::getInstance().stop();
        disableInput();
        mOwner->push<PauseState>();
    }

    void GameState::adjustGameCamera() {
        auto worldSize = mGridSystem->getWorldSize();
        mGameCamera->setCenter(worldSize.x / 2, worldSize.y / 2);

        auto cameraSize = mGameCamera->getSize();
        float defaultZoom = fmin(worldSize.x / cameraSize.x, worldSize.y / cameraSize.y);
        mGameCamera->zoom(defaultZoom);
    }

    void GameState::onWheelScrolled(int delta) {
        float factor = 1 - (delta * scrollSpeed * Time::getDeltaTime());

        auto size = mGameCamera->getSize();
        size.x = floor(size.x * factor);
        size.y = floor(size.y * factor);

        auto center = mGameCamera->getCenter();
        auto worldSize = mGridSystem->getWorldSize();

        if(center.x - size.x / 2 < 0 || center.x + size.x / 2 > worldSize.x || center.y - size.y / 2 < 0 || center.y + size.y / 2 > worldSize.y)
            return;

        mGameCamera->setSize(size);
    }

    void GameState::onMouseDrag(int deltaX, int deltaY) {
        deltaX *= cameraMoveSpeed * Time::getDeltaTime() * -1;
        deltaY *= cameraMoveSpeed * Time::getDeltaTime() * -1;


        auto center = mGameCamera->getCenter();
        auto cameraSize = mGameCamera->getSize();
        auto worldSize = mGridSystem->getWorldSize();
        sf::Vector2f minCenter(cameraSize.x / 2, cameraSize.y / 2);
        sf::Vector2f maxCenter(worldSize.x - cameraSize.x / 2, worldSize.y - cameraSize.y / 2);
        center.x += deltaX;
        center.y += deltaY;

        if(center.x < minCenter.x)
            center.x = minCenter.x;
        else if(center.x > maxCenter.x)
            center.x = maxCenter.x;

        if(center.y < minCenter.y)
            center.y = minCenter.y;
        else if(center.y > maxCenter.y)
            center.y = maxCenter.y;

        mGameCamera->setCenter(center);
    }

    void GameState::onEnemySpawned(components::Enemy *enemy) {
        mEnemyCount++;

        enemy->onEnemyDead.connect(boost::bind(&GameState::onEnemyDead, this, _1));
        enemy->onEnemyArriveDestination.connect(boost::bind(&GameState::onEnemyArriveDestination, this, _1));
    }

    void GameState::onAllEnemiesSpawned() {
        Logger::log("all enemy spawned!", 5);

        if(mEnemySpawner->getCurrentFightIndex() >= mEnemySpawner->getTotalFights())
            return;


        mEnemySpawnButton->getSprite()->setColor(sf::Color::White);
        mEnemySpawnButton->getText()->setColor(sf::Color::White);
        mEnemySpawnButton->getText()->setText(std::to_string(mEnemySpawner->getCurrentFightIndex() + 1) +
                                              "/" +
                                              std::to_string(mEnemySpawner->getTotalFights()), true);
        mEnemySpawnButton->setRaycastable(true);
    }

    void GameState::onEnemyDead(const data::EnemyDefine* enemy) {
        mEnemyCount--;
        if(mEnemyCount <= 0 && mEnemySpawner->getCurrentFightIndex() >= mEnemySpawner->getTotalFights()) {
            winGame();
            return;
        }

        auto playerState = GameManager::getInstance().getPlayerState();
        playerState->changePoint(enemy->point);
    }

    void GameState::onEnemyArriveDestination(const data::EnemyDefine* enemy) {
        mEnemyCount--;
        auto playerState = GameManager::getInstance().getPlayerState();
        playerState->damage(enemy->damage);

        if(playerState->getCurrentHP() <= 0) {
            loseGame();
        }
        else if(mEnemyCount <= 0) {
            winGame();
        }
    }

    void GameState::disableInput() {
        mKeyPressedListener.disconnect();
        mMouseDragListener.disconnect();
        mWheelScrolledListener.disconnect();
    }


    void GameState::enableInput() {
        mMouseDragListener = InputManager::getInstance().GameMouseDragEvent.connect(boost::bind(&GameState::onMouseDrag, this, _1, _2));
    }


    void GameState::loseGame() {
        MusicManager::getInstance().stop();
        disableInput();
        mOwner->push<GameOverState>();
    }

    void GameState::winGame() {
        MusicManager::getInstance().stop();
        disableInput();

        auto playerState = GameManager::getInstance().getPlayerState();
        int currentLevel = playerState->getGameLevel() + 1;
        if(mGameWorld.allLevels().size() <= currentLevel)
            mOwner->push<GameCompletedState>();
        else {
            playerState->setGameLevel(currentLevel);
            mOwner->push<GameWinState>();
        }
    }
}
