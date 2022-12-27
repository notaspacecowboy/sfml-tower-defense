//
// Created by Zheng Yang on 30/10/22.
//

#include "Components/Animators/Animator.h"
#include "Utils/Logger.h"

namespace game::components {
    Animator::Animator(game::components::GameObject &owner, int duration, bool isLooping, bool isStartAutomatically)
    : Component(owner)
    , mDuration(duration)
    , mIsLooping(isLooping)
    , mIsStartAutomatically(isStartAutomatically)
    , mTimeElapsed(0) {
    }

    Animator::~Animator() noexcept {
    }

    void Animator::start() {
        mIsPlaying = true;
        mTimeElapsed = 0;
    }

    void Animator::stop() {
        mIsPlaying = false;
    }

    void Animator::onEnable() {
        if(mIsStartAutomatically)
            start();
    }

    void Animator::onDisable() {
        stop();
    }
}