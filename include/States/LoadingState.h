//
// Created by Zheng Yang on 31/10/22.
//

#ifndef GAME_LOADINGSTATE_H
#define GAME_LOADINGSTATE_H

#include <States/State.h>

namespace game::states {


    /** @brief loading state
     *
     *  this state will be pushed to state machine when a loading task starts
     *
     *  @author Zheng Yang
     */
    class LoadingState: public State {
    public:

        /** @brief LoadingState constructor
         *
         * LoadingState constructor
         *
         * @param owner state machine
         *
         */
        explicit                                LoadingState(StateMachine* owner);

        /** @brief LoadingState destructor
         *
         * LoadingState destructor
         *
         */
                                                ~LoadingState();


        /** @brief initialization of state
         *
         * initialization of state, called by state machine after state is created and put to the stack
         *
         */
        void                                    init() override;
    };
}

#endif //GAME_LOADINGSTATE_H
