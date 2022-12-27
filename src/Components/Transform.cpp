//
// Created by Zheng Yang on 08/10/22.
//

#include "Components/Transform.h"
#include <cassert>
#include <Utils/Logger.h>
#include <Components/GameObject.h>

namespace game::components {
    Transform::Transform(GameObject &owner)
        : Component(owner)
        , mParent(nullptr)
        , mChildren()
        , mIsDirty(false)
        , mSize(0, 0)
        , mAnchor(ANCHOR_TOP_LEFT)
        , mPivot(PIVOT_TOP_LEFT)
        , mLocalPosition()
        , mCachedWorldPosition()
        , mRotate(0)
        , mScale(1.f, 1.f) {
    }

    Transform::~Transform() noexcept {
        if(mParent != nullptr)
            mParent->detachChild(this);
    }

    void Transform::onEnable() {
        utils::Logger::log("Transform onEnable");

        for(auto child: mChildren) {
            child->getGameObject().setState(mOwner.getState());
        }
    }

    void Transform::onDisable() {
        utils::Logger::log("Transform onDisable");

        for(auto child: mChildren) {
            child->getGameObject().setState(mOwner.getState());
        }
    }

    void Transform::tick(float deltaTime) {
    }

    void Transform::setParent(game::components::Transform *parent) {
        if(mParent != nullptr && mParent == parent)
            return;

        assert(this != mParent);

        sf::Vector2f newLocalPos = getWorldPosition();
        int halfWidth = mSize.x / 2;
        int halfHeight = mSize.y / 2;
        newLocalPos.x += halfWidth * (mPivot % 3);
        newLocalPos.y += halfHeight * (mPivot / 3);

        this->mParent = parent;
        if(parent == nullptr) {
            setLocalPosition(newLocalPos);
            return;
        }
        mParent->attachChild(this);

        halfWidth = mParent->getSize().x / 2;
        halfHeight = mParent->getSize().y / 2;
        newLocalPos.x -= halfWidth * (mAnchor % 3);
        newLocalPos.y -= halfHeight * (mAnchor / 3);

        setLocalPosition(newLocalPos);

        //do not need to set dirty because world position for this game object is not changed
        //setDirty();
    }

    Transform *Transform::getParent() const {
        return this->mParent;
    }

    sf::Vector2f Transform::getScale() const {
        return mScale;
    }

    void Transform::setScale(float x, float y) {
        mScale.x = x;
        mScale.y = y;
    }

    void Transform::setDirty() {
        mIsDirty = true;

        for(Transform *child: mChildren) {
            child->setDirty();
        }
    }


    //do not call this function directly, use setParent instead
    void Transform::attachChild(game::components::Transform *child) {
        mChildren.push_back(child);
    }

    void Transform::detachChild(const game::components::Transform *child) {
        auto find = std::find(mChildren.begin(), mChildren.end(), child);
        if(find != mChildren.end())
            mChildren.erase(find);
    }

    void Transform::reset() {
        setParent(nullptr);
        setLocalPosition(sf::Vector2f(0, 0));
    }

    void Transform::setSize(sf::Vector2f newSize) {
        setSize(newSize.x, newSize.y);
    }

    void Transform::setSize(float width, float height) {
        mSize.x = width;
        mSize.y = height;
        setDirty();
    }

    void Transform::move(float width, float height) {
        mLocalPosition.x += width;
        mLocalPosition.y += height;

        setDirty();
    }

    sf::Vector2f Transform::getSize() const {
        return sf::Vector2f(std::abs(mSize.x * mScale.x), std::abs(mSize.y * mScale.y));
    }


    sf::Vector2f Transform::getLocalPosition() const {
        return mLocalPosition;
    }

    void Transform::setLocalPosition(sf::Vector2f newPos) {
        setLocalPosition(newPos.x, newPos.y);
    }

    void Transform::setLocalPosition(float x, float y) {
        mLocalPosition.x = x;
        mLocalPosition.y = y;

        setDirty();
    }

