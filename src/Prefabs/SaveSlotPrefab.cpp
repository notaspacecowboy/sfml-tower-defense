//
// Created by Zheng Yang on 06/11/22.
//

#include <Prefabs.h>
#include <Core/GameManager.h>
#include <Components.h>
#include <Resource/ResourceManager.h>
#include <Renderer/RenderLayer.h>

using namespace game::core;
using namespace game::components;
using namespace game::resource;
using namespace game::renderer;

namespace game::prefabs {
    SaveSlotPrefab::SaveSlotPrefab() {
        mRoot = GameManager::getInstance().instantiateGameObject();
        auto bgGO = mRoot.get();
        bgGO->getTransform()->setSize(300, 300);

        mFrame = bgGO->addComponent<Sprite>(UI, 101);
        mFrame->setTexture(TextureManager::getInstance().getByID(TEXTURE_ITEM_FRAME_1));

        auto go = GameManager::getInstance().instantiateGameObject().get();
        auto transform = go->getTransform();
        transform->setParent(bgGO->getTransform());
        transform->setPivot(components::PIVOT_CENTER);
        transform->setAnchor(components::ANCHOR_CENTER);

        go->getTransform()->setLocalPosition(0, 0);
        go->getTransform()->setSize(270, 270);
        sf::Color bgColor(173, 154, 153, 255);
        go->addComponent<Shape>(bgColor, renderer::UI, 100);

        //level text
        go = GameManager::getInstance().instantiateGameObject().get();
        transform = go->getTransform();
        transform->setParent(bgGO->getTransform());
        transform->setLocalPosition(40, 50);
        mLevelText = go->addComponent<Text>(UI, 105);
        mLevelText->setFont(FontManager::getInstance().getByID(FONT_GUI_1));
        mLevelText->setTextSize(50);
        mLevelText->setText("Level: 1", true);

        //gold text
        go = GameManager::getInstance().instantiateGameObject().get();
        transform = go->getTransform();
        transform->setParent(bgGO->getTransform());
        transform->setLocalPosition(40, 100);
        mGoldText = go->addComponent<Text>(UI, 105);
        mGoldText->setFont(FontManager::getInstance().getByID(FONT_GUI_1));
        mGoldText->setTextSize(50);
        mGoldText->setText("Gold: 1000", true);

        //time text
        go = GameManager::getInstance().instantiateGameObject().get();
        transform = go->getTransform();
        transform->setParent(bgGO->getTransform());
        transform->setLocalPosition(40, 150);
        mTimeText = go->addComponent<Text>(UI, 105);
        mTimeText->setFont(FontManager::getInstance().getByID(FONT_GUI_1));
        mTimeText->setTextSize(50);
        mTimeText->setText("2022-11-03 09:00:10", true);

        //selected Sprite
        go = GameManager::getInstance().instantiateGameObject().get();
        go->setState(components::GameObject::GoState::DISABLED);
        transform = go->getTransform();
        transform->setParent(bgGO->getTransform());
        transform->setPivot(components::PIVOT_BOT_MIDDLE);
        transform->setAnchor(components::ANCHOR_BOT_MIDDLE);
        transform->setLocalPosition(0, -40);
        transform->setSize(30, 30);
        mSelectedSprite = go->addComponent<Sprite>(UI, 101);
        mSelectedSprite->setTexture(TextureManager::getInstance().getByID(TEXTURE_ITEM_FRAME_2));
    }

    core::GoHandle SaveSlotPrefab::getGoHandle() {
        return mRoot;
    }

    components::Text *SaveSlotPrefab::getLevelText() const {
        return mLevelText;
    }

    components::Text *SaveSlotPrefab::getGoldText() const {
        return mGoldText;
    }

    components::Text *SaveSlotPrefab::getTimeText() const {
        return mTimeText;
    }

    components::Sprite *SaveSlotPrefab::getFrame() const {
        return mFrame;
    }

    components::Sprite *SaveSlotPrefab::getSelectedSprite() const {
        return mSelectedSprite;
    }
}
