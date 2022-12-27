//
// Created by Zheng Yang on 20/10/22.
//

#include <Utils/Logger.h>
#include <Core/GameManager.h>
#include <Resource/ResourceManager.h>
#include <boost/bind/bind.hpp>
#include <functional>
#include <Resource/Localization.h>
#include <Input/InputManager.h>
#include <Audio.h>
#include <States.h>
#include <Components.h>
#include <Data.h>
#include <Grid/GridSystem.h>

using namespace game::core;
using namespace game::renderer;
using namespace game::components;
using namespace game::data;
using namespace game::resource;
using namespace game::input;
using namespace boost::placeholders;
using namespace game::audio;

namespace game::states {
    StartState::StartState(StateMachine *owner): State(owner) {
        utils::Logger::log("Start State pushed", 5);
    }

    StartState::~StartState() noexcept {
        utils::Logger::log("Start State Poped", 5);
        mFadeInListener.disconnect();
        mLoadingTaskListener.disconnect();
        mKeyPressedListener.disconnect();
        mGoToMainStateListener.disconnect();
        mMousePressedListener.disconnect();
    }

    void StartState::init() {
        loadImmediateResources();

        mOwner->push<LoadingState>();

        auto task = GameManager::getInstance().registerAsyncTask(std::bind(&StartState::loadAllResources, this));
        mLoadingTaskListener = task->onTaskCompleted.connect(boost::bind(&StartState::onLoadingComplete, this));
        task->execute();
    }


    void StartState::loadImmediateResources() {
        registerResources();
        TextureManager::getInstance().load(TEXTURE_LOADING_SPIN);
    }


    void StartState::loadAllResources() {
        DataManager::getInstance().loadData();
        Localization::getInstance().loadMasterText();

        TextureManager      ::getInstance().loadAll();
        FontManager         ::getInstance().loadAll();
        SoundBufferManager  ::getInstance().loadAll();

        DataManager::getInstance().loadPlayerFromIndex(DataManager::getInstance().getCurrentPlayerIndex());

        sleep(2);
    }

    void StartState::onBackgroundFadeInCompleted() {
    }

    void StartState::onLoadingComplete() {
        mOwner->pop();

        GameManager::getInstance().getRenderer().showFPS();
        //test background
        auto backgroundGO = instantiateGO(components::ANCHOR_CENTER, PIVOT_CENTER);
        backgroundGO->getTransform()->matchParent();
        mBackgroundSprite = backgroundGO->addComponent<Sprite>(UI, 0);
        mBackgroundSprite->setTexture(TextureManager::getInstance().getByID(TEXTURE_BG_START));
        mBackgroundSprite->setAlpha(0);
        auto fadeInAnimator = backgroundGO->addComponent<FadeInOutAnimator>(0, 1, 1, false, false);
        fadeInAnimator->addTarget(mBackgroundSprite);
        fadeInAnimator->start();
        fadeInAnimator->onAnimationComplete.connect(boost::bind(&StartState::onBackgroundFadeInCompleted, this));

        //test text
        auto pressKeyGO = instantiateGO(ANCHOR_CENTER, PIVOT_CENTER);
        mPressKeyText = pressKeyGO->addComponent<Text>(UI, 2);
        mPressKeyText->setFont(FontManager::getInstance().getByID(FONT_GUI_1));
        mPressKeyText->setTextSize(50);
        mPressKeyText->setText(Localization::getInstance().get("PRESS_KEY_PROMOTION"), true);
        pressKeyGO->getTransform()->move(0, 100);
        auto textAnimator = pressKeyGO->addComponent<FadeInOutAnimator>(0, 1, 1, true, true);
        textAnimator->addTarget(mPressKeyText);

        mKeyPressedListener = InputManager::getInstance().GameKeyPressedEvent.connect(boost::bind(&StartState::onAnyKeyPressed, this, _1));
        mMousePressedListener = InputManager::getInstance().GameMousePressedEvent.connect(boost::bind(&StartState::onMousePressed, this));

        MusicManager::getInstance().play(MusicType::MUSIC_START);
        MusicManager::getInstance().setVolumn(100);
    }

    void StartState::onAnyKeyPressed(sf::Keyboard::Key keyCode) {
        onMousePressed();
    }

