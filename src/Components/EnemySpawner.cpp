//
// Created by Zheng Yang on 20/11/22.
//

#include <Components.h>
#include <Data.h>
#include <cmath>
#include <Core/GameManager.h>
#include <Utils/Logger.h>
#include <Grids.h>

using namespace game::data;
using namespace game::core;
using namespace game::utils;
using namespace game::grid;

const std::string ENEMY_LAYER           = "Enemies";
const std::string ENTITY_TYPE_NAME      = "EnemyPath";
const std::string PATROL_PATH_FIELD     = "PatrolPath";

namespace game::components {
    EnemySpawner::EnemySpawner(game::components::GameObject &owner, grid::GridSystem* gridSystem)
    : Component(owner)
    , mGameLevel(nullptr)
    , mGridSystem(gridSystem)
    , mData(nullptr)
    , mEnemies()
    , mEnemyPaths()
    , mCurrentFightIndex(0)
    , mIsSpawning(false)
    , mTimeElapsedAfterLastSpawn(0)
    , mTimeToSpawnNextEnemy(0)
    , mTotalRegularEnemyToSpawn(0)
    , mTotalEliteEnemyToSpawn(0)
    {}

    EnemySpawner::~EnemySpawner() noexcept {
    }

    void EnemySpawner::onEnable() {
        mIsSpawning = false;
        mTimeElapsedAfterLastSpawn = 0;
        mTimeToSpawnNextEnemy = 0;
        mTotalRegularEnemyToSpawn = 0;
        mTotalEliteEnemyToSpawn = 0;
    }

    void EnemySpawner::onDisable() {
    }

    void EnemySpawner::loadLevel(const ldtk::Level* level) {
        mGameLevel = level;
        auto gamelevelIndex = GameManager::getInstance().getPlayerState()->getGameLevel() + 1;
        mData = DataManager::getInstance().get<EnemySpawnRuleDefine>(data::DataType::ENEMY_SPAWN_RULE, gamelevelIndex);
        assert(mData != nullptr);
        mRegularEnemyTypes.clear();
        mEliteEnemyTypes.clear();
        for(int tid: mData->enemyList) {
            const auto* data = DataManager::getInstance().get<EnemyDefine>(data::DataType::ENEMY, tid);
            if(data->isElite)
                mEliteEnemyTypes.emplace_back(data);
            else
                mRegularEnemyTypes.emplace_back(data);
        }

        mEnemyPaths.clear();
        const auto& layerData = mGameLevel->getLayer(ENEMY_LAYER);
        for(const ldtk::Entity& enemy: layerData.getEntitiesByName(ENTITY_TYPE_NAME)) {
            const auto& size = enemy.getSize();

            const auto& path = enemy.getArrayField<ldtk::IntPoint>(PATROL_PATH_FIELD);
            std::vector<sf::Vector2i> pathVector;
            for(auto point: path) {
                pathVector.emplace_back(point->x * size.x, point->y * size.y);
            }

            mEnemyPaths.emplace_back(pathVector);
        }

        mCurrentFightIndex = 0;
    }

    void EnemySpawner::Spawn() {
        assert(mData != nullptr);
        assert(mCurrentFightIndex < mData->totalFights);

        if(mIsSpawning)
            return;

        const auto& fightDefine = mData->fights[mCurrentFightIndex];
        mIsSpawning = true;
        mTimeElapsedAfterLastSpawn = 0;
        float minWaitTime = fightDefine->minimumWaitTime;
        float maxWaitTime = fightDefine->maximumWaitTime;
        mTimeToSpawnNextEnemy = minWaitTime + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxWaitTime-minWaitTime)));

        mTotalRegularEnemyToSpawn = floor(fightDefine->totalEnemies * fightDefine->regularEnemies);
        mTotalEliteEnemyToSpawn   = floor(fightDefine->totalEnemies * fightDefine->eliteEnemies);

    }

    void EnemySpawner::tick(float deltaTime) {
        if(!mIsSpawning || mData == nullptr)
            return;

        mTimeElapsedAfterLastSpawn += deltaTime;
        if(mTimeElapsedAfterLastSpawn < mTimeToSpawnNextEnemy)
            return;

        //Logger::log("wait time: " + std::to_string(mTimeToSpawnNextEnemy), 5);

        const auto& fightDefine = mData->fights[mCurrentFightIndex];
        mTimeElapsedAfterLastSpawn = 0;
        float minWaitTime = fightDefine->minimumWaitTime;
        float maxWaitTime = fightDefine->maximumWaitTime;
        mTimeToSpawnNextEnemy = minWaitTime + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxWaitTime-minWaitTime)));

        auto& layer = *(mGridSystem->getGridLayerByID(Layer::PATH));
        if(mTotalRegularEnemyToSpawn > 0) {
            int randomEnemyType = rand() % mRegularEnemyTypes.size();
            int randomPath = rand() % mEnemyPaths.size();
            const auto* enemyData = mRegularEnemyTypes[randomEnemyType];
            auto go = GameManager::getInstance().instantiateGameObject().get();
            go->getTransform()->setParent(mOwner.getTransform());
            auto enemy = go->addComponent<Enemy>(*enemyData, &mEnemyPaths[randomPath], layer);
            enemy->spawn();
            onEnemySpawned(enemy);
            mTotalRegularEnemyToSpawn--;
        }

        if(mTotalEliteEnemyToSpawn > 0) {
            int randomEnemyType = rand() % mEliteEnemyTypes.size();
            int randomPath = rand() % mEnemyPaths.size();
            const auto* enemyData = mEliteEnemyTypes[randomEnemyType];
            auto go = GameManager::getInstance().instantiateGameObject().get();
            go->getTransform()->setParent(mOwner.getTransform());
            auto enemy = go->addComponent<Enemy>(*enemyData, &mEnemyPaths[randomPath], layer);
            enemy->spawn();
            onEnemySpawned(enemy);
            mTotalEliteEnemyToSpawn--;
        }

        if(mTotalRegularEnemyToSpawn == 0 && mTotalEliteEnemyToSpawn == 0) {
            mIsSpawning = false;
            mCurrentFightIndex++;
            onAllEnemiesSpawned();
        }
    }

    int EnemySpawner::getCurrentFightIndex() const {
        return mCurrentFightIndex;
    }

    int EnemySpawner::getTotalFights() const {
        return mData->totalFights;
    }

    bool EnemySpawner::hasMoreFights() const {
        //temp
        return false;
    }
}
