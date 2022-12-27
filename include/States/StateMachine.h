//
// Created by Zheng Yang on 19/10/22.
//

#ifndef GAME_STATEMACHINE_H
#define GAME_STATEMACHINE_H

#include <States/State.h>
#include <map>
#include <functional>
#include <memory>
#include <SFML/System/NonCopyable.hpp>

namespace game::states {
    /** @brief implementation of a pushdown state machine
     *
     *  this class manages all active states and put them in a stack to simulate pushdown automata behavior. This allows
     *  multiple states to be displayed in the same time
     *
     *  @author Zheng Yang
     */
    class StateMachine: private sf::NonCopyable {
    public:
        /** @brief state machine constructor
         *
         * state machine constructor
         *
         * @param owner state machine constructor
         *
         */
                                                                                    StateMachine();


        /** @brief push a state
         *
         * push a state into the top of stack
         *
         * @param args state constructor parameters
         *
         */
        template<class TState, typename... Args>
        TState*                                                                     push(Args&&... args);


        /** @brief pop the top state
         *
         * pop the top state from stack
         *
         *
         */
        void                                                                        pop();


        /** @brief get the top state
         *
         * get the top state from stack
         *
         * @return top state
         */
        State*                                                                      peak() const;


        /** @brief clear all active states
         *
         * clear all active states from the state machine
         *
         */
        void                                                                        clear();


        /** @brief check if state machine is empty
         *
         * check if state machine is empty
         *
         * @return true if state machine is empty, false otherwise
         */
        bool                                                                        isEmpty() const;

    private:
        //TODO change this to follow the same design as how gamemanager handles gameobjects
        std::vector<std::unique_ptr<State>>                                         mActiveStates;      /*!< all active states */
    };
}

#include <States/StateMachine.inl>

#endif //GAME_STATEMACHINE_H
