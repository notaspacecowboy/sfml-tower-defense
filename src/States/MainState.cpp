//
// Created by Zheng Yang on 02/11/22.
//

#include <Utils/Logger.h>
#include <Core/GameManager.h>
#include <Data/DataManager.h>
#include <Resource/ResourceManager.h>
#include <boost/bind/bind.hpp>
#include <functional>
#include <Resource/Localization.h>
#include <Input/InputManager.h>
#include <boost/bind/bind.hpp>
#include <Components.h>
#include <Audio.h>
#include <States.h>

using namespace game::core;
using namespace game::renderer;
using namespace game::components;
using namespace game::data;
using namespace game::resource;
using namespace game::input;
using namespace game::audio;
using namespace boost::placeholders;


namespace game::states {
    MainState::MainState(game::states::StateMachine *owner): State(owner) {
        utils::Logger::log("Main State Pushed", 5);
    }

    MainState::~MainState() noexcept {
        utils::Logger::log("Main State Poped", 5);
        mStartButtonListener.disconnect();
        mQuitButtonListener.disconnect();
        mOptionButtonListener.disconnect();
        mShopButtonListener.disconnect();
        mSaveAndLoadButtonListener.disconnect();
        mTestButtonListener.disconnect();
    }

    void MainState::init() {
        auto backgroundGO = instantiateGO(components::ANCHOR_TOP_LEFT, components::PIVOT_TOP_LEFT);
        backgroundGO->getTransform()->matchParent();
        auto bg = backgroundGO->addComponent<Sprite>(UI, 0);
        bg->setTexture(TextureManager::getInstance().getByID(TEXTURE_BG_MAIN));

        utils::Logger::log(bg->getGameObject().getTransform()->getWorldPosition(), 5);

        auto fadeInAnimator = backgroundGO->addComponent<FadeInOutAnimator>(0, 1, 1, false, false);
        fadeInAnimator->addTarget(bg);

        auto shapeGO = instantiateGO(components::ANCHOR_TOP_LEFT, components::PIVOT_TOP_LEFT);
        shapeGO->getTransform()->setSize(mRoot->getTransform()->getSize().x, 80);
        auto shape = shapeGO->addComponent<Shape>(sf::Color::Black, UI, 1);
        shape->setAlpha(0.3);


        //quit button button
        auto buttonDefine = DataManager::getInstance().get<ButtonDefine>(DataType::BUTTON, 2);
        auto buttonGO = instantiateGO(components::ANCHOR_TOP_MIDDLE, components::PIVOT_TOP_RIGHT);
        buttonGO->getTransform()->move(-200, 0);
        auto button = buttonGO->addComponent<Button>(buttonDefine, UI, 2);
        button->getText()->setText("QUIT", true);
        mQuitButtonListener = button->onClick.connect(boost::bind(&MainState::onQuitButtonClicked, this));
        fadeInAnimator->addTarget(button->getText());
        fadeInAnimator->addTarget(button->getSprite());

        //option button
        buttonDefine = DataManager::getInstance().get<ButtonDefine>(DataType::BUTTON, 2);
        buttonGO = instantiateGO(components::ANCHOR_TOP_MIDDLE, components::PIVOT_TOP_LEFT);
        buttonGO->getTransform()->move(200, 0);
        button = buttonGO->addComponent<Button>(buttonDefine, UI, 2);
        button->getText()->setText("OPTION", true);
        mOptionButtonListener = button->onClick.connect(boost::bind(&MainState::onOptionButtonClicked, this));
        fadeInAnimator->addTarget(button->getText());
        fadeInAnimator->addTarget(button->getSprite());

        //start button
        buttonDefine = DataManager::getInstance().get<ButtonDefine>(DataType::BUTTON, 3);
        buttonGO = instantiateGO(components::ANCHOR_CENTER, components::PIVOT_BOT_MIDDLE);
        buttonGO->getTransform()->move(0, 100);
        button = buttonGO->addComponent<Button>(buttonDefine, UI, 2);
        button->getText()->setText("START", true);
        mStartButtonListener = button->onClick.connect(boost::bind(&MainState::onStartButtonClicked, this));
        fadeInAnimator->addTarget(button->getText());
        fadeInAnimator->addTarget(button->getSprite());

        //shop button
        buttonDefine = DataManager::getInstance().get<ButtonDefine>(DataType::BUTTON, 1);
        buttonGO = instantiateGO(components::ANCHOR_CENTER, components::PIVOT_CENTER);
        buttonGO->getTransform()->move(0, 200);
        button = buttonGO->addComponent<Button>(buttonDefine, UI, 2);
        button->getText()->setText("SHOP", true);
        mShopButtonListener = button->onClick.connect(boost::bind(&MainState::onShopButtonClicked, this));
        fadeInAnimator->addTarget(button->getText());
        fadeInAnimator->addTarget(button->getSprite());

        //load & save button
        buttonDefine = DataManager::getInstance().get<ButtonDefine>(DataType::BUTTON, 3);
        buttonGO = instantiateGO(components::ANCHOR_CENTER, components::PIVOT_MIDDLE_RIGHT);
        buttonGO->getTransform()->move(-200, 200);
        button = buttonGO->addComponent<Button>(buttonDefine, UI, 2);
        button->getText()->setText("LOAD", true);
        mSaveAndLoadButtonListener = button->onClick.connect(boost::bind(&MainState::onSaveAndLoadButtonClicked, this));
        fadeInAnimator->addTarget(button->getText());
        fadeInAnimator->addTarget(button->getSprite());

        //test button
        buttonDefine = DataManager::getInstance().get<ButtonDefine>(DataType::BUTTON, 3);
        buttonGO = instantiateGO(components::ANCHOR_CENTER, components::PIVOT_MIDDLE_LEFT);
        buttonGO->getTransform()->move(200, 200);
        button = buttonGO->addComponent<Button>(buttonDefine, UI, 2);
        button->getText()->setText("TEST", true);
        mTestButtonListener = button->onClick.connect(boost::bind(&MainState::onTestButtonClicked, this));
        fadeInAnimator->addTarget(button->getText());
        fadeInAnimator->addTarget(button->getSprite());

        fadeInAnimator->onAnimationComplete.connect(boost::bind(&MainState::onFadeIn, this));
        fadeInAnimator->start();

        MusicManager::getInstance().play(MusicType::MUSIC_MAIN);
        MusicManager::getInstance().setVolumn(100);
    }

    void MainState::onFadeIn() {
        mFadeInComplete = true;
    }

    void MainState::onSaveAndLoadButtonClicked() {
        if(!mFadeInComplete)
            return;

        MusicManager::getInstance().stop();
        mOwner->pop();
        mOwner->push<SaveAndLoadState>();
    }

    void MainState::onTestButtonClicked() {
        if(!mFadeInComplete)
            return;

        MusicManager::getInstance().stop();
        mOwner->pop();
        mOwner->push<TestState>();
    }

    void MainState::onOptionButtonClicked() {
        if(!mFadeInComplete)
            return;
        //mOwner->pop();
    }

    void MainState::onQuitButtonClicked() {
        mOwner->pop();
    }

    void MainState::onShopButtonClicked() {
        if(!mFadeInComplete)
            return;

        MusicManager::getInstance().stop();
        mOwner->pop();
        mOwner->push<ShopState>();
    }

    void MainState::onStartButtonClicked() {
        if(!mFadeInComplete)
            return;

        MusicManager::getInstance().stop();
        mOwner->pop();
        mOwner->push<GameState>();
    }
}
