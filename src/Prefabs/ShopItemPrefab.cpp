//
// Created by Zheng Yang on 05/11/22.
//

#include <Prefabs.h>
#include <Components.h>
#include <Core/GameManager.h>
#include <Resource/ResourceManager.h>

using namespace game::components;
using namespace game::core;
using namespace game::resource;

namespace game::prefabs {
    ShopItemPrefab::ShopItemPrefab() {
        mRoot = GameManager::getInstance().instantiateGameObject();
        auto go = mRoot.get();
        go->getTransform()->setSize(100, 100);

        mFrame = go->addComponent<Sprite>(renderer::UI, 105);
        mFrame->setTexture(TextureManager::getInstance().getByID(TEXTURE_ITEM_FRAME_1));

        auto bgGO = GameManager::getInstance().instantiateGameObject().get();
        bgGO->getTransform()->setParent(go->getTransform());
        bgGO->getTransform()->setPivot(components::PIVOT_CENTER);
        bgGO->getTransform()->setAnchor(components::ANCHOR_CENTER);

        bgGO->getTransform()->setLocalPosition(0, 0);
        bgGO->getTransform()->setSize(90, 90);
        sf::Color bgColor(173, 154, 153, 255);
        bgGO->addComponent<Shape>(bgColor, renderer::UI, 101);

        auto iconGO  = GameManager::getInstance().instantiateGameObject().get();
        iconGO->getTransform()->setParent(go->getTransform());
        iconGO->getTransform()->setPivot(components::PIVOT_BOT_MIDDLE);
        iconGO->getTransform()->setAnchor(components::ANCHOR_BOT_MIDDLE);
        iconGO->getTransform()->setSize(50, 50);
        iconGO->getTransform()->setLocalPosition(0, -10);
        mIcon = iconGO->addComponent<Sprite>(renderer::UI, 102);

        auto nameGO = GameManager::getInstance().instantiateGameObject().get();
        nameGO->getTransform()->setParent(go->getTransform());
        nameGO->getTransform()->setPivot(components::PIVOT_TOP_MIDDLE);
        nameGO->getTransform()->setAnchor(components::ANCHOR_TOP_MIDDLE);
        nameGO->getTransform()->setLocalPosition(0, 10);
        nameGO->getTransform()->setSize(go->getTransform()->getSize().x, 40);
        mName = nameGO->addComponent<Text>(renderer::UI, 102);
        mName->setFont(FontManager::getInstance().getByID(FONT_GUI_1));
        mName->setTextSize(30);
    }

    core::GoHandle ShopItemPrefab::getGoHandle() {
        return mRoot;
    }

    components::Text *ShopItemPrefab::getText() const {
        return mName;
    }

    components::Sprite *ShopItemPrefab::getIcon() const {
        return mIcon;
    }

    components::Sprite *ShopItemPrefab::getFrame() const {
        return mFrame;
    }
}
