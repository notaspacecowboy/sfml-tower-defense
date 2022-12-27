//
// Created by Zheng Yang on 03/11/22.
//

#include <Components.h>
#include <Utils/Logger.h>
#include <Data/DataManager.h>
#include <Resource/ResourceManager.h>

using namespace game::data;
using namespace game::resource;

namespace game::components {
    CharacterAnimator::CharacterAnimator(game::components::GameObject &owner)
    : Animator(owner, 0, true, false)
    , mInitialAnimation(nullptr)
    , mTarget(nullptr) {
    }

    void CharacterAnimator::start() {
        if(mTarget == nullptr || mInitialAnimation == nullptr) {
            utils::Logger::log("animator cannot find a target or animator cannot find any animation clips attached", 5);
            return;
        }

        mCurrentAnimation = mInitialAnimation;
        mCurrentAnimIndex = 0;
        mCachedTexture = TextureManager::getInstance().getByID(mCurrentAnimation->textureID);

        sf::Vector2f size(mCachedTexture->getSize().x / mCurrentAnimation->column, mCachedTexture->getSize().y / mCurrentAnimation->row);
        mTarget->setTexture(mCachedTexture);
        mTarget->setTextureRect(0, 0, size.x, size.y);
        mTarget->setSpriteNativeSize();
        mGoReverse = false;
        mIsLooping = mCurrentAnimation->isLooping;
        Animator::start();
    }

    void CharacterAnimator::stop() {
        Animator::stop();
    }

    void CharacterAnimator::setTarget(game::components::Sprite *target) {
        mTarget = target;
    }

    void CharacterAnimator::makeTransition(game::components::AnimationState state) {
        auto find = mStateMap.find(state);
        if(find == mStateMap.end())
        {
            utils::Logger::log("trying to change to an invalid state", 5);
            return;
        }

        mCurrentAnimation = find->second;
        mCurrentState = state;
        mCurrentAnimIndex = 0;
        mTimeElapsed = 0;
        mIsLooping = mCurrentAnimation->isLooping;
        mCachedTexture = TextureManager::getInstance().getByID(mCurrentAnimation->textureID);

        sf::Vector2f size(mCachedTexture->getSize().x / mCurrentAnimation->column, mCachedTexture->getSize().y / mCurrentAnimation->row);
        mTarget->setTexture(mCachedTexture);
        mTarget->setTextureRect(0, 0, size.x, size.y);
        mTarget->setSpriteNativeSize();
        mGoReverse = false;
        mIsPlaying = true;
    }

    void CharacterAnimator::registerState(game::components::AnimationState state, int tid, bool makeInitialState) {
        auto find = mStateMap.find(state);
        if(find != mStateMap.end())
            return;

        auto animDefine = DataManager::getInstance().get<AnimDefine>(data::DataType::ANIMATION, tid);
        mStateMap.insert(std::make_pair(state, animDefine));

        if(makeInitialState) {
            mInitialAnimation = animDefine;
            mCurrentState = state;
        }
    }

    void CharacterAnimator::registerState(int animStateID, int tid, bool makeInitialState) {
        AnimationState state = static_cast<AnimationState>(animStateID);
        registerState(state, tid, makeInitialState);
    }

    AnimationState CharacterAnimator::getCurrentState() const {
        return mCurrentState;
    }

    bool CharacterAnimator::containsState(game::components::AnimationState state) {
        auto find = mStateMap.find(state);
        if(find == mStateMap.end())
            return false;

        return true;
    }

    void CharacterAnimator::tick(float deltaTime) {
        if (!mIsPlaying)
            return;

        mTimeElapsed += deltaTime;
        if (mTimeElapsed < 1.f / mCurrentAnimation->speed)
            return;

        mTimeElapsed = 0;

        if(mCurrentAnimation->reverse) {
            mCurrentAnimIndex = (mGoReverse ? mCurrentAnimIndex - 1 : mCurrentAnimIndex + 1);
            if (mCurrentAnimIndex == 0 || mCurrentAnimIndex == mCurrentAnimation->column * mCurrentAnimation->row - 1)
                mGoReverse = !mGoReverse;
        }
        else {
            auto totalCount = mCurrentAnimation->row * mCurrentAnimation->column;
            if(!mIsLooping && mCurrentAnimIndex == totalCount - 1)
            {
                mIsPlaying = false;

                if(!onAnimationComplete.empty())
                    onAnimationComplete();
                return;
            }

            mCurrentAnimIndex = (mCurrentAnimIndex + 1) % totalCount;
        }

        //utils::Logger::log("current index: " + std::to_string(mCurrentAnimIndex), 5);
        sf::Vector2f size(mCachedTexture->getSize().x / mCurrentAnimation->column, mCachedTexture->getSize().y / mCurrentAnimation->row);
        int offsetX = size.x * (mCurrentAnimIndex % mCurrentAnimation->column);
        int offsetY = size.y * (mCurrentAnimIndex / mCurrentAnimation->column);
        mTarget->setTextureRect(offsetX, offsetY, size.x, size.y);
    }

    void CharacterAnimator::getAllStates(std::vector<AnimationState> &states) const {
        states.clear();
        auto iter = mStateMap.begin();
        for(; iter != mStateMap.end(); iter++) {
            states.push_back(iter->first);
        }
    }
}
