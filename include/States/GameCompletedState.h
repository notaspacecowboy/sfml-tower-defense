//
// Created by Zheng Yang on 26/11/22.
//

#ifndef GAME_GAMECOMPLETEDSTATE_H
#define GAME_GAMECOMPLETEDSTATE_H



#include <States/State.h>

namespace game::states {

    /** @brief game completed state
     *
     *  this state will be pushed to state machine when player beats the game
     *
     *  @author Zheng Yang
     */
    class GameCompletedState: public State {
    public:


        /** @brief GameCompletedState constructor
         *
         * GameCompletedState constructor
         *
         * @param owner state machine
         *
         */
        GameCompletedState(StateMachine* owner);


        /** @brief GameOverState destructor
         *
         * GameOverState destructor
         *
         */
        ~GameCompletedState();


        /** @brief initialization of state
         *
         * initialization of state, called by state machine after state is created and put to the stack
         *
         */
        void                                            init() override;


        /** @brief check if delta time should be set to 0 when the state is created and put to the state machine
         *
         * check if delta time should be set to 0 when the state is created and put to the state machine
         *
         */
        bool                                            freezeTime() override;


        /** @brief return to main button click event handler
         *
         * callback function for main button click event
         *
         */
        void                                            onQuitGameClicked();


        /** @brief return to restart button click event handler
         *
         * callback function for restart button click event
         *
         */
        void                                            onRestartClicked();


        /** @brief reset player state before going back to main menu
         *
         * reset player state before going back to main menu
         *
         */
        void                                            resetPlayer();

    private:
        boost::signals2::connection                     mQuitButtonListener;  /*!< return to main button click event listener */
        boost::signals2::connection                     mRestartListener;             /*!< restart game button click event listener */
    };
}

#endif //GAME_GAMECOMPLETEDSTATE_H
