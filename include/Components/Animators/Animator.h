//
// Created by Zheng Yang on 30/10/22.
//

#ifndef GAME_ANIMATOR_H
#define GAME_ANIMATOR_H

#include "Components/Component.h"
#include "boost/signals2.hpp"
#include "Components/Drawables/RenderComponent.h"

namespace game::components {
    typedef boost::signals2::signal<void()>         animationCompleteDelegate;

    /** @brief base class of all the animator components
     *
     *  This class is the base class of all the animator components
     *
     *  @author Zheng Yang
     */
    class Animator: public Component {
    public:
        /** @brief animator constructor
        *
        *  animator constructor
        *
        *  @param owner owner of the animator
        *  @param duration duration of the animation
        *  @param isLooping is the animation repeating
        *  @param isStartAutomatically does the animation automatically start when enabled
        */
        explicit                                    Animator(GameObject &owner,
                                                             int duration,
                                                             bool isLooping,
                                                             bool isStartAutomatically);

        /** @brief animator destructor
        *
        *  animator destructor
        *
        */
                                                    ~Animator();

        /** @brief start animation
        *
        * to start the animation, call this method
        *
        */
        virtual void                                start();

        /** @brief stop animation
        *
        * to stop the animation, call this method
        *
        */
        virtual void                                stop();

        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is enabled
        *
        */
        void                                        onEnable() override;

        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is disabled
        *
        */
        void                                        onDisable() override;

        animationCompleteDelegate                   onAnimationComplete;  /*!< callback event for animation complete */

    protected:
        bool                                        mIsLooping;             /*!< is the animation repeating */
        bool                                        mIsStartAutomatically;  /*!< is the animation automatically started */
        bool                                        mIsPlaying;             /*!< current playing state */
        float                                       mDuration;              /*!< duration of the animation */
        float                                       mTimeElapsed;           /*!< current time elapsed */
    };
}

#endif //GAME_ANIMATOR_H
