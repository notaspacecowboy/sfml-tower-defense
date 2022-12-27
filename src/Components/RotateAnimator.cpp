//
// Created by Zheng Yang on 31/10/22.
//

#include "Components/Animators/RotateAnimator.h"
#include "Components/Drawables/RenderComponent.h"
#include <Utils/Logger.h>

namespace game::components {
    RotateAnimator::RotateAnimator(game::components::GameObject &owner, float startAngle, float endAngle, int duration,
                                   bool isLooping, bool isStartAutomatically)
                                   : Animator(owner, duration, isLooping, isStartAutomatically)
                                   , mStartAngle(startAngle)
                                   , mEndAngle(endAngle)
                                   , mCurrentAngle(0){}

    void RotateAnimator::start() {
        if(mTarget == nullptr) {
            throw std::runtime_error("must set a target before starting animation!");
            return;
        }

        mCurrentAngle = mStartAngle;
        Animator::start();
    }

    void RotateAnimator::setTarget(game::components::RenderComponent* target) {
        mTarget = target;
        if(mIsStartAutomatically)
            start();
    }

    void RotateAnimator::tick(float deltaTime) {
        if(!mIsPlaying)
            return;

        mTimeElapsed += deltaTime;
        //linear interpolation
        float percentage = mTimeElapsed / mDuration;
        if(percentage > 1.f)
            percentage = 1.f;

        mTarget->setRotate(mStartAngle + percentage * (mEndAngle - mStartAngle));
        if(mTimeElapsed >= mDuration) {
            if(mIsLooping) {
                mCurrentAngle = mStartAngle;
                mTimeElapsed = 0;
            }
            else {
                mIsPlaying = false;
                if(!onAnimationComplete.empty())
                    onAnimationComplete();
            }
        }
    }
}
