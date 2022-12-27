//
// Created by Zheng Yang on 20/10/22.
//

#include "Components/Drawables/RenderComponent.h"
#include <Components/GameObject.h>
#include <Core/GameManager.h>

namespace game::components {
    using namespace core;

    const int RenderComponent::LayerModifier = 10000;

    RenderComponent::RenderComponent(game::components::GameObject &owner, renderer::RenderLayer layer, int depth)
        : Component(owner)
        , mTransform(owner.getTransform())
        , mLayer(layer)
        , mDepth(depth)
        , mIsRaycastable(false) {
        mDepth += layer * LayerModifier;
    }

    RenderComponent::~RenderComponent() noexcept {
    }

    void RenderComponent::onEnable() {
        GameManager::getInstance().getRenderer().registerDrawable(this);
    }

    void RenderComponent::onDisable() {
        GameManager::getInstance().getRenderer().unregisterDrawable(this);
    }

    renderer::RenderLayer RenderComponent::getLayer() const {
        return mLayer;
    }

    int RenderComponent::getDepth() const {
        return mDepth;
    }

    void RenderComponent::draw(sf::RenderWindow &window) {
    }

    bool RenderComponent::isRaycastable() {
        return mIsRaycastable;
    }

    sf::FloatRect RenderComponent::getBoundingBox() const {
        sf::Vector2f worldPos = mTransform->getWorldPosition();
        sf::Vector2f size = mTransform->getSize();
        return sf::FloatRect(worldPos.x, worldPos.y, size.x, size.y);
    }

    sf::Vector2f RenderComponent::getSize() const {
        return mTransform->getSize();
    }

    void RenderComponent::setRaycastable(bool isRaycastable) {
        mIsRaycastable = isRaycastable;
    }

    void RenderComponent::setAlpha(float alpha) {}

    void RenderComponent::rotate(float angle) {
        mTransform->rotate(angle);
    }

    void RenderComponent::setRotate(float angle) {
        mTransform->setRotate(angle);
    }
}
