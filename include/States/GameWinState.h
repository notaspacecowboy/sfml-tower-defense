//
// Created by Zheng Yang on 26/11/22.
//

#ifndef GAME_GAMEWINSTATE_H
#define GAME_GAMEWINSTATE_H


#include <States/State.h>

namespace game::states {

    /** @brief game win state
     *
     *  this state will be pushed to state machine when player beats a game level
     *
     *  @author Zheng Yang
     */
    class GameWinState: public State {
    public:


        /** @brief GameOverState constructor
         *
         * GameOverState constructor
         *
         * @param owner state machine
         *
         */
        GameWinState(StateMachine* owner);


        /** @brief GameOverState destructor
         *
         * GameOverState destructor
         *
         */
        ~GameWinState();


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


        /** @brief return to go to next level button click event handler
         *
         * callback function for go to next level button click event
         *
         */
        void                                            onGoToNextLevelClicked();

    private:
        boost::signals2::connection                     mReturnToMainButtonListener;  /*!< return to main button click event listener */
        boost::signals2::connection                     mGotoNextGameListener;        /*!< go to next game button click event listener */
    };
}

#endif //GAME_GAMEWINSTATE_H