    void StartState::onMousePressed() {
        utils::Logger::log("Key Pressed, move to main state", 5);

        MusicManager::getInstance().stop();

        mKeyPressedListener.disconnect();
        mMousePressedListener.disconnect();

        mBackgroundSprite->getGameObject().removeComponent<FadeInOutAnimator>();
        mPressKeyText->getGameObject().removeComponent<FadeInOutAnimator>();

        auto animator = mBackgroundSprite->getGameObject().addComponent<FadeInOutAnimator>(1, 0, 1, false, false);
        animator->addTarget(mBackgroundSprite);
        animator->addTarget(mPressKeyText);
        mGoToMainStateListener = animator->onAnimationComplete.connect(boost::bind(&StartState::gotoMainState, this));
        animator->start();
    }

    void StartState::gotoMainState() {
        mOwner->pop();
        mOwner->push<MainState>();
    }





























    //register resources
    void StartState::registerResources() {
        auto &textureManager = TextureManager::getInstance();
        textureManager.registerResource("TEXTURE_LOADING_SPIN"              , TEXTURE_LOADING_SPIN              , "./assets/textures/GUI/LoadingSpinner_bootstrap.png");
        textureManager.registerResource("TEXTURE_BUTTON_FRAME_1"            , TEXTURE_BUTTON_FRAME_1            , "./assets/textures/GUI/button_1.png");
        textureManager.registerResource("TEXTURE_BUTTON_FRAME_2"            , TEXTURE_BUTTON_FRAME_2            , "./assets/textures/GUI/button_2.png");
        textureManager.registerResource("TEXTURE_BUTTON_FRAME_3"            , TEXTURE_BUTTON_FRAME_3            , "./assets/textures/GUI/button_3.png");
        textureManager.registerResource("TEXTURE_BG_START"                  , TEXTURE_BG_START                  , "./assets/textures/Background/bg_1.jpg");
        textureManager.registerResource("TEXTURE_BG_MAIN"                   , TEXTURE_BG_MAIN                   , "./assets/textures/Background/bg_2.png");
        textureManager.registerResource("TEXTURE_ENEMY_1_IDLE"              , TEXTURE_ENEMY_1_IDLE              , "./assets/textures/Entity/hell-hound-idle.png");
        textureManager.registerResource("TEXTURE_ENEMY_1_RUN"               , TEXTURE_ENEMY_1_RUN               , "./assets/textures/Entity/hell-hound-run.png");
        textureManager.registerResource("TEXTURE_ENEMY_1_WALK"              , TEXTURE_ENEMY_1_WALK              , "./assets/textures/Entity/hell-hound-walk.png");
        textureManager.registerResource("TEXTURE_TOWER_1_IDLE"              , TEXTURE_TOWER_1_IDLE              , "./assets/textures/Entity/RedMoonTower_free_idle_animation.png");
        textureManager.registerResource("TEXTURE_SKELETON_DEAD"             , TEXTURE_SKELETON_DEAD             , "./assets/textures/Entity/Skeleton Dead.png");
        textureManager.registerResource("TEXTURE_SKELETON_WALK"             , TEXTURE_SKELETON_WALK             , "./assets/textures/Entity/Skeleton Walk.png");
        textureManager.registerResource("TEXTURE_ICON_ARROW"                , TEXTURE_ICON_ARROW                , "./assets/textures/ShopIcon/icon_itemicon_arrow.png");
        textureManager.registerResource("TEXTURE_ICON_ARROWS"               , TEXTURE_ICON_ARROWS               , "./assets/textures/ShopIcon/icon_itemicon_arrows.png");
        textureManager.registerResource("TEXTURE_ICON_AX"                   , TEXTURE_ICON_AX                   , "./assets/textures/ShopIcon/icon_itemicon_ax.png");
        textureManager.registerResource("TEXTURE_ICON_BATTLE"               , TEXTURE_ICON_BATTLE               , "./assets/textures/ShopIcon/icon_itemicon_battle.png");
        textureManager.registerResource("TEXTURE_ICON_BOMB"                 , TEXTURE_ICON_BOMB                 , "./assets/textures/ShopIcon/icon_itemicon_bomb.png");
        textureManager.registerResource("TEXTURE_ICON_BOOK_MAGIC"           , TEXTURE_ICON_BOOK_MAGIC           , "./assets/textures/ShopIcon/icon_itemicon_book_magic.png");
        textureManager.registerResource("TEXTURE_ICON_BOOK_OPEN"            , TEXTURE_ICON_BOOK_OPEN            , "./assets/textures/ShopIcon/icon_itemicon_book_open.png");
        textureManager.registerResource("TEXTURE_ICON_BOOK_SKILL"           , TEXTURE_ICON_BOOK_SKILL           , "./assets/textures/ShopIcon/icon_itemicon_book_skill.png");
        textureManager.registerResource("TEXTURE_ICON_ARMOR"                , TEXTURE_ICON_ARMOR                , "./assets/textures/ShopIcon/icon_itemicon_armor.png");
        textureManager.registerResource("TEXTURE_ITEM_FRAME_1"              , TEXTURE_ITEM_FRAME_1              , "./assets/textures/GUI/frame_itemframe_00_n_gold.png");
        textureManager.registerResource("TEXTURE_ITEM_FRAME_2"              , TEXTURE_ITEM_FRAME_2              , "./assets/textures/GUI/frame_itemframe_00_s2.png");
        textureManager.registerResource("TEXTURE_TILESET_1"                 , TEXTURE_TILESET_1                 , "./assets/textures/tilesets/tile1.png");
        textureManager.registerResource("TEXTURE_ICON_POTION_RED"           , TEXTURE_ICON_POTION_RED           , "./assets/textures/GUI/icon_itemicon_potionred.png");
        textureManager.registerResource("TEXTURE_ICON_STOPWATCH"            , TEXTURE_ICON_STOPWATCH            , "./assets/textures/GUI/icon_itemicon_stopwatch.png");
        textureManager.registerResource("TEXTURE_ICON_POUCH"                , TEXTURE_ICON_POUCH                , "./assets/textures/GUI/icon_itemicon_pouch.png");
        textureManager.registerResource("TEXTURE_BUTTON_FRAME_RED"          , TEXTURE_BUTTON_FRAME_RED          , "./assets/textures/GUI/btn_circle_01_red.png");
        textureManager.registerResource("TEXTURE_ICON_HOME"                 , TEXTURE_ICON_HOME                 , "./assets/textures/GUI/btn_icon_home_3.png");
        textureManager.registerResource("TEXTURE_ICON_POINT"                , TEXTURE_ICON_POINT                , "./assets/textures/GUI/icon_itemicon_hammer.png");
        textureManager.registerResource("TEXTURE_TELEVISION"                , TEXTURE_TELEVISION                , "./assets/textures/GUI/group_image_tv1.png");
        textureManager.registerResource("TEXTURE_ICON_SHEET"                , TEXTURE_ICON_SHEET                , "./assets/textures/GUI/icon_sheet.png");
        textureManager.registerResource("TEXTURE_PROJECTION_1"              , TEXTURE_PROJECTION_1              , "./assets/textures/Projections/projection_1.png");
        textureManager.registerResource("TEXTURE_TILESET_2"                 , TEXTURE_TILESET_2                 , "./assets/textures/tilesets/tile2.png");
        textureManager.registerResource("TEXTURE_TILESET_3"                 , TEXTURE_TILESET_3                 , "./assets/textures/tilesets/tile3.png");
        textureManager.registerResource("TEXTURE_TILESET_4"                 , TEXTURE_TILESET_4                 , "./assets/textures/tilesets/tile4.png");

        auto &fontManager = FontManager::getInstance();
        fontManager.registerResource("FONT_GUI_1"                           , FONT_GUI_1                        , "./assets/fonts/m3x6.ttf");
        fontManager.registerResource("FONT_GUI_2"                           , FONT_GUI_2                        , "./assets/fonts/Toriko.ttf");

        auto &soundManager = SoundBufferManager::getInstance();
        soundManager.registerResource("SOUND_BUTTON_CLICK_1"                , SOUND_BUTTON_CLICK_1              , "./assets/sound/GenericButton8.wav");

        auto &musicManager = MusicManager::getInstance();
        musicManager.registerMusic(MusicType::MUSIC_START                   , "./assets/music/start.ogg");
        musicManager.registerMusic(MusicType::MUSIC_MAIN                    , "./assets/music/main.ogg");
        musicManager.registerMusic(MusicType::MUSIC_BATTLE                  , "./assets/music/battle.ogg");
    }
}
