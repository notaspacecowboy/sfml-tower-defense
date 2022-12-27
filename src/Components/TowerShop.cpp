//
// Created by Zheng Yang on 25/11/22.
//

#include <Components.h>
#include <Prefabs.h>
#include <Grids.h>
#include <Input/InputManager.h>
#include <Utils/Logger.h>
#include <Utils/TransformUtility.h>
#include <Data.h>
#include <Core/GameManager.h>

using namespace game::prefabs;
using namespace game::grid;
using namespace game::input;
using namespace game::utils;
using namespace game::data;
using namespace game::core;

namespace game::components {
    const std::string TOWER_OFFSET_X          = "TowerOffsetX";
    const std::string TOWER_OFFSET_Y          = "TowerOffsetY";

    TowerShop::TowerShop(game::components::GameObject &owner, grid::GridSystem *system, sf::RenderWindow *renderWindow,
                         sf::View *gameCamera)
    : Component(owner)
    , mGridSystem(system)
    , mSelectedGrid(nullptr)
    , mSelectedTowerShopGO(nullptr)
    , mGameWindow(renderWindow)
    , mGameView(gameCamera)
    , mGameLevel(nullptr){
    }

    void TowerShop::tick(float deltaTime) {
        auto& pointerData = InputManager::getInstance().getCachedPointerData();
        if(!pointerData.pressedThisFrame || pointerData.pointerPressed)
            return;

        auto mousePos = sf::Mouse::getPosition(*mGameWindow);
        auto mousePosInWorld = TransformUtility::mapScreenPointToWorldPos(*mGameWindow, *mGameView, mousePos);

        auto gridLayer = mGridSystem->getGridLayerByID(grid::SLOTS);
        auto grid = gridLayer->getGridByWorldPosition(mousePosInWorld);

        if(grid == nullptr || grid->getEntityCounts() > 0) {
            if(mSelectedTowerShopGO != nullptr) {
                mSelectedTowerShopGO->setState(components::GameObject::GoState::MARK_TO_DESTROY);
                mSelectedTowerShopGO = nullptr;
            }

            mSelectedGrid = nullptr;
            return;
        }

        if(mSelectedTowerShopGO != nullptr) {
            mSelectedTowerShopGO->setState(components::GameObject::GoState::MARK_TO_DESTROY);
            mSelectedTowerShopGO = nullptr;
        }

        if(grid == mSelectedGrid) {
            BuyTower(DataManager::getInstance().get<TowerDefine>(data::DataType::TOWER, 1), grid);

            mSelectedGrid = nullptr;
            return;
        }

        mSelectedGrid = grid;
        TowerShopItemPrefab prefab;
        mSelectedTowerShopGO = prefab.getGoHandle().get();
        auto transform = mSelectedTowerShopGO->getTransform();
        transform->setParent(grid->getRoot()->getTransform());
        transform->setPivot(components::PIVOT_CENTER);
        transform->setAnchor(components::ANCHOR_CENTER);
        transform->setLocalPosition(0, 0);
    }


    void TowerShop::BuyTower(data::TowerDefine *define, grid::Grid *grid) {
        auto playerState = GameManager::getInstance().getPlayerState();
        if(playerState->getCurrentPoint() < define->cost)
            return;

        playerState->changePoint(-define->cost);

        auto go = GameManager::getInstance().instantiateGameObject().get();
        auto transform = go->getTransform();
        transform->setParent(grid->getRoot().get()->getTransform());
        transform->setPivot(PIVOT_BOT_MIDDLE);
        transform->setAnchor(ANCHOR_CENTER);

        int towerOffsetX = mGameLevel->getField<int>(TOWER_OFFSET_X).value();
        int towerOffsetY = mGameLevel->getField<int>(TOWER_OFFSET_Y).value();

        transform->setLocalPosition(towerOffsetX, towerOffsetY);
        transform->setScale(define->textureScaleX, define->textureScaleY);
        auto tower = go->addComponent<Tower>(*define,
                                             *mGridSystem->getGridLayerByID(grid::SLOTS),
                                             *mGridSystem->getGridLayerByID(grid::PATH));

        auto index = grid->getIndex();
        tower->setGridIndex(index.x, index.y);
        tower->spawn();
    }

    void TowerShop::loadLevel(const ldtk::Level *level) {
        mGameLevel = level;
    }
}
