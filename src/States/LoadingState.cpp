//
// Created by ZHeng Yang on 01/11/22.
//

#include <States/LoadingState.h>
#include "Components/Drawables/Sprite.h"
#include "Components/Animators/RotateAnimator.h"
#include <Resource/ResourceManager.h>
#include <Core/GameManager.h>
#include <Utils/Logger.h>

namespace game::states {
    using namespace core;
    using namespace resource;
    using namespace components;
    using namespace renderer;

    LoadingState::LoadingState(StateMachine *owner): State(owner) {
        utils::Logger::log("Loading State Pushed", 5);
    }

    LoadingState::~LoadingState() noexcept {
        utils::Logger::log("Loading State Poped", 5);
    }

    void LoadingState::init() {
        auto backgroundGO = instantiateGO();
        backgroundGO->getTransform()->matchParent();
        auto background = backgroundGO->addComponent<Shape>(sf::Color::Black, UI, 10000);


        auto loadingSpin = instantiateGO();
        loadingSpin->getTransform()->setAnchor(components::ANCHOR_BOT_RIGHT);
        loadingSpin->getTransform()->setPivot(components::PIVOT_CENTER);
        loadingSpin->getTransform()->setLocalPosition(-100, -100);

        auto loadingSpinner = loadingSpin->addComponent<Sprite>(UI, 10001);
        loadingSpinner->setTexture(TextureManager::getInstance().getByID(TEXTURE_LOADING_SPIN));
        loadingSpinner->setSpriteNativeSize();
        auto loadingSpinAnimator = loadingSpin->addComponent<RotateAnimator>(0, 360, 1.5f, true, false);
        loadingSpinAnimator->setTarget(loadingSpinner);
        loadingSpinAnimator->start();
    }
}
