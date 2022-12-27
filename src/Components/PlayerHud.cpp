//
// Created by Zheng Yang on 17/11/22.
//

#include <Components.h>
#include <Core/GameManager.h>
#include <math.h>
#include <boost/signals2/signal.hpp>

using namespace game::core;
using namespace boost::placeholders;

namespace game::components {
    PlayerHud::PlayerHud(game::components::GameObject &owner, prefabs::PlayerHudPrefab prefab)
    : Component(owner)
    , mPrefab(prefab)
    , mTimeElapsed(0) {
        mPlayerState = GameManager::getInstance().getPlayerState();
    }

    void PlayerHud::onEnable() {
        mPrefab.setHP(mPlayerState->getCurrentHP());
        mPrefab.setPoint(mPlayerState->getCurrentPoint());
        mPrefab.setTimeElapsed(0);

        mPlayerHpChangeListener     = mPlayerState->playerHpChangeEvent.connect(boost::bind(&PlayerHud::OnPlayerHpChange, this, _1));
        mPlayerPointChangeListener   = mPlayerState->playerPointChangeEvent.connect(boost::bind(&PlayerHud::OnPlayerPointChange, this, _1));
    }

    void PlayerHud::onDisable() {
        mPlayerHpChangeListener.disconnect();
        mPlayerPointChangeListener.disconnect();
    }

    void PlayerHud::tick(float deltaTime) {
        int seconds = floor(mTimeElapsed);
        mTimeElapsed += deltaTime;
        int newSeconds = floor(mTimeElapsed);
        if(seconds != newSeconds)
            mPrefab.setTimeElapsed(newSeconds);
    }

    void PlayerHud::OnPlayerHpChange(int changeAmount) {
        mPrefab.setHP(mPlayerState->getCurrentHP());
    }

    void PlayerHud::OnPlayerPointChange(int changeAmount) {
        mPrefab.setPoint(mPlayerState->getCurrentPoint());
    }

}
