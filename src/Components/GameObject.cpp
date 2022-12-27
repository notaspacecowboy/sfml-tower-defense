//
// Created by Zheng Yang on 08/10/22.
//

#include "Components/GameObject.h"
#include "Utils/Logger.h"

namespace game::components {

    GameObject::GameObject(GUID id, GoState state): mID(id),  mState(state), mTransform(nullptr) {

        //all gameobjects are attached with a transform component
        mTransform = addComponent<Transform>();
    }

    GameObject::~GameObject() {
    }

    void GameObject::setState(game::components::GameObject::GoState state) {
        if(mState == state)
            return;

        auto tmp = mState;
        mState = state;
        for(auto &component: mComponents) {
            if(state == GoState::ACTIVE)
                component->onEnable();
            else if(tmp == GoState::ACTIVE)
                component->onDisable();
        }
    }

    void GameObject::tick(float deltaTime) {
        //if gameobject not active, do not tick
        if(mState != GoState::ACTIVE)
            return;

        for(auto &component: mComponents) {
            component->tick(deltaTime);
        }
    }

    GameObject::GoState GameObject::getState() {
        return mState;
    }
} // game::components