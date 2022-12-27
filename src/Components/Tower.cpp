//
// Created by Zheng Yang on 25/11/22.
//


#include <Components.h>
#include <Data.h>
#include <cmath>
#include <Utils/Logger.h>
#include <Grids.h>
#include <Core/GameManager.h>

using namespace game::data;
using namespace game::utils;
using namespace game::grid;
using namespace game::core;


namespace game::components {
    Tower::Tower(game::components::GameObject &owner, const data::TowerDefine &data, grid::GridLayer &towerLayer, grid::GridLayer &enemyLayer)
    : GridEntity(owner, towerLayer)
    , mData(data)
    , mEnemyLayer(enemyLayer)
    , mTimeElapsedFromLastAttack(0)
    , mIsSpawned(false) {
        mSprite = mOwner.getComponent<Sprite>();
        if(mSprite == nullptr)
            mSprite = mOwner.addComponent<Sprite>(renderer::ENTITY, 0);

        mAnimator = mOwner.getComponent<CharacterAnimator>();
        if(mAnimator != nullptr)
            mOwner.removeComponent<CharacterAnimator>();
        mAnimator = getGameObject().addComponent<CharacterAnimator>();
        mAnimator->setTarget(mSprite);

        registerAnimation();
    }

    Tower::~Tower() noexcept {
    }

    void Tower::registerAnimation() {
        for(const auto& iter: mData.animations) {
            const auto enemAnim = iter.get();
            mAnimator->registerState(enemAnim->animStateID, enemAnim->animID, enemAnim->makeInitialState);
        }
    }

    const data::TowerDefine &Tower::getData() const {
        return mData;
    }

    void Tower::spawn() {
        mAnimator->start();

        auto index = GridEntity::getGridIndex();
        mIsSpawned = true;
        mTimeElapsedFromLastAttack = 0;
    }

    void Tower::tick(float deltaTime) {
        if(!mIsSpawned)
            return;

        mTimeElapsedFromLastAttack += deltaTime;
        if(mTimeElapsedFromLastAttack < mData.attackInterval)
            return;

        //search enemy
        auto enemy = searchEnemy();
        if(enemy == nullptr)
            return;

        mTimeElapsedFromLastAttack = 0;
        Logger::log("attack!", 5);

        //create projection
        auto projectionData = DataManager::getInstance().get<ProjectionDefine>(data::DataType::PROJECTION, mData.projectileID);
        GoHandle enemyGoHandle = GameManager::getInstance().getEmptyGoHandle();
        enemyGoHandle.updateGUID(enemy->getGUID());

        auto projectionGO = GameManager::getInstance().instantiateGameObject().get();
        projectionGO->getTransform()->setParent(mOwner.getTransform());
        projectionGO->getTransform()->setPivot(PIVOT_CENTER);
        projectionGO->getTransform()->setAnchor(ANCHOR_CENTER);
        projectionGO->getTransform()->setLocalPosition(0, 0);
        projectionGO->getTransform()->setScale(0.5, 0.5);
        projectionGO->addComponent<Projection>(enemyGoHandle, *projectionData, mData);
    }

    GridEntity *Tower::searchEnemy() {
        auto towerIndex = GridEntity::getGridIndex();
        Grid* grid = nullptr;

        bool found = false;
        for(int i = 1; i <= mData.attackRange; i++) {
            for(int j = 1; j <= 2 * i; j++) {
                grid = mEnemyLayer.getGridByIndex(towerIndex.x - i + j, towerIndex.y - i);
                if(grid != nullptr && grid->getEntityCounts() > 0)  {
                    found = true;
                    break;
                }


                grid = mEnemyLayer.getGridByIndex(towerIndex.x + i, towerIndex.y - i + j);
                if(grid != nullptr && grid->getEntityCounts() > 0)  {
                    found = true;
                    break;
                }

                grid = mEnemyLayer.getGridByIndex(towerIndex.x - i + j, towerIndex.y + i);
                if(grid != nullptr && grid->getEntityCounts() > 0)  {
                    found = true;
                    break;
                }

                grid = mEnemyLayer.getGridByIndex(towerIndex.x - i, towerIndex.y - i + j);
                if(grid != nullptr && grid->getEntityCounts() > 0)  {
                    found = true;
                    break;
                }
            }

            if(found)
                break;
        }

        if(found) {
            Logger::log("found enemy!", 5);
            auto& allEntities = grid->getAllEntities();
            int minDistance = INT32_MAX;
            return grid->getAllEntities()[0];
        }

        return nullptr;
    }
}
