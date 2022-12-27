//
// Created by Zheng Yang on 21/11/22.
//

#include <States.h>
#include <Core/GameManager.h>
#include <boost/bind/bind.hpp>
#include <functional>
#include <Utils/Logger.h>
#include <Utils/Time.h>
#include <Input/InputManager.h>
#include <Renderer/RenderLayer.h>
#include <Data.h>
#include <math.h>
#include <Components.h>
#include <Prefabs.h>
#include <Resource/ResourceManager.h>

using namespace game::core;
using namespace game::utils;
using namespace boost::placeholders;
using namespace game::input;
using namespace game::data;
using namespace game::renderer;
using namespace game::components;
using namespace game::resource;

namespace game::states {
    PauseState::PauseState(game::states::StateMachine *owner)
    : State(owner) {}

    PauseState::~PauseState() noexcept {
    }

    void PauseState::init() {
        //transparent background that block all raycasts
        auto go = instantiateGO();
        auto transform = go->getTransform();
        transform->matchParent();
        auto shape = go->addComponent<Shape>(sf::Color(0, 0, 0, 122), UI, 100);
        shape->setRaycastable(true);


        //random icon...
        auto iconGO = instantiateGO(components::ANCHOR_CENTER, components::PIVOT_CENTER);
        transform = iconGO->getTransform();
        transform->setScale(0.8, 0.8);
        transform->setLocalPosition(0, -30);
        auto sprite = iconGO->addComponent<Sprite>(UI, 101);
        sprite->setTexture(resource::TextureType::TEXTURE_TELEVISION);
        sprite->setSpriteNativeSize();

        //quit game button
        go = GameManager::getInstance().instantiateGameObject().get();
        transform = go->getTransform();
        transform->setParent(iconGO->getTransform());
        transform->setPivot(components::PIVOT_TOP_RIGHT);
        transform->setAnchor(components::ANCHOR_BOT_LEFT);
        transform->setLocalPosition(-30, 40);
        auto buttonDefine = DataManager::getInstance().get<ButtonDefine>(data::DataType::BUTTON, 3);
        auto button = go->addComponent<Button>(buttonDefine, UI, 102);
        button->getText()->setText("QUIT GAME", true);
        mExitButtonListener = button->onClick.connect(boost::bind(&PauseState::onExitButtonClicked, this));


        //return to main button
        go = GameManager::getInstance().instantiateGameObject().get();
        transform = go->getTransform();
        transform->setParent(iconGO->getTransform());
        transform->setPivot(components::PIVOT_TOP_MIDDLE);
        transform->setAnchor(components::ANCHOR_BOT_MIDDLE);
        transform->setLocalPosition(0, 40);
        button = go->addComponent<Button>(buttonDefine, UI, 102);
        button->getText()->setText("MAIN MENU", true);
        mReturnToMainButtonListener = button->onClick.connect(boost::bind(&PauseState::onReturnToMainButtonClicked, this));


        //return to game button
        go = GameManager::getInstance().instantiateGameObject().get();
        transform = go->getTransform();
        transform->setParent(iconGO->getTransform());
        transform->setPivot(components::PIVOT_TOP_LEFT);
        transform->setAnchor(components::ANCHOR_BOT_RIGHT);
        transform->setLocalPosition(30, 40);

        button = go->addComponent<Button>(buttonDefine, UI, 102);
        button->getText()->setText("RETURN", true);
        mReturnToGameButtonListener = button->onClick.connect(boost::bind(&PauseState::onReturnToGameButtonClicked, this));
    }


    bool PauseState::freezeTime() {
        return true;
    }

    void PauseState::onExitButtonClicked() {
        GameManager::getInstance().terminate();
    }

    void PauseState::onReturnToGameButtonClicked() {
        mOwner->pop();
        mOwner->peak()->enableInput();
    }

    void PauseState::onReturnToMainButtonClicked() {
        mOwner->clear();
        mOwner->push<MainState>();
    }
}
