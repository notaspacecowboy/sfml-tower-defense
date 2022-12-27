//
// Created by Zheng Yang on 30/10/22.
//

#include <Components/Button.h>
#include <Components/GameObject.h>
#include <Resource/ResourceManager.h>
#include <Core/GameManager.h>
#include <Utils/Logger.h>
#include <Audio.h>

namespace game::components {

    Button::Button(game::components::GameObject &owner, const data::ButtonDefine *buttonDefine, renderer::RenderLayer layer, int depth)
    : Component(owner)
    , mData(buttonDefine)
    , mSprite(nullptr)
    , mText(nullptr)
    , mLayer(layer)
    , mDepth(depth) {
        mNormalTexture = resource::TextureManager::getInstance().getByID(mData->textureID);
        mPressedTexture = (mData->hasPressedSprite ? resource::TextureManager::getInstance().getByID(mData->pressed_textureID) : nullptr);
    }

    Button::~Button() {
    }

    void Button::onEnable() {
        if(mSprite == nullptr) {
            if(mOwner.getComponent<Sprite>() == nullptr) {
                mSprite = mOwner.addComponent<Sprite>(mLayer, mDepth);

                mSprite->setTexture(mNormalTexture);
                if(mData->isSpriteSheet) {
                    mSprite->setTextureRect(mData->offsetX, mData->offsetY, mData->width, mData->height);
                }

                mSprite->setSpriteNativeSize();
                mOwner.getTransform()->setScale(mData->scale, mData->scale);
            }
        }

        if(mText == nullptr && mData->hasText) {
            auto textGO = core::GameManager::getInstance().instantiateGameObject(GameObject::GoState::ACTIVE).get();
            textGO->getTransform()->setParent(mOwner.getTransform());
            //->getTransform()->setLocalPosition(mData->textOffsetX, mData->textOffsetY);
            mText = textGO->addComponent<Text>(mLayer, mDepth + 1);
            mText->setFont(resource::FontManager::getInstance().getByID(mData->fontID));
            mText->setTextSize(mData->textSize);
            mText->getGameObject().getTransform()->setAnchor(ANCHOR_CENTER);
            mText->getGameObject().getTransform()->setPivot(PIVOT_CENTER);
            mText->getGameObject().getTransform()->setLocalPosition(mData->textOffsetX, mData->textOffsetY);

            //utils::Logger::log(mSprite->getGameObject().getTransform()->getWorldPosition(), 5);
            //utils::Logger::log(mText->getGameObject().getTransform()->getWorldPosition(), 5);
        }

        mSprite->setRaycastable(true);
    }

    void Button::onDisable() {
        utils::Logger::log("button disabled");
    }

    void Button::onPointerPress() {
        audio::SoundManager::getInstance().play(mData->sfx_onclick);

        if(mData->hasPressedSprite) {
            mSprite->setTexture(mPressedTexture);
            if(mData->isSpriteSheet) {
                mSprite->setTextureRect(mData->pressed_offsetX, mData->pressed_offsetY, mData->pressed_width, mData->pressed_height);
            }
            if(mData->hasText) {
                mText->getGameObject().getTransform()->move(mData->pressed_textOffsetX, mData->pressed_textOffsetY);
            }
        }
    }

    void Button::onPointerRelease() {
        mSprite->setTexture(mNormalTexture);
        if(mData->isSpriteSheet) {
            mSprite->setTextureRect(mData->offsetX, mData->offsetY, mData->width, mData->height);
        }
        if(mData->hasText) {
            mText->getGameObject().getTransform()->move(mData->pressed_textOffsetX * -1, mData->pressed_textOffsetY * -1);
        }
    }

    void Button::onPointerClick() {
        if(!onClick.empty())
            onClick();
    }

    void Button::setRaycastable(bool isRaycastable) {
        mSprite->setRaycastable(isRaycastable);
    }

    Text *Button::getText() const {
        return mText;
    }

    Sprite *Button::getSprite() const {
        return mSprite;
    }
}
