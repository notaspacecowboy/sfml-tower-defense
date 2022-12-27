//
// Created by Zheng Yang on 05/11/22.
//

#include <Components.h>

namespace game::components {
    GridLayout::GridLayout(game::components::GameObject &owner,sf::Vector2i gridSize, sf::Vector2i gridMargin, sf::Vector2i elementSize)
    : Component(owner)
    , mTransform(owner.getTransform())
    , mGridSize(gridSize)
    , mElementSize(elementSize)
    , mGridMargin(gridMargin) {
        setLayoutHorizontal();
        setLayoutVertical();
    }

    void GridLayout::onEnable() {
        GridLayout::setLayoutVertical();
        GridLayout::setLayoutHorizontal();
    }

    void GridLayout::setGridElementSize(int width, int height) {
        mElementSize.x = width;
        mElementSize.y = height;

        setLayoutHorizontal();
        setLayoutVertical();
    }

    void GridLayout::setMargin(int x, int y) {
        mGridMargin.x = x;
        mGridMargin.y = y;

        setLayoutHorizontal();
        setLayoutVertical();
    }

    void GridLayout::setGridSize(int x, int y) {
        mGridSize.x = x;
        mGridSize.y = y;

        setLayoutHorizontal();
        setLayoutVertical();
    }

    void GridLayout::setLayoutHorizontal() {
        int width = (mElementSize.x + mGridMargin.x) * mGridSize.x + mGridMargin.x;
        mOwner.getTransform()->setSize(width, mOwner.getTransform()->getSize().y);
    }

    void GridLayout::setLayoutVertical() {
        int height = (mElementSize .y + mGridMargin.y) * mGridSize.y + mGridMargin.y;
        mOwner.getTransform()->setSize(mOwner.getTransform()->getSize().x, height);
    }

    void GridLayout::addGridElement(game::components::Transform *element) {
        int totalChild = mTransform->getChildrenCount();
        element->setParent(mTransform);
        element->setSize(mElementSize.x, mElementSize.y);

        setElementPosition(element, totalChild);
    }

    void GridLayout::setElementPosition(Transform* element, int index) {
        int offsetX = mGridMargin.x + (mGridMargin.x + mElementSize.x) * (index % mGridSize.x);
        int offsetY = mGridMargin.y + (mGridMargin.y + mElementSize.y) * (index / mGridSize.x);
        element->setLocalPosition(offsetX, offsetY);
    }
}
