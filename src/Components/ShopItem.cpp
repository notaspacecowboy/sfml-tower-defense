//
// Created by Zheng Yang on 05/11/22.
//

#include <Components.h>
#include <Data.h>
#include <Resource/ResourceManager.h>

using namespace game::data;
using namespace game::resource;

namespace game::components {
    ShopItem::ShopItem(GameObject &owner, const data::ShopItemDefine *data, game::components::Sprite *frame, game::components::Sprite *icon, game::components::Text *text)
    : Component(owner)
    , mData(data)
    , mIcon(icon)
    , mClickable(frame)
    , mName(text) {}

    void ShopItem::onEnable() {
        mIcon->setTexture(TextureManager::getInstance().getByID(mData->iconTextureID));
        mName->setText(mData->name);
        mName->fitText();

        mClickable->setRaycastable(true);
    }

    void ShopItem::onDisable() {
        onItemSelected.disconnect_all_slots();
        mClickable->setRaycastable(false);
    }

    void ShopItem::onPointerClick() {
        if(!onItemSelected.empty())
            onItemSelected(mData);
    }
}