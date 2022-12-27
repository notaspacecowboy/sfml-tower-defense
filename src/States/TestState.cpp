//
// Created by Zheng Yang on 03/11/22.
//

#include "States.h"
#include "Components.h"
#include "Input/InputManager.h"
#include <Utils/Logger.h>
#include <boost/bind/bind.hpp>
#include <Resource/ResourceManager.h>

using namespace game::components;
using namespace game::renderer;
using namespace game::input;
using namespace game::utils;
using namespace boost::placeholders;
using namespace game::resource;

namespace game::states {
    TestState::TestState(game::states::StateMachine *owner): State(owner) {
        utils::Logger::log("Test State pushed", 5);
    }

    TestState::~TestState() noexcept {
        utils::Logger::log("Test State poped", 5);
        mKeyPressedListener.disconnect();
    }

    void TestState::init() {
        //test entity 1
        auto characterGO = instantiateGO(components::ANCHOR_CENTER, components::PIVOT_CENTER, GameObject::GoState::DISABLED);
        characterGO->getTransform()->setScale(2, 2);
        auto characterSprite = characterGO->addComponent<Sprite>(UI, 0);
        characterGO->getTransform()->setLocalPosition(0, 0);
        auto animator = characterGO->addComponent<CharacterAnimator>();
        animator->setTarget(characterSprite);
        animator->registerState(components::AnimationState::IDLE, 1, true);
        animator->registerState(components::AnimationState::WALK, 2);
        animator->registerState(components::AnimationState::RUN, 3);
        mTestAnimators.emplace_back(animator);

        //test entity 2
        characterGO = instantiateGO(components::ANCHOR_CENTER, components::PIVOT_CENTER, GameObject::GoState::DISABLED);
        characterGO->getTransform()->setScale(2, 2);
        characterSprite = characterGO->addComponent<Sprite>(UI, 0);
        characterGO->getTransform()->setLocalPosition(0, 0);
        animator = characterGO->addComponent<CharacterAnimator>();
        animator->setTarget(characterSprite);
        animator->registerState(components::AnimationState::WALK, 6, true);
        animator->registerState(components::AnimationState::DIE, 5);
        mTestAnimators.emplace_back(animator);

        //test entity tower
        characterGO = instantiateGO(components::ANCHOR_CENTER, components::PIVOT_CENTER, GameObject::GoState::DISABLED);
        characterSprite = characterGO->addComponent<Sprite>(UI, 0);
        characterGO->getTransform()->setLocalPosition(0, 0);
        animator = characterGO->addComponent<CharacterAnimator>();
        animator->setTarget(characterSprite);
        animator->registerState(components::AnimationState::IDLE, 4, true);
        mTestAnimators.emplace_back(animator);

        //test projection
        characterGO = instantiateGO(components::ANCHOR_CENTER, components::PIVOT_CENTER, GameObject::GoState::DISABLED);
        characterSprite = characterGO->addComponent<Sprite>(UI, 0);
        characterGO->getTransform()->setLocalPosition(0, 0);
        animator = characterGO->addComponent<CharacterAnimator>();
        animator->setTarget(characterSprite);
        animator->registerState(components::AnimationState::IDLE, 7, true);
        mTestAnimators.emplace_back(animator);

        auto textGO = instantiateGO(components::ANCHOR_BOT_MIDDLE, components::PIVOT_BOT_MIDDLE);
        textGO->getTransform()->move(0, -200);
        auto text = textGO->addComponent<Text>(UI, 0);
        text->setTextSize(40);
        text->setText("PRESS SPACE KEY TO CHANGE ANIMATION", true);

        textGO = instantiateGO(components::ANCHOR_BOT_MIDDLE, components::PIVOT_BOT_MIDDLE);
        textGO->getTransform()->move(0, -150);
        text = textGO->addComponent<Text>(UI, 0);
        text->setTextSize(40);
        text->setText("PRESS TAB KEY TO SWITCH ENTITY", true);

        textGO = instantiateGO(components::ANCHOR_BOT_MIDDLE, components::PIVOT_BOT_MIDDLE);
        textGO->getTransform()->move(0, -100);
        text = textGO->addComponent<Text>(UI, 0);
        text->setTextSize(40);
        text->setText("PRESS ESC TO RETURN TO MAIN MENU", true);

        mKeyPressedListener = InputManager::getInstance().GameKeyPressedEvent.connect(boost::bind(&TestState::onPressKey, this, _1));

        mCurrentAnimatorIndex = 0;
        mCurrentAnimationClipIndex = 0;
        mTestAnimators[mCurrentAnimatorIndex]->getGameObject().setState(GameObject::GoState::ACTIVE);
        mTestAnimators[mCurrentAnimatorIndex]->getAllStates(mStates);
        mTestAnimators[mCurrentAnimatorIndex]->start();
    }

    void TestState::onPressKey(sf::Keyboard::Key keyCode) {
        if(keyCode == sf::Keyboard::Escape)
        {
            mOwner->pop();
            mOwner->push<MainState>();
            return;
        }

        if(keyCode == sf::Keyboard::Tab) {
            mTestAnimators[mCurrentAnimatorIndex]->getGameObject().setState(GameObject::GoState::DISABLED);
            mCurrentAnimatorIndex = (mCurrentAnimatorIndex + 1) % mTestAnimators.size();
            mCurrentAnimationClipIndex = 0;
            mTestAnimators[mCurrentAnimatorIndex]->getAllStates(mStates);
            mTestAnimators[mCurrentAnimatorIndex]->getGameObject().setState(GameObject::GoState::ACTIVE);
            mTestAnimators[mCurrentAnimatorIndex]->start();
        }

        auto animator = mTestAnimators[mCurrentAnimatorIndex];
        mCurrentAnimationClipIndex = (mCurrentAnimationClipIndex + 1) % mStates.size();
        animator->makeTransition(mStates[mCurrentAnimationClipIndex]);
    }

}
