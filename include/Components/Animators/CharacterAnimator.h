//
// Created by Zheng Yang on 03/11/22.
//

#ifndef GAME_CHARACTERANIMATOR_H
#define GAME_CHARACTERANIMATOR_H

#include "Animator.h"
#include <Data/AnimDefine.h>
#include <Components/Drawables/Sprite.h>
#include <unordered_map>

namespace game::components {

    /** @brief a enum class for all the available animation states
     *
     *  This class is a enum class that provide unique identifier for every available animation states
     *
     *  @author Zheng Yang
     */
    enum AnimationState {
        NONE = 0,
        IDLE = 1,
        WALK = 2,
        JUMP = 3,
        RUN = 4,
        DIE = 5
    };


    /** @brief animator for in-game characters
     *
     *  This type of animator animates directly on in-game character such as enemies and towers. It allows user to
     *  register multiple animation state so that it can transit between states during gameplay
     *
     *  @author Zheng Yang
     */
    class CharacterAnimator: public Animator {
    public:
        /** @brief character animator constructor
        *
        *  character animator constructor
        *
        *  @param owner owner of the animator
        */
                                                                            CharacterAnimator(GameObject& owner);

        /** @brief start animation
        *
        * to start the animation, call this override method
        *
        */
        void                                                                start() override;

        /** @brief stop animation
        *
        * to stop the animation, call this override method
        *
        */
        void                                                                stop() override;

        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically every frame. This is where every component in the game gets updated
        *
        * @param deltaTime the time elpased between now and last frame
        */
        void                                                                tick(float deltaTime) override;

        /** @brief set the sprite component to perform animation on
        *
        * this function set the sprite component to perform animation on
        *
        * @param target  the sprite component to perform animation on
        */
        void                                                                setTarget(Sprite* target);

        /** @brief transition between animation states
        *
        * call this function to make transition between multiple animation states, must call registerState first to register the available states
        *
        * @param state  the new state
        */
        void                                                                makeTransition(AnimationState state);

        /** @brief register state
        *
        * call this function to register an animation state with the current character animator
        *
        * @param state  the state id
        * @param tid animation define data tid
        * @param makeInitialState is this state the initial state of the animator
        */
        void                                                                registerState(AnimationState state, int tid, bool makeInitialState = false);

        /** @brief register state
        *
        * call this function to register an animation state with the current character animator
        *
        * @param state  the state id
        * @param tid animation define data tid
        * @param makeInitialState is this state the initial state of the animator
        */
        void                                                                registerState(int animStateID, int tid, bool makeInitialState = false);


        /** @brief check if an animation state is registered
        *
        * call this function to check if an animation state is registered
        *
        * @param state  the state id
        * @return true if state exist, otherwise false
        */
        bool                                                                containsState(AnimationState state);

        /** @brief current animation state getter
        *
        * this function returns the current animation state of the animator
        *
        * @return  current animation state
        */
        AnimationState                                                      getCurrentState() const;

        /** @brief get all the available states of the current animator
        *
        * get all the available states of the current animator and put it in the vector
        *
        * @param states all the animation states will be put here
        */
        void                                                                getAllStates(std::vector<AnimationState>& states) const;

    private:
        Sprite*                                                             mTarget;            /*!< target of the animator */
        sf::Texture*                                                        mCachedTexture;     /*!< texture of the animator */
        int                                                                 mCurrentAnimIndex;  /*!< position of current animation */
        AnimationState                                                      mCurrentState;      /*!< current animation state */
        const data::AnimDefine*                                             mCurrentAnimation;  /*!< current animation identifier */
        const data::AnimDefine*                                             mInitialAnimation;  /*!< initial animation identifier */
        std::unordered_map<AnimationState, const data::AnimDefine*>         mStateMap;          /*!< animation state to data file mapping */

        bool                                                                mGoReverse;         /*!< true if go is facing right, false otherwise */
    };
}


#endif //GAME_CHARACTERANIMATOR_H
