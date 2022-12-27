//
// Created by Zheng Yang on 28/10/22.
//

#include "Components/Drawables/Sprite.h"
#include <Core/GameManager.h>
#include <Utils/Logger.h>
#include <Resource/ResourceManager.h>

namespace game::components {
    Sprite::Sprite(game::components::GameObject &owner, renderer::RenderLayer layer, int depth)
    : RenderComponent(owner, layer, depth)
    , mSprite()
    , mReferencedTexture(nullptr)
    , mTextureRect()
    , mPivot(mTransform->getPivot())
    , mSize(0, 0){
    }

    Sprite::~Sprite() {
    }

    void Sprite::onEnable() {
        RenderComponent::onEnable();
    }

    void Sprite::onDisable() {
        RenderComponent::onDisable();
    }

    void Sprite::setTexture(sf::Texture *texture) {
        mReferencedTexture = texture;
        mTextureRect.left = 0;
        mTextureRect.top = 0;

        if(mReferencedTexture == nullptr)
        {
            mTextureRect.width = 0;
            mTextureRect.height = 0;
            return;
        }
        mTextureRect.width = mReferencedTexture->getSize().x;
        mTextureRect.height = mReferencedTexture->getSize().y;
        mSprite.setTexture(*mReferencedTexture);
        mSprite.setTextureRect(mTextureRect);
    }

    void Sprite::setTexture(int tid) {
        setTexture(game::resource::TextureManager::getInstance().getByID(tid));
    }

    void Sprite::setTextureRect(int offsetX, int offsetY, int width, int height) {
        mTextureRect.left = offsetX;
        mTextureRect.top = offsetY;
        mTextureRect.width = width;
        mTextureRect.height = height;
        mSprite.setTextureRect(mTextureRect);
    }

    void Sprite::setSpriteNativeSize() {
        mTransform->setSize(mTextureRect.width, mTextureRect.height);
    }

    bool Sprite::isRaycastable() {
        if(mReferencedTexture != nullptr && mIsRaycastable)
            return true;

        return false;
    }

    void Sprite::draw(sf::RenderWindow &window) {
        if(mReferencedTexture == nullptr || mTextureRect.height == 0 || mTextureRect.width == 0)
            return;

        if(getGUID() == 200) {
            utils::Logger::log(123);
        }
        auto position = mTransform->getWorldPosition();
        auto size = mTransform->getSize();
        auto scale = mTransform->getScale();
        if(mPivot != mTransform->getPivot() || mSize != size) {
            utils::Logger::log("reset origin...");
            mSize = size;
            mPivot = mTransform->getPivot();
            float originX = (mPivot % 3) * mTextureRect.width / 2;
            float originY = (mPivot / 3) * mTextureRect.height / 2;

            mSprite.setOrigin(originX, originY);
        }

        float offsetX = (mPivot % 3) * mSize.x / 2;
        float offsetY = (mPivot / 3) * mSize.y / 2;
        position.x += offsetX;
        position.y += offsetY;

        mSprite.setPosition(position);
        mSprite.setScale(size.x / mTextureRect.width * (scale.x < 0 ? -1 : 1), size.y / mTextureRect.height * (scale.y < 0 ? -1 : 1));
        mSprite.setRotation(mTransform->getRotate());
        window.draw(mSprite);
        //target.draw(mSprite);
    }

    void Sprite::setAlpha(float alpha) {
        if(alpha > 1.f || alpha < 0.f) {
            throw std::runtime_error("alpha must be a value between 0 and 1");
        }

        int alphaChannel = 255 * alpha;
        sf::Color currentColor = mSprite.getColor();
        currentColor.a = alphaChannel;
        mSprite.setColor(currentColor);
    }

    void Sprite::setColor(sf::Color color) {
        mSprite.setColor(color);
    }
}
