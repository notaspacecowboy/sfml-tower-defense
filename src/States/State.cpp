//
// Created by Zheng Yang on 19/10/22.
//

#include <States/State.h>
#include <States/StateMachine.h>
#include <Utils/Logger.h>
#include <Core/GameManager.h>

namespace game::states {
    using namespace core;

    State::State(game::states::StateMachine *owner): mOwner(owner) {
        mRoot = GameManager::getInstance().instantiateGameObject();
        auto size = GameManager::getInstance().getRenderer().ReferencedResolution;
        mRoot->getTransform()->setSize(size.x, size.y);
        mRoot->getTransform()->setLocalPosition(0, 0);
    }

    State::State(StateMachine *owner, int rootWidth, int rootHeight) {
        mRoot = GameManager::getInstance().instantiateGameObject();
        mRoot->getTransform()->setSize(rootWidth, rootHeight);
    }

    State::~State() {
        if(mRoot) {
            mRoot->setState(components::GameObject::GoState::MARK_TO_DESTROY);
        }
    }

    components::GameObject* State::instantiateGO(components::Anchor anchor, components::Pivot pivot, components::GameObject::GoState goState) {
        auto go = GameManager::getInstance().instantiateGameObject(goState).get();
        go->getTransform()->setParent(mRoot->getTransform());
        go->getTransform()->setAnchor(anchor);
        go->getTransform()->setPivot(pivot);
        go->getTransform()->setLocalPosition(0, 0);

        return go;
    }

    void State::init() {}

    void State::enableInput() {}

    void State::disableInput() {}

    bool State::freezeTime() {
        return false;
    }


}