//
// Created by Zheng Yang on 20/10/22.
//

#ifndef GAME_STARTSTATE_H
#define GAME_STARTSTATE_H

#include <States/State.h>
#include <Core/ObjectHandle.h>
#include <boost/signals2.hpp>
#include <SFML/Graphics.hpp>

namespace game::components {
    class Button;
    class Text;
    class Sprite;
    class RotateAnimator;
    class FadeInOutAnimator;
}

namespace game::states {

    /** @brief game state
     *
     *  this is the fist state to be pushed into the state machine when player opens the game application
     *
     *  @author Zheng Yang
     */
    class StartState: public State {
    public:

        /** @brief StartState constructor
         *
         * StartState constructor
         *
         */
                                            StartState(StateMachine* owner);


        /** @brief StartState destructor
         *
         * StartState destructor
         *
         */
                                            ~StartState();


        /** @brief initialization of state
         *
         * initialization of state, called by state machine after state is created and put to the stack
         *
         */
        void                                init() override;


        /** @brief register all game resources
         *
         * register all game resources to the resource manager
         *
         */
        void                                registerResources();


        /** @brief load all the resource that needs to be used before loading other resources
         *
         * load all the resource that needs to be used before loading other resources
         * for example, the loading spinner
         *
         */
        void                                loadImmediateResources();


        /** @brief asynchronous task to load all resources
         *
         *  asynchronous task to load all resources into game
         *
         */
        void                                loadAllResources();


        /** @brief callback for fade in completed event
         * callback function for fade in completed event
         *
         */
        void                                onBackgroundFadeInCompleted();


        /** @brief callback for loading completed event
         * callback function for loading completed event
         *
         */
        void                                onLoadingComplete();


        /** @brief callback for any keyboard key pressed event
         * callback function for any keyboard key pressed event
         *
         */
        void                                onAnyKeyPressed(sf::Keyboard::Key keyCode);


        /** @brief callback for mouse pressed event
         * callback function for mouse pressed event
         *
         */
        void                                onMousePressed();


        /** @brief go to main state
         * call this function to go to main state
         *
         */
        void                                gotoMainState();

    private:
        boost::signals2::connection         mFadeInListener;                 /*!< fade in animation listener */
        boost::signals2::connection         mLoadingTaskListener;            /*!< loading task listener */
        boost::signals2::connection         mKeyPressedListener;             /*!< keyboard pressed listener */
        boost::signals2::connection         mMousePressedListener;           /*!< mouse pressed listener */
        boost::signals2::connection         mGoToMainStateListener;          /*!< go to main menu listener */

        components::Sprite*                 mBackgroundSprite;               /*!< background sprite */
        components::Text*                   mPressKeyText;                   /*!< press any key text */
    };
}


#endif //GAME_STARTSTATE_H
