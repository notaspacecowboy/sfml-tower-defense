//
// Created by Zheng Yang on 16/11/22.
//

#include <Prefabs.h>
#include <Core/GameManager.h>
#include <Components.h>
#include <Resource/ResourceManager.h>
#include <Renderer/RenderLayer.h>
#include <Data.h>
#include <Utils/Logger.h>

using namespace game::core;
using namespace game::components;
using namespace game::resource;
using namespace game::renderer;
using namespace game::data;
using namespace game::utils;


namespace game::prefabs {
    PlayerHudPrefab::PlayerHudPrefab() {
        mRoot = GameManager::getInstance().instantiateGameObject();
        auto rootGO = mRoot.get();
        auto transform = rootGO->getTransform();
        auto referenceResolution = GameManager::getInstance().getRenderer().ReferencedResolution;
        transform->setSize(referenceResolution.x, referenceResolution.y);

        //top left frame
        mTopLeftGO = GameManager::getInstance().instantiateGameObject().get();
        transform = mTopLeftGO->getTransform();
        transform->setParent(rootGO->getTransform());
        transform->setLocalPosition(40, 40);
        transform->setSize(450, 60);
        mTopLeftGO->addComponent<Shape>(sf::Color(0, 0, 0, 100), UI, 0);

        //hp icon
        auto go = GameManager::getInstance().instantiateGameObject().get();
        transform = go->getTransform();
        transform->setParent(mTopLeftGO->getTransform());
        transform->setLocalPosition(20, 10);
        transform->setScale(0.3, 0.3);
        auto sprite = go->addComponent<Sprite>(UI, 1);
        sprite->setTexture(TEXTURE_ICON_POTION_RED);
        sprite->setSpriteNativeSize();

        //hp text
        auto textGo = GameManager::getInstance().instantiateGameObject().get();
        transform = textGo->getTransform();
        transform->setParent(go->getTransform());
        transform->setAnchor(components::ANCHOR_TOP_RIGHT);
        transform->setLocalPosition(10, 10);
        mHpText = textGo->addComponent<Text>(UI, 1);
        mHpText->setFont(FONT_GUI_1);
        mHpText->setTextSize(60);
        mHpText->setText("20", true);



        //point icon
        go = GameManager::getInstance().instantiateGameObject().get();
        transform = go->getTransform();
        transform->setParent(textGo->getTransform());
        transform->setAnchor(ANCHOR_TOP_RIGHT);
        transform->setLocalPosition(30, -10);
        transform->setScale(0.3, 0.3);
        sprite = go->addComponent<Sprite>(UI, 1);
        sprite->setTexture(TEXTURE_ICON_POINT);
        sprite->setSpriteNativeSize();

        //money text
        textGo = GameManager::getInstance().instantiateGameObject().get();
        transform = textGo->getTransform();
        transform->setParent(go->getTransform());
        transform->setAnchor(components::ANCHOR_TOP_RIGHT);
        transform->setLocalPosition(10, 10);
        mPointText = textGo->addComponent<Text>(UI, 1);
        mPointText->setFont(FONT_GUI_1);
        mPointText->setTextSize(60);
        mPointText->setText("50000", true);

        //time icon
        go = GameManager::getInstance().instantiateGameObject().get();
        transform = go->getTransform();
        transform->setParent(textGo->getTransform());
        transform->setAnchor(ANCHOR_TOP_RIGHT);
        transform->setLocalPosition(30, -10);
        transform->setScale(0.3, 0.3);
        sprite = go->addComponent<Sprite>(UI, 1);
        sprite->setTexture(TEXTURE_ICON_STOPWATCH);
        sprite->setSpriteNativeSize();

        //time text
        textGo = GameManager::getInstance().instantiateGameObject().get();
        transform = textGo->getTransform();
        transform->setParent(go->getTransform());
        transform->setAnchor(components::ANCHOR_TOP_RIGHT);
        transform->setLocalPosition(10, 10);
        mTimeElapsedText = textGo->addComponent<Text>(UI, 1);
        mTimeElapsedText->setFont(FONT_GUI_1);
        mTimeElapsedText->setTextSize(60);
        mTimeElapsedText->setText("00:00", true);

        reCalculateBgSize();
    }

    core::GoHandle PlayerHudPrefab::getGoHandle() {
        return mRoot;
    }

    void PlayerHudPrefab::setHP(int newHP) {
        mHpText->setText(std::to_string(newHP), true);
        reCalculateBgSize();
    }

    void PlayerHudPrefab::setPoint(int newMoney) {
        mPointText->setText(std::to_string(newMoney), true);
        reCalculateBgSize();
    }

    void PlayerHudPrefab::setTimeElapsed(int timeInSeconds) {
        int minutes = timeInSeconds / 60;
        int seconds = timeInSeconds % 60;
        std::string timeStr = "";
        timeStr += (minutes < 10 ? "0" + std::to_string(minutes) : std::to_string(minutes));
        timeStr += ":";
        timeStr += (seconds < 10 ? "0" + std::to_string(seconds) : std::to_string(seconds));

        mTimeElapsedText->setText(timeStr, true);
        reCalculateBgSize();
    }

    void PlayerHudPrefab::reCalculateBgSize() {
        auto worldPos = mTopLeftGO->getTransform()->getWorldPosition();
        auto rightMostWorldPos = mTimeElapsedText->getGameObject().getTransform()->getWorldPosition();
        auto size = mTimeElapsedText->getGameObject().getTransform()->getSize();
        rightMostWorldPos.x += size.x + 20;
        auto newSizeX = rightMostWorldPos.x - worldPos.x;
        auto oldSize = mTopLeftGO->getTransform()->getSize();
        mTopLeftGO->getTransform()->setSize(newSizeX, oldSize.y);
    }

}