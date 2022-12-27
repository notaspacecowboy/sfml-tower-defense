//
// Created by Zheng Yang on 29/09/22.
//

#include "Input/InputManager.h"
#include "Components/Drawables/RenderComponent.h"
#include "Utils/TransformUtility.h"
#include "Utils/Logger.h"
#include "Input/InputEventHandler.h"

namespace game::input {
    using namespace core;

    InputManager::InputManager(): mCachedPointerData(MouseButton::LEFT) {}

    void InputManager::init(sf::RenderWindow *window, sf::View *uiCamera, sf::View *gameCamera) {
        mWindow = window;
        mUICamera = uiCamera;
        mGameCamera = gameCamera;
    }

    void InputManager::tick() {
        if(mWindow == nullptr || mUICamera == nullptr || mGameCamera == nullptr)
            return;

        mCachedPointerData.pressedThisFrame = false;

        sf::Event event;
        while(mWindow != nullptr && mWindow->pollEvent(event)) {
            switch (event.type) {
                case::sf::Event::KeyPressed:
                    if(!GameKeyPressedEvent.empty())
                        GameKeyPressedEvent(event.key.code);
                    break;

                case::sf::Event::MouseButtonPressed:
                    if(!GameMousePressedEvent.empty())
                        GameMousePressedEvent();

                    if(event.mouseButton.button == sf::Mouse::Left)
                        mCachedPointerData.pressedThisFrame = true;
                    break;

                case::sf::Event::MouseMoved:
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !GameMouseDragEvent.empty()) {
                        GameMouseDragEvent(mCachedPointerData.deltaPos.x, mCachedPointerData.deltaPos.y);
                    }
                    break;

                case::sf::Event::MouseWheelMoved:
                    if(!GameWheelScrolledEvent.empty())
                        GameWheelScrolledEvent(event.mouseWheel.delta);
                    break;

                case::sf::Event::Resized:
                    if(!GameWindowResizeEvent.empty())
                        GameWindowResizeEvent(event.size.width, event.size.height);
                    break;

                case sf::Event::Closed:
                    if(!GameWindowCloseEvent.empty())
                        GameWindowCloseEvent();
                    return;
            }
        }

        processMouseInput(*mUICamera, renderer::RenderLayer::UI, renderer::RenderLayer::ENTITY);
    }


    void InputManager::processMouseInput(sf::View& camera, renderer::RenderLayer layerStartToCheck, renderer::RenderLayer layerStopToCheck) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*mWindow);
        sf::Vector2i delta = mousePos - mCachedPointerData.pos;
        mCachedPointerData.pos = mousePos;
        mCachedPointerData.deltaPos = delta;

        const std::vector<components::RenderComponent*> &allDrawables = GameManager::getInstance().getRenderer().getCurrentDrawables();
        auto iter = allDrawables.rbegin();
        bool found = false;
        for(; iter != allDrawables.rend(); ++iter) {
            auto drawable = *iter;

            if(drawable->getLayer() <= layerStopToCheck)
                break;

            if(drawable->getLayer() > layerStartToCheck)
                continue;

            if(!drawable->isRaycastable())
                continue;


            if(utils::TransformUtility::rectangleContainsScreenPoint(*mWindow, camera, mousePos, drawable->getBoundingBox())) {
                found = true;
                break;
            }
        }

        if(found) {
            auto drawable = *iter;
            auto currentGO = &(drawable->getGameObject());

            if(mCachedPointerData.pointerEnter && mCachedPointerData.pointerEnter->getGUID() != currentGO->getGUID()) {
                //utils::Logger::log("cached pointer not equal to current go: execute pointer leave event for cached GO");
                executePointerLeave(mCachedPointerData.pointerEnter.get());
            }
            else if(!mCachedPointerData.pointerEnter) {
                //utils::Logger::log("enter the GO area just in this frame, execute pointer enter for current go");
                executePointerEnter(currentGO);
            }
            mCachedPointerData.pointerEnter.updateGUID(currentGO->getGUID());

            // if player mouse is being pressed
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                if(mCachedPointerData.pointerPressed && mCachedPointerData.pointerPressed->getGUID() == currentGO->getGUID()) {
                    //this is a drag event, we do not handle it for now
                    //utils::Logger::log("drag event unhandled");
                }
                else if(mCachedPointerData.pointerPressed) {
                }
                else if(mCachedPointerData.pressedThisFrame){

                    //drawable just got pressed this frame, execute onPointerPressEvent
                    mCachedPointerData.pointerPressed.updateGUID(currentGO->getGUID());

                    //utils::Logger::log("current GO just got pressed in this frame, execute pointer press for current go");
                    executePointerPress(currentGO);
                }
            }
            else {
                if(mCachedPointerData.pointerPressed) {
                    //utils::Logger::log("we were pressing on some GO before, but it is not pressed anymore, executer pointer release for cached GO");
                    executePointerRelease(mCachedPointerData.pointerPressed.get());

                    //button click
                    if(mCachedPointerData.pointerPressed->getGUID() == currentGO->getGUID()) {
                        utils::Logger::log("pointer click");
                        executePointerClick(currentGO);
                    }

                    mCachedPointerData.pointerPressed.reset();
                }
            }
        }
        else {
            if(mCachedPointerData.pointerEnter) {
                //utils::Logger::log("player pointer left the area of the cached GO, execute pointer leave");
                executePointerLeave(mCachedPointerData.pointerEnter.get());
                mCachedPointerData.pointerEnter.reset();
            }

            if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mCachedPointerData.pointerPressed) {
                //utils::Logger::log("player pointer released outside of the area of the cached GO, execute pointer release only");
                executePointerRelease(mCachedPointerData.pointerPressed.get());
                mCachedPointerData.pointerPressed.reset();
            }
        }


    }

    void InputManager::executePointerEnter(components::GameObject *target) {
        std::vector<IPointerEnter*> allHandlers;
        target->getComponents<IPointerEnter>(allHandlers);
        for(IPointerEnter* handler: allHandlers) {
            handler->onPointerEnter();
        }
    }

    void InputManager::executePointerLeave(components::GameObject *target) {
        std::vector<IPointerLeave*> allHandlers;
        target->getComponents<IPointerLeave>(allHandlers);
        for(IPointerLeave* handler: allHandlers) {
            handler->onPointerLeave();
        }
    }

    void InputManager::executePointerPress(components::GameObject *target) {
        std::vector<IPointerPress*> allHandlers;
        target->getComponents<IPointerPress>(allHandlers);
        for(IPointerPress* handler: allHandlers) {
            handler->onPointerPress();
        }
    }


    void InputManager::executePointerRelease(components::GameObject *target) {
        std::vector<IPointerRelease*> allHandlers;
        target->getComponents<IPointerRelease>(allHandlers);
        for(IPointerRelease* handler: allHandlers) {
            handler->onPointerRelease();
        }
    }

    void InputManager::executePointerClick(components::GameObject *target) {
        std::vector<IPointerClick*> allHandlers;
        target->getComponents<IPointerClick>(allHandlers);
        for(IPointerClick* handler: allHandlers) {
            handler->onPointerClick();
        }
    }

    PointerData &InputManager::getCachedPointerData() {
        return mCachedPointerData;
    }
}
