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
using namespace game::prefabs;

namespace game::components {
    SaveSlot::SaveSlot(game::components::GameObject &owner, const data::PlayerData *data,prefabs::SaveSlotPrefab prefab, int index, bool isSelected)
    : Component(owner)
    , mPrefab(prefab)
    , mData(data)
    , mIndex(index)
    , mIsSelected(isSelected) {}

    void SaveSlot::onEnable() {
        mPrefab.getFrame()->setRaycastable(true);

        if(mData == nullptr) {
            mPrefab.getLevelText()->setText("EMPTY", true);
            mPrefab.getGoldText()->setText("");
            mPrefab.getTimeText()->setText("");
            return;
        }

        mPrefab.getLevelText()->setText("Level: " + std::to_string(mData->gameLevel));
        mPrefab.getGoldText()->setText("Gold: " + std::to_string(mData->currentGold));
        mPrefab.getTimeText()->setText(mData->saveTime);
        if(mIsSelected)
            mPrefab.getSelectedSprite()->getGameObject().setState(GameObject::GoState::ACTIVE);
    }

    void SaveSlot::onDisable() {
        mPrefab.getFrame()->setRaycastable(false);
        onPlayerDataSelected.disconnect_all_slots();
    }

    void SaveSlot::onPointerClick() {
        if(!onPlayerDataSelected.empty())
            onPlayerDataSelected(this);
    }

    int SaveSlot::getIndex() const {
        return mIndex;
    }
}
