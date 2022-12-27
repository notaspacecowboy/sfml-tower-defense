//
// Created by Zheng Yang on 06/11/22.
//

#include <Core/PlayerState.h>
#include <algorithm>
#include <Utils/Logger.h>
#include <Utils/Time.h>

using namespace game::data;

namespace game::core {
    PlayerState::PlayerState()
    : mHp(0)
    , mPoint(0) {
    }

    void PlayerState::load(data::PlayerData *data) {
        mGameLevel = data->gameLevel;

        mCurrentGold = data->currentGold;

        mPowerUps.clear();
        for(auto powerUp: data->powerUps)
            mPowerUps.push_back(powerUp);

        mUnlockedTowers.clear();
        for(auto tower: data->unlockedTowers)
            mUnlockedTowers.push_back(tower);

        mCompletedAchievements.clear();
        for(auto achievement: data->completedAchievements)
            mCompletedAchievements.push_back(achievement);
    }

    void PlayerState::save(data::PlayerData* data) {
        data->gameLevel = mGameLevel;

        data->currentGold = mCurrentGold;
        data->saveTime = utils::Time::getCurrentTime();

        data->powerUps.clear();
        for(auto powerUp: mPowerUps)
            data->powerUps.push_back(powerUp);

        data->unlockedTowers.clear();
        for(auto tower: mUnlockedTowers)
            data->unlockedTowers.push_back(tower);

        data->completedAchievements.clear();
        for(auto achievement: mCompletedAchievements)
            data->completedAchievements.push_back(achievement);
    }

    int PlayerState::getGameLevel() const {
        return mGameLevel;
    }

    void PlayerState::setGameLevel(int newLevel) {
        mGameLevel = newLevel;
    }


    int PlayerState::getCurrentHP() const {
        return mHp;
    }

    void PlayerState::setHP(int newHP) {
        int tmp = mHp;
        mHp = newHP;

        if(!playerHpChangeEvent.empty())
            playerHpChangeEvent((mHp - tmp));

        if(mHp <= 0 && !playerDeadEvent.empty())
            playerDeadEvent();
    }

    void PlayerState::heal(int healAmount) {
        mHp += healAmount;

        playerHpChangeEvent(healAmount);
    }

    void PlayerState::damage(int damageAmount) {
        if(mHp <= 0)
            return;

        int tmp = mHp;
        mHp -= damageAmount;
        if(mHp <= 0) {
            mHp = 0;
        }
        if(!playerHpChangeEvent.empty())
            playerHpChangeEvent((mHp - tmp));

        if(mHp <= 0 && !playerDeadEvent.empty())
            playerDeadEvent();
    }


    int PlayerState::getCurrentPoint() const {
        return mPoint;
    }

    void PlayerState::setPoint(int newPoint) {
        int tmp = mPoint;
        mPoint = newPoint;
        if(!playerPointChangeEvent.empty())
            playerPointChangeEvent(mPoint - tmp);
    }

    void PlayerState::changePoint(int changedAmount) {
        int tmp = mPoint;

        mPoint += changedAmount;
        if(mPoint < 0)
            mPoint = 0;

        changedAmount = mPoint - tmp;
        if(!playerPointChangeEvent.empty())
            playerPointChangeEvent(changedAmount);
    }



    int PlayerState::getCurrentGold() const {
        return mCurrentGold;
    }

    void PlayerState::changeGold(int changedAmount) {
        int tmp = mCurrentGold;

        mCurrentGold += changedAmount;
        if(mCurrentGold < 0)
            mCurrentGold = 0;

        changedAmount = mCurrentGold - tmp;
        if(!playerGoldChangeEvent.empty())
            playerGoldChangeEvent(changedAmount);
    }

    const std::vector<int> &PlayerState::getCurrentPowerUps() const {
        return mPowerUps;
    }

    void PlayerState::addPowerUp(int id) {
        if(std::find(mPowerUps.begin(), mPowerUps.end(), id) != mPowerUps.end()) {
            utils::Logger::log("powerup already exist");
            return;
        }
        mPowerUps.push_back(id);
    }

    const std::vector<int> &PlayerState::getCurrentLockedTowers() const {
        return mUnlockedTowers;
    }

    void PlayerState::unlockTower(int id) {
        if(std::find(mUnlockedTowers.begin(), mUnlockedTowers.end(), id) != mUnlockedTowers.end()) {
            utils::Logger::log("tower already unlocked");
            return;
        }
        mUnlockedTowers.push_back(id);
    }

    const std::vector<int> &PlayerState::getCurrentCompletedAchievements() const {
        return mCompletedAchievements;
    }

    void PlayerState::completeAchievement(int id) {
        if(std::find(mCompletedAchievements.begin(), mCompletedAchievements.end(), id) != mCompletedAchievements.end()) {
            utils::Logger::log("achievement already completed");
            return;
        }

        mCompletedAchievements.push_back(id);
    }

    void PlayerState::reset() {
        PlayerData newData;
        load(&newData);
    }
}
