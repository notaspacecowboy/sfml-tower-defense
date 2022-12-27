//
// Created by Zheng Yang on 03/11/22.
//

#ifndef GAME_TESTSTATE_H
#define GAME_TESTSTATE_H

#include <States/State.h>
#include <Components/Animators/CharacterAnimator.h>

namespace game::states {


    /** @brief shop state
     *
     *  this state will be pushed to state machine when player goes to the test scene
     *
     *  @author Zheng Yang
     */
    class TestState: public State {
    public:

        /** @brief TestState constructor
         *
         * TestState constructor
         *
         * @param owner state machine
         *
         */
                                                        TestState(StateMachine* owner);


        /** @brief TestState destructor
         *
         * TestState destructor
         *
         */
                                                        ~TestState();


        /** @brief initialization of state
         *
         * initialization of state, called by state machine after state is created and put to the stack
         *
         */
        void                                            init() override;


        /** @brief callback for keyboard pressed event
         * callback function for keyboard pressed event
         *
         * @param keyCode keycode of the key that gets pressed
         */
        void                                            onPressKey(sf::Keyboard::Key keyCode);

    private:
        boost::signals2::connection                     mKeyPressedListener;            /*!< fade in animation listener */
        int                                             mCurrentAnimatorIndex;          /*!< current animator index */
        int                                             mCurrentAnimationClipIndex;     /*!< current animation index */
        std::vector<components::CharacterAnimator*>     mTestAnimators;                 /*!< test animators */
        std::vector<components::AnimationState>         mStates;                        /*!< all animation states */
    };
}

#endif //GAME_TESTSTATE_H
