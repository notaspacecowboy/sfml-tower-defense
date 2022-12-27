//
// Created by Zheng Yang on 20/10/22.
//

#include <Renderer/GameRenderer.h>
#include "Components/Drawables/RenderComponent.h"
#include <Utils/Logger.h>
#include <Input/InputManager.h>
#include <boost/bind/bind.hpp>
#include <Components.h>
#include <Resource/ResourceManager.h>

namespace game::renderer {
    using namespace input;
    using namespace boost::placeholders;
    using namespace components;

    const sf::Vector2i GameRenderer::ReferencedResolution(1280, 720);

    GameRenderer::GameRenderer(sf::RenderWindow &window, sf::View &uiView, sf::View &gameView)
        : mWindow(window)
        , mUICamera(uiView)
        , mGameCamera(gameView) {
    }

    GameRenderer::~GameRenderer() {
        mGameWindowResizeListener.disconnect();
    }

    void GameRenderer::init() {
        mGameWindowResizeListener = InputManager::getInstance().GameWindowResizeEvent.connect(boost::bind(&GameRenderer::onGameWindowResize, this, _1, _2));
    }

    void GameRenderer::registerDrawable(components::RenderComponent *drawable) {
        int depth = drawable->getDepth();
        auto iter = mRenderQueue.begin();
        for(; iter != mRenderQueue.end(); ++iter) {
            if(depth < (*iter)->getDepth())
                break;
        }

        mRenderQueue.insert(iter, drawable);
        utils::Logger::log(std::to_string(drawable->getGUID()) + " has been added to the render queue");
    }

    void GameRenderer::unregisterDrawable(components::RenderComponent *drawable) {
        auto iter = std::find(mRenderQueue.begin(), mRenderQueue.end(), drawable);
        if(iter != mRenderQueue.end()) {
            mRenderQueue.erase(iter);
            utils::Logger::log(std::to_string(drawable->getGUID()) + " has been removed to the render queue");
        }
    }

    void GameRenderer::clear() {
        mRenderQueue.clear();
        utils::Logger::log("render queue cleared");
    }

    //depth only works for UI elements, for drawables in layers such as ENTITY and BACKGROUND, we render them based
    //on their distance towords the camera
    void GameRenderer::draw() {
        std::sort(mRenderQueue.begin(), mRenderQueue.end(), [](const RenderComponent* a, const RenderComponent* b) -> bool {
            if(a->getLayer() != b->getLayer())
                return a->getLayer() < b->getLayer();
            else if(a->getDepth() != b->getDepth())
                return a->getDepth() < b->getDepth();
            else {
                auto boxA = a->getBoundingBox();
                auto boxB = b->getBoundingBox();
                return (boxA.top + boxA.height) < (boxB.top + boxB.height);
            }
        });

        mWindow.setView(mGameCamera);
        auto iter = mRenderQueue.begin();
        for (iter = mRenderQueue.begin(); iter != mRenderQueue.end() && (*iter)->getLayer() < RenderLayer::UI; iter++) {
            (*iter)->draw(mWindow);
        }

        mWindow.setView(mUICamera);
        for (; iter != mRenderQueue.end(); iter++) {
            (*iter)->draw(mWindow);
        }

        if(mFpsText != nullptr) {
            int fps = core::GameManager::getInstance().getFPS();
            mFpsText->setText("FPS: " + std::to_string(fps), true);
        }

    }

    const std::vector<components::RenderComponent *> &GameRenderer::getCurrentDrawables() const {
        return mRenderQueue;
    }

    void GameRenderer::onGameWindowResize(int width, int height) {
        float referencedRatio = (float)ReferencedResolution.x / ReferencedResolution.y;
        float currentRatio = (float)width / height;

        if(referencedRatio > currentRatio) {
            float newHeight = (float)height / referencedRatio * currentRatio;
            float blackPortion = std::abs(height - newHeight) / (float)height;
            mUICamera.setViewport(sf::FloatRect(0.f, blackPortion / 2, 1.f, 1.f - blackPortion));
            mGameCamera.setViewport(sf::FloatRect(0.f, blackPortion / 2, 1.f, 1.f - blackPortion));
        }
        else {
            float newWidth = (float)width / currentRatio * referencedRatio;
            float blackPortion = std::abs(width - newWidth) / (float)width;
            mUICamera.setViewport(sf::FloatRect(blackPortion / 2, 0, 1.f - blackPortion, 1.f));
            mGameCamera.setViewport(sf::FloatRect(blackPortion / 2, 0, 1.f - blackPortion, 1.f));
        }
    }

    void GameRenderer::showFPS() {
        if(mFpsText == nullptr) {
            auto go = core::GameManager::getInstance().instantiateGameObject();
            auto transform = go->getTransform();
            transform->setLocalPosition(10, 10);
            mFpsText = go->addComponent<Text>(UI, 10000);
            mFpsText->setFont(resource::FontManager::getInstance().getByID(resource::FONT_GUI_1));
            mFpsText->setTextSize(40);
            mFpsText->setColor(sf::Color::Cyan);
            mFpsText->setText("", true);
        }
    }
}