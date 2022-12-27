//
// Created by Zheng Yang on 29/09/22.
//

#ifndef GAME_INPUTMANAGER_H
#define GAME_INPUTMANAGER_H

#include "Utils/Singleton.h"
#include "Core/GameManager.h"
#include "Input/PointerData.h"
#include "Renderer/RenderLayer.h"
#include "Input/InputEnums.h"
#include "SFML/System/Vector2.hpp"
#include "boost/signals2.hpp"

namespace game::input {
    typedef boost::signals2::signal<void(int, int)>                                     GameWindowResizeDelegate;
    typedef boost::signals2::signal<void()>                                             GameWindowCloseDelegate;
    typedef boost::signals2::signal<void(sf::Keyboard::Key keyPressed)>                 GameKeyPressedDelegate;
    typedef boost::signals2::signal<void()>                                             GameMousePressedDelegate;
    typedef boost::signals2::signal<void(int, int)>                                     GameMouseDragDelegate;
    typedef boost::signals2::signal<void(int)>                                          GameWheelScrolledDelegate;


    /** @brief player input handler
     *
     *  this class processes player input every frame
     *
     *  @author Zheng Yang
     */
    class InputManager: public utils::Singleton<InputManager> {
        friend class Singleton<InputManager>;
    public:


        /** @brief singleton class initialization method
         *
         *  call this function before accessing any of its APIs
         *
         *  @param window game window
         *  @param uiCamera ui camera
         *  @param gameCamera game camera
         */
        void                                                init(sf::RenderWindow *window, sf::View *uiCamera, sf::View *gameCamera);


        /** @brief processes all player inputs from last frame
         *
         *  this function is called by game manager every frame to handle all player inputs from last frame
         *  do not call it manually!
         */
        void                                                tick();


        /** @brief get cached pointer data for current frame
         *
         *  this function returns the cached pointer data for current frame
         *
         *  @return cached pointer data for current frame
         */
        PointerData&                                        getCachedPointerData();

        GameWindowResizeDelegate                            GameWindowResizeEvent;      /*!< game window resize event */
        GameWindowCloseDelegate                             GameWindowCloseEvent;       /*!< game window close event */
        GameKeyPressedDelegate                              GameKeyPressedEvent;        /*!< keyboard pressing event */
        GameMousePressedDelegate                            GameMousePressedEvent;      /*!< mouse pressing event */
        GameWheelScrolledDelegate                           GameWheelScrolledEvent;     /*!< mouse wheel scrolling event */
        GameMouseDragDelegate                               GameMouseDragEvent;         /*!< mouse drag event */


    private:

        /** @brief private constructor
         *
         *  private constructor to ensure singleton pattern
         */
                                                            InputManager();


        /** @brief processes mouse input every frame
         *
         *  this function gets called by tick() every frame to handle all the mouse input events from last frame
         *
         *  @param camera camera
         *  @param layerStartToCheck check starts from which layer
         *  @param layerStartToCheck check stops from which layer
         */
        void                                                processMouseInput(sf::View& camera,
                                                                              renderer::RenderLayer layerStartToCheck,
                                                                              renderer::RenderLayer layerStopToCheck);


        /** @brief execute pointer enter event handlers
         *
         *  this function execute all the components in a gameobject that implements IPointerEnter interface
         *
         *  @param target game object
         */
        void                                                executePointerEnter(components::GameObject* target);


        /** @brief execute pointer leave event handlers
         *
         *  this function execute all the components in a gameobject that implements IPointerLeave interface
         *
         *  @param target game object
         */
        void                                                executePointerLeave(components::GameObject* target);


        /** @brief execute pointer press event handlers
         *
         *  this function execute all the components in a gameobject that implements IPointerPress interface
         *
         *  @param target game object
         */
        void                                                executePointerPress(components::GameObject* target);


        /** @brief execute pointer release event handlers
         *
         *  this function execute all the components in a gameobject that implements IPointerRelease interface
         *
         *  @param target game object
         */
        void                                                executePointerRelease(components::GameObject* target);


        /** @brief execute pointer click event handlers
         *
         *  this function execute all the components in a gameobject that implements IPointerClick interface
         *
         *  @param target game object
         */
        void                                                executePointerClick(components::GameObject* target);


        //TODO store the pointer data cache in a map if we want to detect right mouse click
        PointerData                                         mCachedPointerData;     /*!< cached mouse data */
        sf::RenderWindow*                                   mWindow;                /*!< cached game window */

        sf::View*                                           mUICamera;              /*!< cached UI camera */
        sf::View*                                           mGameCamera;            /*!< cached game camera */
    };

}

#endif //GAME_INPUTMANAGER_H
