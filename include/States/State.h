//
// Created by Zheng Yang on 19/10/22.
//

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <Core/ObjectHandle.h>
#include <Components.h>

namespace game::states {

    class StateMachine;


    /** @brief base class of all game states
     *
     *  this is the base class of all game states. A game state controls the game flow, and it allows a state to be easily
     *  reused and stack on each other to create multiple states
     *  for example, a game pause state can be stack on the game state so the game state can be resumed once the game pause state
     *  gets poped
     *
     *  @author Zheng Yang
     */
    class State {
    public:

        /** @brief state constructor
         *
         * state constructor
         *
         * @param owner state machine
         *
         */
        explicit                        State(StateMachine* owner);


        /** @brief state constructor
         *
         * state constructor
         *
         * @param owner state machine
         * @param rootHeight height of the root gameobject for the state
         * @param rootWidth width of the root gameobject for the state
         *
         */
        explicit                        State(StateMachine* owner, int rootWidth, int rootHeight);


        /** @brief state destructor
         *
         * state destructor
         *
         */
        virtual                         ~State();

        /** @brief initialization of state
         *
         * initialization of state, called by state machine after state is created and put to the stack
         *
         */
        virtual void                    init();


        /** @brief enable user input in the current state
         *
         * call this function to enable user input in the current state
         *
         */
        virtual void                    enableInput();


        /** @brief disable user input in the current state
         *
         * call this function to disable user input in the current state
         *
         */
        virtual void                    disableInput();


        /** @brief check if delta time should be set to 0 when the state is created and put to the state machine
         *
         * check if delta time should be set to 0 when the state is created and put to the state machine
         *
         */
        virtual bool                    freezeTime();


        /** @brief helper function to instantiate a gameobject
         *
         * helper function to instantiate a gameobject and set its parent to the root gameobject of the state
         *
         * @param anchor gameobject anchor
         * @param pivot gameobject pivot
         */
        components::GameObject*         instantiateGO(components::Anchor anchor = components::ANCHOR_TOP_LEFT,
                                                      components::Pivot pivot = components::PIVOT_TOP_LEFT,
                                                      components::GameObject::GoState = components::GameObject::GoState::ACTIVE);

    protected:
        core::GoHandle                  mRoot;          /*!< root gameobject handle */
        StateMachine*                   mOwner;         /*!< state machine */
    };

}

#endif //GAME_STATE_H
