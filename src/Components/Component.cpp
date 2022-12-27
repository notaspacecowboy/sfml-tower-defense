//
// Created by Zheng Yang on 08/10/22.
//

#include <Components/GameObject.h>

namespace game::components {
    Component::Component(game::components::GameObject &owner): mOwner(owner) {
    }

    GameObject &Component::getGameObject() {
        return mOwner;
    }

    GUID Component::getGUID() const {
        return mOwner.getGUID();
    }

    void Component::onEnable() {}

    void Component::tick(float deltaTime) {}

    void Component::onDisable() {}

} // components