//
// Created by Zheng Yang on 31/10/22.
//

#ifndef GAME_ROTATEANIMATOR_H
#define GAME_ROTATEANIMATOR_H

#include "Animator.h"

namespace game::components {
    class RenderComponent;

    /** @brief a simple animator that makes an element or a group of elements rotate a certain angle during a given duration
     *
     *  This class is a a simple animator that makes an element or a group of elements rotate a certain angle in a given duration
     *  currently it only support linear animation transition, the support for ease functions will be added if we have time
     *
     *  @author Zheng Yang
     */
    class RotateAnimator: public Animator {
    public:

        /** @brief character animator constructor
        *
        *  rotation animator constructor
        *
        *  @param owner owner of the animator
        *  @param startAngle the rotation value of the element when animation starts
        *  @param endAngle the rotation value of the element when animation ends
        *  @param duration the total amount of time it takes to finish the animation
        *  @param isLooping should the animation repeating
        *  @param isStartAutomatically should the animation start automatically
        */
        explicit                                                RotateAnimator(game::components::GameObject &owner,
                                                                                  float startAngle,
                                                                                  float endAngle,
                                                                                  int duration,
                                                                                  bool isLooping,
                                                                                  bool isStartAutomatically);

        /** @brief set the drawable to perform animation on
        *
        * this function set the drawable to perform animation on
        *
        * @param target  the drawable to perform animation on
        */
        void                                                    setTarget(RenderComponent* target);

        /** @brief start animation
        *
        * to start the animation, call this override method
        *
        */
        void                                                    start() override;

        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically every frame. This is where every component in the game gets updated
        *
        * @param deltaTime the time elpased between now and last frame
        */
        void                                                    tick(float deltaTime) override;


    private:
        RenderComponent*                                        mTarget;        /*!< target of the animator */
        float                                                   mStartAngle;    /*!< the rotation value of the element when animation start */
        float                                                   mEndAngle;      /*!< the rotation value of the element when animation start */
        float                                                   mCurrentAngle;  /*!< the current rotation value of the elements */
    };
}

#endif //GAME_ROTATEANIMATOR_H
