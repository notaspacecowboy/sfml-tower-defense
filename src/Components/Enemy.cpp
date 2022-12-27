//
// Created by Zheng Yang on 18/11/22.
//

#include <Components.h>
#include <Data.h>
#include <cmath>
#include <Utils/Logger.h>
#include <Grids.h>

using namespace game::data;
using namespace game::utils;
using namespace game::grid;

const float PI = 3.14159f;

namespace game::components {
    Enemy::Enemy(game::components::GameObject &owner, const data::EnemyDefine &data, const std::vector<sf::Vector2i>* path, GridLayer& layer)
    : GridEntity(owner, layer)
    , mData(data)
    , mPath(path)
    , mCurrentHP(data.hp)
    , mIsAlive(false)
    , mNextPos(0)
    , mCurrentTime(0) {
        mOwner.getTransform()->setScale(mData.scaleSpriteX, mData.scaleSpriteY);

        mSprite = mOwner.getComponent<Sprite>();
        if(mSprite == nullptr)
            mSprite = mOwner.addComponent<Sprite>(renderer::ENTITY, 0);
        mOwner.getTransform()->setPivot(PIVOT_CENTER);

        mAnimator = mOwner.getComponent<CharacterAnimator>();
        if(mAnimator != nullptr)
            mOwner.removeComponent<CharacterAnimator>();
        mAnimator = getGameObject().addComponent<CharacterAnimator>();
        mAnimator->setTarget(mSprite);

        registerAnimation();
    }

    Enemy::~Enemy() noexcept {}

    void Enemy::onEnable() {
        GridEntity::onEnable();
    }

    void Enemy::onDisable() {
        GridEntity::onDisable();
        mDeadAnimCompleteListener.disconnect();
    }

    void Enemy::registerAnimation() {
        for(const auto& iter: mData.animations) {
            const auto enemAnim = iter.get();
            mAnimator->registerState(enemAnim->animStateID, enemAnim->animID, enemAnim->makeInitialState);
        }
    }

    void Enemy::spawn() {
        mNextPos = 0;
        const sf::Vector2i spawnPos = mPath->at(mNextPos++);
        mOwner.getTransform()->setLocalPosition(spawnPos.x, spawnPos.y);
        GridEntity::calculateCurrentGrid();
        faceTo(mPath->at(mNextPos));
        calculateTimeToNextPos();
        mCurrentTime = 0;
        mIsAlive = true;

        mAnimator->start();
        mAnimator->makeTransition(RUN);
    }

    void Enemy::hurt(const data::TowerDefine* attacker) {
        if(!mIsAlive)
            return;

        //should add a class for this instead of calculating the damage here
        mCurrentHP -= attacker->damage;
        if(mCurrentHP < 0) {
            mIsAlive = false;
            GridEntity::unregister();
            if(!onEnemyDead.empty())
                onEnemyDead(&mData);

            if (mAnimator->containsState(AnimationState::DIE))
            {
                mAnimator->makeTransition(DIE);
                mDeadAnimCompleteListener = mAnimator->onAnimationComplete.connect(boost::bind(&Enemy::onDeadAnimationComplete, this));
            }
            else {
                mOwner.setState(GameObject::GoState::MARK_TO_DESTROY);
            }
        }
    }

    void Enemy::onDeadAnimationComplete() {
        mDeadAnimCompleteListener.disconnect();
        mOwner.setState(GameObject::GoState::MARK_TO_DESTROY);
    }

    //rotate enemy towards their moving direction seems super weird in a 2D top-down game, disable this functionality for now
    void Enemy::faceTo(sf::Vector2i position) {
        faceTo(sf::Vector2f(position.x, position.y));
    }

    void Enemy::faceTo(sf::Vector2f position) {
        //mStartAngle = mOwner.getTransform()->getRotate();

        //const sf::Vector2f worldPos = mOwner.getTransform()->getWorldPosition();
        sf::Vector2f offSet = position - sf::Vector2f(mPath->at(mNextPos - 1).x, mPath->at(mNextPos - 1).y) ;

        //facing enemy to a point to its left
        sf::Vector2f scale = mOwner.getTransform()->getScale();
        if(offSet.x < 0) {
            scale.x = std::abs(scale.x) * (mData.isFacingRight ? -1 : 1);
        }
        else {
            scale.x = std::abs(scale.x) * (mData.isFacingRight ? 1 : -1);
        }
        mOwner.getTransform()->setScale(scale.x, scale.y);


//        if(offSet.x < 0)
//            offSet.x *= -1;
//
//        offSet.y *= -1;
//        float angle = atan2f(offSet.y, offSet.x);
//        angle *= 180 / PI;
//        angle *= -1;
//
//        mRotateAngle = angle;
//        mIsRotating = true;
//        mTimeToFinishRotate = abs(mRotateAngle - mStartAngle) / mData->rotateSpeed;
    }

    void Enemy::tick(float deltaTime) {
        if(!mIsAlive)
            return;

        mCurrentTime += deltaTime;
        if(mCurrentTime >= mTimeToNextPos) {
            mNextPos++;

            //reach end
            //TODO: add some logic here
            if(mNextPos >= mPath->size()) {
                onEnemyArriveDestination(&mData);

                mOwner.setState(GameObject::GoState::MARK_TO_DESTROY);
                mIsAlive = false;
                return;
            }
            else {
                mCurrentTime -= mTimeToNextPos;
                faceTo(mPath->at(mNextPos));
                calculateTimeToNextPos();
            }
        }

        //tickRotation();
        tickMovement();
        GridEntity::calculateCurrentGrid();
    }

    void Enemy::calculateTimeToNextPos() {
        //const sf::Vector2f worldPos = mOwner.getTransform()->getWorldPosition();
        //sf::Vector2i offset = mPath->at(mNextPos) - sf::Vector2i(worldPos.x, worldPos.y);
        sf::Vector2i offset = mPath->at(mNextPos) - mPath->at(mNextPos - 1);
        float distance = sqrt(offset.x * offset.x + offset.y * offset.y);
        mTimeToNextPos = distance / mData.speed;
    }

    void Enemy::tickMovement() {
        const sf::Vector2i startPos = mPath->at(mNextPos - 1);
        const sf::Vector2i nextPos  = mPath->at(mNextPos);

        int newX = startPos.x + (mCurrentTime / mTimeToNextPos) * (nextPos.x - startPos.x);
        int newY = startPos.y + (mCurrentTime / mTimeToNextPos) * (nextPos.y - startPos.y);

        mOwner.getTransform()->setLocalPosition(newX, newY);
    }

//    void Enemy::tickRotation() {
//        if(mIsRotating && mCurrentTime >= mTimeToFinishRotate) {
//            mIsRotating = false;
//        }
//        else if(mIsRotating) {
//            float angle = mStartAngle + (mCurrentTime / mTimeToFinishRotate) * (mRotateAngle - mStartAngle);
//            mOwner.getTransform()->setRotate(angle);
//        }
//    }

    const data::EnemyDefine &Enemy::getData() const {
        return mData;
    }
}