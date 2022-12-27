//
// Created by Zheng Yang on 25/11/22.
//


#include <Prefabs.h>
#include <Components.h>
#include <Core/GameManager.h>
#include <Resource/ResourceManager.h>
#include <Data.h>

using namespace game::components;
using namespace game::core;
using namespace game::resource;
using namespace game::data;

namespace game::prefabs {
    TowerShopItemPrefab::TowerShopItemPrefab() {
        mRoot = GameManager::getInstance().instantiateGameObject();
        auto go = mRoot.get();
        go->getTransform()->setScale(2, 2);

        mIcon = go->addComponent<Sprite>(renderer::ENTITY, 105);
        mIcon->setTexture(TextureManager::getInstance().getByID(TEXTURE_ICON_SHEET));
        mIcon->setTextureRect(259, 195, 26, 26);
        mIcon->setSpriteNativeSize();

        go = GameManager::getInstance().instantiateGameObject().get();
        auto transform = go->getTransform();
        transform->setParent(mRoot.get()->getTransform());
        transform->setAnchor(components::ANCHOR_TOP_MIDDLE);
        transform->setPivot(components::PIVOT_BOT_MIDDLE);
        transform->setLocalPosition(0, -15);
        auto text = go->addComponent<Text>(renderer::ENTITY, 105);
        text->setTextSize(45);
        text->setColor(sf::Color::Red);

        auto data = DataManager::getInstance().get<TowerDefine>(data::DataType::TOWER, 1);
        text->setText("$" + std::to_string(data->cost), true);
    }

    core::GoHandle TowerShopItemPrefab::getGoHandle() {
        return mRoot;
    }

    components::Sprite *TowerShopItemPrefab::getIcon() const {
        return mIcon;
    }
}
