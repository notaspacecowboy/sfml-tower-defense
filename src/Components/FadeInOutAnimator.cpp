//
// Created by Zheng Yang on 30/10/22.
//

#include "Components/Animators/FadeInOutAnimator.h"
#include <Utils/Logger.h>

namespace game::components {
    FadeInOutAnimator::FadeInOutAnimator(game::components::GameObject &owner, float startAlpha, float endAlpha,
                                         int duration, bool isLooping, bool isStartAutomatically)
                                         : mStartAlpha(startAlpha)
                                         , mEndAlpha(endAlpha)
                                         , Animator(owner, duration, isLooping, isStartAutomatically) {
    }

    void FadeInOutAnimator::start() {
        mCurrentAlpha = mStartAlpha;
        for(auto drawable: mTargets)
            drawable->setAlpha(mStartAlpha);
        Animator::start();
    }

    void FadeInOutAnimator::tick(float deltaTime) {
        if(!mIsPlaying)
            return;

        mTimeElapsed += deltaTime;
        //linear interpolation
        float percentage = mTimeElapsed / mDuration;
        if(percentage > 1.f)
            percentage = 1.f;

        for(auto target: mTargets)
             target->setAlpha(mStartAlpha + percentage * (mEndAlpha - mStartAlpha));

        if(mTimeElapsed >= mDuration) {
            if(mIsLooping) {
                float tmp = mStartAlpha;
                mStartAlpha = mEndAlpha;
                mEndAlpha = tmp;
                mTimeElapsed = 0;
            }
            else {
                mIsPlaying = false;
                if(!onAnimationComplete.empty())
                    onAnimationComplete();
            }
        }
    }

    void FadeInOutAnimator::addTarget(game::components::RenderComponent *animated) {
        mTargets.emplace_back(animated);
    }

    void FadeInOutAnimator::removeTarget(game::components::RenderComponent *animated) {
        mTargets.erase(std::find(mTargets.begin(), mTargets.end(), animated));
    }
}
