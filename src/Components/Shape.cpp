//
// Created by Zheng Yang on 03/11/22.
//

#include "Components/Drawables/Shape.h"

namespace game::components {
    Shape::Shape(game::components::GameObject &owner, sf::Color color, renderer::RenderLayer layer, int depth)
    : RenderComponent(owner, layer, depth)
    , mColor(color)
    , mShape() {
        mShape.setFillColor(mColor);
    }

    void Shape::onEnable() {
        RenderComponent::onEnable();
    }

    void Shape::onDisable() {
        RenderComponent::onDisable();
    }

    void Shape::draw(sf::RenderWindow &window) {
        auto position = mTransform->getWorldPosition();
        auto size = mTransform->getSize();
        auto pivot = mTransform->getPivot();

//        float offsetX = (pivot% 3) * size.x / 2;
//        float offsetY = (pivot / 3) * size.y / 2;
//        position.x += offsetX;
//        position.y += offsetY;

        mShape.setPosition(position);
        mShape.setSize(size);
        //mShape.setRotation(mTransform->getRotate());
        window.draw(mShape);
    }

    void Shape::setAlpha(float alpha) {
        if(alpha > 1.f || alpha < 0.f) {
            throw std::runtime_error("alpha must be a value between 0 and 1");
        }

        int alphaChannel = 255 * alpha;
        sf::Color currentColor = mShape.getFillColor();
        currentColor.a = alphaChannel;
        mColor = currentColor;
        mShape.setFillColor(currentColor);
    }
}
