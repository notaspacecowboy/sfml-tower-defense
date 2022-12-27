//
// Created by Zheng Yang on 21/11/22.
//

#ifndef GAME_PAUSESTATE_H
#define GAME_PAUSESTATE_H

#include <States/State.h>


namespace game::components {
    class Button;
};

namespace game::states {

    /** @brief pause state
     *
     *  this state will be pushed to state machine when player pauses game
     *
     *  @author Zheng Yang
     */
    class PauseState: public State {
    public:

        /** @brief PauseState constructor
         *
         * PauseState constructor
         *
         * @param owner state machine
         *
         */
                                                        PauseState(StateMachine* owner);


        /** @brief PauseState destructor
         *
         * PauseState destructor
         *
         */
                                                        ~PauseState();


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


        /** @brief callback for exit button click event
         *
         * callback function for exit button click event
         *
         */
        void                                            onExitButtonClicked();


        /** @brief callback for main menu button click event
         *
         * callback function for main menu button click event
         *
         */
        void                                            onReturnToMainButtonClicked();


        /** @brief callback for return game button click event
         *
         * callback function for return game button click event
         *
         */
        void                                            onReturnToGameButtonClicked();

    private:
        boost::signals2::connection                     mExitButtonListener;                /*!< exit button click listener */
        boost::signals2::connection                     mReturnToMainButtonListener;        /*!< main menu button click listener */
        boost::signals2::connection                     mReturnToGameButtonListener;        /*!< return game button click listener */
    };
}

#endif //GAME_PAUSESTATE_H
