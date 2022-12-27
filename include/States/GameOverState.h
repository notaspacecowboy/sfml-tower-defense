//
// Created by Zheng Yang on 22/11/22.
//

#ifndef GAME_GAMEOVERSTATE_H
#define GAME_GAMEOVERSTATE_H

#include <States/State.h>

namespace game::states {

    /** @brief game over state
     *
     *  this state will be pushed to state machine when player loses
     *
     *  @author Zheng Yang
     */
    class GameOverState: public State {
    public:


        /** @brief GameOverState constructor
         *
         * GameOverState constructor
         *
         * @param owner state machine
         *
         */
                                                        GameOverState(StateMachine* owner);


        /** @brief GameOverState destructor
         *
         * GameOverState destructor
         *
         */
                                                        ~GameOverState();


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
        void                                            onReturnToMainButtonClicked();


        /** @brief reset player state before going back to main menu
         *
         * reset player state before going back to main menu
         *
         */
        void                                            resetPlayer();

    private:
        boost::signals2::connection                     mReturnToMainButtonListener;  /*!< return to main button click event listener */
    };
}

#endif //GAME_GAMEOVERSTATE_H
