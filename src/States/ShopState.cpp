//
// Created by Zheng Yang on 05/11/22.
//

#include <Utils/Logger.h>
#include <Core/GameManager.h>
#include <Resource/ResourceManager.h>
#include <boost/bind/bind.hpp>
#include <functional>
#include <Resource/Localization.h>
#include <Input/InputManager.h>
#include <Audio.h>
#include <States.h>
#include <Components.h>
#include <Data.h>
#include <Prefabs.h>

using namespace game::core;
using namespace game::renderer;
using namespace game::components;
using namespace game::data;
using namespace game::resource;
using namespace game::input;
using namespace boost::placeholders;
using namespace game::audio;
using namespace game::prefabs;

namespace game::states {
    ShopState::ShopState(game::states::StateMachine *owner)
    : State(owner) {
        utils::Logger::log("Shop State Pushed", 5);
        mPlayerState = GameManager::getInstance().getPlayerState();
    }

    ShopState::~ShopState() {
        utils::Logger::log("Shop State Poped", 5);
        mBuyButtonListener.disconnect();
        mBackButtonListener.disconnect();
    }

    void ShopState::init() {
        auto go = instantiateGO(components::ANCHOR_TOP_LEFT, components::PIVOT_TOP_LEFT);
        go->getTransform()->matchParent();
        auto bg = go->addComponent<Sprite>(UI, 0);
        bg->setTexture(TextureManager::getInstance().getByID(TEXTURE_BG_MAIN));

        auto backgroundGO = instantiateGO(components::ANCHOR_TOP_LEFT, components::PIVOT_TOP_LEFT);
        backgroundGO->getTransform()->setSize(mRoot->getTransform()->getSize().x, 100);
        auto shape = backgroundGO->addComponent<Shape>(sf::Color::Black, UI, 1);
        shape->setAlpha(0.3);

        //back to main menu button
        auto buttonDefine = DataManager::getInstance().get<ButtonDefine>(DataType::BUTTON, 2);
        auto buttonGO = instantiateGO(components::ANCHOR_TOP_RIGHT, components::PIVOT_TOP_RIGHT);
        buttonGO->getTransform()->setLocalPosition(-200, 20);
        auto button = buttonGO->addComponent<Button>(buttonDefine, UI, 10);
        button->getText()->setText("BACK", true);
        mBackButtonListener = button->onClick.connect(boost::bind(&ShopState::onBackButtonClick, this));

        //current golds text
        go = instantiateGO(components::ANCHOR_CENTER, components::PIVOT_CENTER);
        auto transform = go->getTransform();
        transform->setParent(backgroundGO->getTransform());
        transform->setLocalPosition(0, 0);
        mCurrentGold = go->addComponent<Text>(UI, 20);
        mCurrentGold->setFont(FontManager::getInstance().getByID(FONT_GUI_1));
        mCurrentGold->setTextSize(60);
        mCurrentGold->setText("$" + std::to_string(mPlayerState->getCurrentGold()), true);


        auto panel = instantiateGO(components::ANCHOR_BOT_MIDDLE, components::PIVOT_BOT_MIDDLE);

        //panel frame
        panel->getTransform()->setSize(500, 580);
        sf::Color color(75, 79, 116, 255);
        panel->addComponent<Shape>(color, UI, 1);

        //shop text
        auto textGO = instantiateGO(components::ANCHOR_TOP_MIDDLE, components::PIVOT_TOP_MIDDLE);
        textGO->getTransform()->setParent(panel->getTransform());
        textGO->getTransform()->setLocalPosition(0, 30);
        auto text = textGO->addComponent<Text>(UI, 10);
        text->setFont(FontManager::getInstance().getByID(FONT_GUI_1));
        text->setTextSize(70);
        text->setText("PowerUp Selection", true);

        //grid
        auto grid = instantiateGO(components::ANCHOR_CENTER, components::PIVOT_CENTER);
        grid->getTransform()->setParent(panel->getTransform());
        grid->getTransform()->setLocalPosition(0, -20);

        //shop items
        sf::Vector2i gridSize(4, 3);
        sf::Vector2i margin(20, 20);
        sf::Vector2i elementSize(100, 100);
        auto layout = grid->addComponent<GridLayout>(gridSize, margin, elementSize);

        auto &allShopItems = DataManager::getInstance().getAll(data::DataType::SHOP_ITEM);
        for(const auto &[key, value]: allShopItems) {
            auto data = static_cast<ShopItemDefine*>(value.get());
            ShopItemPrefab prefab;
            auto shopItemGO = prefab.getGoHandle().get();
            layout->addGridElement(shopItemGO->getTransform());
            auto item = shopItemGO->addComponent<ShopItem>(data, prefab.getFrame(), prefab.getIcon(), prefab.getText());
            item->onItemSelected.connect(boost::bind(&ShopState::onItemSelect, this, _1));
        }

        //currently selected
        auto selectedGO = instantiateGO(ANCHOR_BOT_MIDDLE, PIVOT_BOT_MIDDLE);
        transform = selectedGO->getTransform();
        transform->setParent(panel->getTransform());
        transform->setLocalPosition(0, 0);
        transform->setSize(panel->getTransform()->getSize().x, 100);
        sf::Color selectedColor(173, 154, 153, 255);
        selectedGO->addComponent<Shape>(selectedColor, UI, 10);

        //selected name
        go = instantiateGO(components::ANCHOR_TOP_LEFT, components::PIVOT_TOP_LEFT);
        transform = go->getTransform();
        transform->setParent(selectedGO->getTransform());
        transform->move(40, 10);
        mCurrentName = go->addComponent<Text>(UI, 20);
        mCurrentName->setFont(FontManager::getInstance().getByID(FONT_GUI_1));
        mCurrentName->setTextSize(30);

        //selected icon
        go = instantiateGO(components::ANCHOR_BOT_LEFT, components::PIVOT_BOT_LEFT);
        transform = go->getTransform();
        transform->setParent(selectedGO->getTransform());
        transform->setLocalPosition(40, -10);
        transform->setSize(50, 50);
        mCurrentIcon = go->addComponent<Sprite>(UI, 20);

        //selected description
        go = instantiateGO(components::ANCHOR_TOP_LEFT, components::PIVOT_TOP_LEFT);
        transform = go->getTransform();
        transform->setParent(selectedGO->getTransform());
        transform->setLocalPosition(120, 20);
        transform->setSize(150, 200);
        mCurrentDescription = go->addComponent<Text>(UI, 20);
        mCurrentDescription->setFont(FontManager::getInstance().getByID(FONT_GUI_1));
        mCurrentDescription->setTextSize(25);

        //selected cost
        go = instantiateGO(components::ANCHOR_TOP_RIGHT, components::PIVOT_TOP_RIGHT);
        transform = go->getTransform();
        transform->setParent(selectedGO->getTransform());
        transform->setLocalPosition(-40, 10);
        mCurrentCost = go->addComponent<Text>(UI, 20);
        mCurrentCost->setFont(FontManager::getInstance().getByID(FONT_GUI_1));
        mCurrentCost->setTextSize(40);

        //item owned text
        go = instantiateGO(components::ANCHOR_MIDDLE_RIGHT, components::PIVOT_MIDDLE_RIGHT);
        transform = go->getTransform();
        transform->setParent(selectedGO->getTransform());
        transform->setLocalPosition(-40, 0);
        mItemOwned = go->addComponent<Text>(UI, 20);
        mItemOwned->setFont(FontManager::getInstance().getByID(FONT_GUI_1));
        mItemOwned->setTextSize(50);
        mItemOwned->setColor(sf::Color::Red);
        mItemOwned->setText("*OWNED", true);

        //not enough gold text
        go = instantiateGO(components::ANCHOR_MIDDLE_RIGHT, components::PIVOT_MIDDLE_RIGHT);
        transform = go->getTransform();
        transform->setParent(selectedGO->getTransform());
        transform->setLocalPosition(-20, -5);
        transform->setSize(100, 50);
        mNotEnoughGold = go->addComponent<Text>(UI, 20);
        mNotEnoughGold->setFont(FontManager::getInstance().getByID(FONT_GUI_1));
        mNotEnoughGold->setTextSize(50);
        mNotEnoughGold->setColor(sf::Color::Red);
        mNotEnoughGold->setText("Gold Not Enough!");

        //buy button
        buttonDefine = DataManager::getInstance().get<ButtonDefine>(DataType::BUTTON, 3);
        go = instantiateGO(components::ANCHOR_BOT_RIGHT, components::PIVOT_BOT_RIGHT);
        transform = go->getTransform();
        transform->setParent(selectedGO->getTransform());
        go->getTransform()->setLocalPosition(-10, -10);
        mPurchaseButton = go->addComponent<Button>(buttonDefine, UI, 20);
        mPurchaseButton->getText()->setTextSize(40);
        mPurchaseButton->getText()->setText("Buy", true);
        transform->setScale(1, 1);
        mBuyButtonListener = mPurchaseButton->onClick.connect(boost::bind(&ShopState::onBuyButtonClick, this));

        mCurrentSelected = static_cast<const ShopItemDefine*>(allShopItems[1].get());
        mCurrentName->setText(mCurrentSelected->name, true);
        mCurrentIcon->setTexture(TextureManager::getInstance().getByID(mCurrentSelected->iconTextureID));
        mCurrentDescription->setText(mCurrentSelected->description);
        mCurrentCost->setText(std::to_string(mCurrentSelected->cost), true);

        checkValidity();

    }