    sf::Vector2f Transform::getWorldPosition() {
        if(!mIsDirty)
            return mCachedWorldPosition;

        //utils::Logger::Log("recalculating world position...");
        sf::Vector2f posFromTopLeft = mLocalPosition;
        int halfWidth = mSize.x * std::abs(mScale.x) / 2;
        int halfHeight = mSize.y * std::abs(mScale.y) / 2;
        posFromTopLeft.x -= halfWidth * (mPivot % 3);
        posFromTopLeft.y -= halfHeight * (mPivot / 3);

        if(mParent == nullptr) {
            mCachedWorldPosition = posFromTopLeft;
            mIsDirty = false;
            return mCachedWorldPosition;
        }

        auto parentSize = mParent->getSize();
        if(parentSize.x != 0 || parentSize.y != 0) {
            halfWidth = parentSize.x / 2;
            halfHeight = parentSize.y / 2;

            posFromTopLeft.x += halfWidth * (mAnchor % 3);
            posFromTopLeft.y += halfHeight * (mAnchor / 3);
        }

        sf::Vector2f parentPos = mParent->getWorldPosition();
        posFromTopLeft.x += parentPos.x;
        posFromTopLeft.y += parentPos.y;

        mCachedWorldPosition = posFromTopLeft;
        mIsDirty = false;
        return mCachedWorldPosition;
    }










    void Transform::setAnchor(game::components::Anchor newAnchor) {
        //TODO change anchor should only affect a transform's local position, while its world position should not be affected
        if(mParent == nullptr || (mParent->getSize() == sf::Vector2f()))
        {
            mAnchor = newAnchor;
            return;
        }

        sf::Vector2f newLocalPos = getLocalPosition();
        float halfWidth = mParent->getSize().x / 2;
        float halfHeight = mParent->getSize().y / 2;
        newLocalPos.x += halfWidth * (mAnchor % 3);
        newLocalPos.x -= halfWidth * (newAnchor % 3);
        newLocalPos.y += halfHeight * (mAnchor / 3);
        newLocalPos.y -= halfHeight * (newAnchor / 3);

        setLocalPosition(newLocalPos);
        mAnchor = newAnchor;
    }

    Anchor Transform::getAnchor() const {
        return mAnchor;
    }

    void Transform::setPivot(game::components::Pivot newPivot) {
        //TODO change pivot should only affect a transform's local position, while its world position should not be affected
        if(newPivot == mPivot)
            return;

        if(mSize.x == 0 && mSize.y == 0)
        {
            mPivot = newPivot;
            return;
        }

        float halfWidth = mSize.x / 2;
        float halfHeight = mSize.y / 2;
        sf::Vector2f newLocalPos = getLocalPosition();
        newLocalPos.x -= halfWidth * (mPivot % 3);
        newLocalPos.y -= halfHeight * (mPivot / 3);
        newLocalPos.x += halfWidth * (newPivot % 3);
        newLocalPos.y += halfHeight * (newPivot / 3);

        setLocalPosition(newLocalPos);
        mPivot = newPivot;
    }

    Pivot Transform::getPivot() const {
        return mPivot;
    }

    void Transform::matchParent() {
        if(mParent == nullptr)
        {
            utils::Logger::log("Transform->setToParentSize: parent is null");
            return;
        }

        setSize(mParent->getSize());
        auto pivotX = (mPivot % 3) * mSize.x / 2;
        auto pivotY = (mPivot / 3) * mSize.y/ 2;

        auto anchorX = (mAnchor % 3) * mParent->getSize().x / 2;
        auto anchorY = (mAnchor / 3) * mParent->getSize().y / 2;
        setLocalPosition(-anchorX + pivotX, -anchorY + pivotY);
    }

    void Transform::setRotate(float angle) {
        mRotate = angle;
        for(auto child: mChildren) {
            child->setRotate(angle);
        }
    }

    void Transform::rotate(float angle) {
        mRotate += angle;
        for(auto child: mChildren) {
            child->rotate(angle);
        }
    }

    float Transform::getRotate() const {
        return mRotate;
    }

    int Transform::getChildrenCount() const {
        return mChildren.size();
    }

} // game::components