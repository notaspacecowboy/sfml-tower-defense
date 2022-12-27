//
// Created by Zheng Yang on 22/11/22.
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
    GameOverState::GameOverState(game::states::StateMachine *owner)
            : State(owner) {}

    GameOverState::~GameOverState() noexcept {
    }

    void GameOverState::init() {
        //transparent background that block all raycasts
        auto go = instantiateGO();
        auto transform = go->getTransform();
        transform->matchParent();
        auto shape = go->addComponent<Shape>(sf::Color(0, 0, 0, 122), UI, 100);
        shape->setRaycastable(true);


        //random icon...
        auto textGO = instantiateGO(components::ANCHOR_CENTER, components::PIVOT_CENTER);
        transform = textGO->getTransform();
        transform->setSize(600, 200);
        transform->setLocalPosition(0, -30);
        auto text = textGO->addComponent<Text>(UI, 101);
        text->setColor(sf::Color::Red);
        text->setTextSize(80);
        text->setText("YOU LOST!", true);


        //return to main button
        go = GameManager::getInstance().instantiateGameObject().get();
        transform = go->getTransform();
        transform->setParent(textGO->getTransform());
        transform->setPivot(components::PIVOT_TOP_MIDDLE);
        transform->setAnchor(components::ANCHOR_BOT_MIDDLE);
        transform->setLocalPosition(0, 40);
        auto buttonDefine = DataManager::getInstance().get<ButtonDefine>(data::DataType::BUTTON, 3);
        auto button = go->addComponent<Button>(buttonDefine, UI, 102);
        button->getText()->setText("MAIN MENU", true);
        mReturnToMainButtonListener = button->onClick.connect(boost::bind(&GameOverState::onReturnToMainButtonClicked, this));
    }


    bool GameOverState::freezeTime() {
        return true;
    }

    void GameOverState::onReturnToMainButtonClicked() {
        resetPlayer();

        mOwner->clear();
        mOwner->push<MainState>();
    }

    void GameOverState::resetPlayer() {
        auto playerState = GameManager::getInstance().getPlayerState();

        //we only reset their game level progress
        playerState->setGameLevel(0);
    }
}