    void ShopState::onItemSelect(const data::ShopItemDefine *data) {
        if(mCurrentSelected == data)
            return;

        mCurrentSelected = data;
        mCurrentName->setText(mCurrentSelected->name, true);
        mCurrentIcon->setTexture(TextureManager::getInstance().getByID(mCurrentSelected->iconTextureID));
        mCurrentDescription->setText(mCurrentSelected->description);
        mCurrentCost->setText("$" + std::to_string(mCurrentSelected->cost), true);

        checkValidity();
    }

    void ShopState::onBuyButtonClick() {
        if(mPlayerState->getCurrentGold() < mCurrentSelected->cost) {
            utils::Logger::log("player does not have enough gold, purchase failed");
            return;
        }

        mPlayerState->changeGold(-mCurrentSelected->cost);
        mPlayerState->addPowerUp(mCurrentSelected->tID);
        mCurrentGold->setText("$" + std::to_string(mPlayerState->getCurrentGold()), true);

        checkValidity();
    }

    void ShopState::onBackButtonClick() {
        mOwner->pop();
        mOwner->push<MainState>();
    }

    void ShopState::checkValidity() {
        auto &allPowerUps = mPlayerState->getCurrentPowerUps();
        auto find = std::find(allPowerUps.begin(), allPowerUps.end(), mCurrentSelected->tID);
        if(find != allPowerUps.end()) {
            mItemOwned->getGameObject().setState(components::GameObject::GoState::ACTIVE);
            mNotEnoughGold->getGameObject().setState(components::GameObject::GoState::DISABLED);
            mCurrentCost->getGameObject().setState(components::GameObject::GoState::DISABLED);
            mPurchaseButton->getSprite()->getGameObject().setState(components::GameObject::GoState::DISABLED);
            mPurchaseButton->getText()->getGameObject().setState(components::GameObject::GoState::DISABLED);
        }
        else {
            mItemOwned->getGameObject().setState(components::GameObject::GoState::DISABLED);

            if(mPlayerState->getCurrentGold() < mCurrentSelected->cost) {
                mNotEnoughGold->getGameObject().setState(components::GameObject::GoState::ACTIVE);
                mCurrentCost->getGameObject().setState(components::GameObject::GoState::DISABLED);
                mPurchaseButton->getSprite()->getGameObject().setState(components::GameObject::GoState::DISABLED);
                mPurchaseButton->getText()->getGameObject().setState(components::GameObject::GoState::DISABLED);
            }
            else {
                mNotEnoughGold->getGameObject().setState(components::GameObject::GoState::DISABLED);
                mCurrentCost->getGameObject().setState(components::GameObject::GoState::ACTIVE);
                mPurchaseButton->getSprite()->getGameObject().setState(components::GameObject::GoState::ACTIVE);
                mPurchaseButton->getText()->getGameObject().setState(components::GameObject::GoState::ACTIVE);
            }
        }
    }
}
