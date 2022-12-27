//
// Created by Zheng Yang on 25/11/22.
//


#include <Components.h>
#include <Data.h>
#include <cmath>
#include <Utils/Logger.h>
#include <Grids.h>

using namespace game::data;
using namespace game::utils;
using namespace game::grid;

const float MIN_DISTANCE = 20.f;
const float PI = 3.14159f;

namespace game::components {
    Projection::Projection(game::components::GameObject &owner, core::GoHandle target,
                           const data::ProjectionDefine &projectionData, const data::TowerDefine &towerData)
    : Component(owner)
    , mTarget(target)
    , mData(projectionData)
    , mAttackerData(towerData) {
        //mOwner.getTransform()->setScale(mData.scaleSpriteX, mData.scaleSpriteY);

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

    Projection::~Projection() noexcept {}

    void Projection::registerAnimation() {
        for(const auto& iter: mData.animations) {
            const auto enemAnim = iter.get();
            mAnimator->registerState(enemAnim->animStateID, enemAnim->animID, enemAnim->makeInitialState);
        }
    }

    void Projection::onEnable() {
        mAnimator->start();
    }

    void Projection::onDisable() {}


    void Projection::tick(float deltaTime) {
        //if enemy is dead / reach the destination, destroy projection
        if(!mTarget) {
            mOwner.setState(GameObject::GoState::MARK_TO_DESTROY);
            return;
        }

        auto target = mTarget.get();

        auto worldPos = mOwner.getTransform()->getWorldPosition();
        auto targetWorldPos = target->getTransform()->getWorldPosition();

        auto distance = getDistance(worldPos, targetWorldPos);

        //do the actual damage
        if(distance < MIN_DISTANCE) {
            auto enemy = mTarget->getComponent<Enemy>();
            assert(enemy != nullptr);
            enemy->hurt(&mAttackerData);

            mOwner.setState(GameObject::GoState::MARK_TO_DESTROY);
            return;
        }

        //tick projection position
        auto offSet = targetWorldPos - worldPos;
        float speedX = offSet.x / distance * mData.speed * deltaTime;
        float speedY = offSet.y / distance * mData.speed * deltaTime;

        mOwner.getTransform()->move(speedX, speedY);

        //tickRotation();

        offSet.y *= -1;
        float angle = atan2f(offSet.y, offSet.x);
        angle *= 180 / PI;
        angle *= -1;

        mOwner.getTransform()->setRotate(angle);
    }


    float Projection::getDistance(sf::Vector2f pos1, sf::Vector2f pos2) {
        sf::Vector2f distance(pos1.x - pos2.x, pos1.y - pos2.y);
        return std::sqrt(distance.x * distance.x + distance.y * distance.y);
    }

}