//
// Created by Zheng Yang on 06/11/22.
//

#include <States.h>
#include <Components.h>
#include <Resource/ResourceManager.h>
#include <Renderer/RenderLayer.h>
#include <Data.h>
#include <boost/bind/bind.hpp>
#include <Prefabs.h>
#include <Utils/Logger.h>

using namespace game::components;
using namespace game::resource;
using namespace game::renderer;
using namespace game::data;
using namespace game::prefabs;
using namespace boost::placeholders;
using namespace game::utils;

namespace game::states {
    SaveAndLoadState::SaveAndLoadState(StateMachine* owner): State(owner) {
        utils::Logger::log("SaveAndLoad State Pushed", 5);
    }

    SaveAndLoadState::~SaveAndLoadState() noexcept {
        utils::Logger::log("SaveAndLoad State Poped", 5);
        mBackButtonListener.disconnect();
    }

    void SaveAndLoadState::init() {
        DataManager::getInstance().savePlayerAtIndex(DataManager::getInstance().getCurrentPlayerIndex());

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
        mBackButtonListener = button->onClick.connect(boost::bind(&SaveAndLoadState::onBackButtonClick, this));

        //grid
        auto grid = instantiateGO(components::ANCHOR_CENTER, components::PIVOT_CENTER);

        //shop items
        sf::Vector2i gridSize(4, 1);
        sf::Vector2i margin(16, 0);
        sf::Vector2i elementSize(300, 300);
        auto layout = grid->addComponent<GridLayout>(gridSize, margin, elementSize);

        int currentSelectedIndex = DataManager::getInstance().getCurrentPlayerIndex();
        auto &allSaves = DataManager::getInstance().getAllSaveData();
        for(int i = 0; i < allSaves.size(); i++) {
            auto playerData = allSaves[i].get();
            SaveSlotPrefab saveslotPrefab;
            bool selected = (currentSelectedIndex == i);
            auto saveslotGO = saveslotPrefab.getGoHandle().get();
            auto saveslot = saveslotGO->addComponent<SaveSlot>(playerData, saveslotPrefab, i, selected);
            saveslot->onPlayerDataSelected.connect(boost::bind(&SaveAndLoadState::onSaveFileSelected, this, _1));
            layout->addGridElement(saveslotGO->getTransform());
        }
    }

    void SaveAndLoadState::onBackButtonClick() {
        mOwner->pop();
        mOwner->push<MainState>();
    }

    void SaveAndLoadState::onSaveFileSelected(SaveSlot* selected) {
        if(DataManager::getInstance().getCurrentPlayerIndex() == selected->getIndex())
            return;

        DataManager::getInstance().loadPlayerFromIndex(selected->getIndex());
        mOwner->pop();
        mOwner->push<MainState>();
    }
}

