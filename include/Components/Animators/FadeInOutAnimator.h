//
// Created by zyang464 on 30/10/22.
//

#ifndef GAME_FADEINOUTANIMATOR_H
#define GAME_FADEINOUTANIMATOR_H

#include "Components/Drawables/RenderComponent.h"
#include "Animator.h"

namespace game::components {

    /** @brief a simple animator that makes an element or a group of elements fade in and fade out in a given duration
     *
     *  This class is a a simple animator that makes an element or a group of elements fade in and fade out in a given duration
     *  currently it only support linear animation transition, the support for ease functions will be added if we have time
     *
     *  @author Zheng Yang
     */
    class FadeInOutAnimator: public Animator {
    public:
        /** @brief character animator constructor
        *
        *  fading animator constructor
        *
        *  @param owner owner of the animator
        *  @param startAlpha the alpha value of the element when animation starts
        *  @param endAlpha the alpha value of the element when animation ends
        *  @param duration the total amount of time it takes to finish the animation
        *  @param isLooping should the animation repeating
        *  @param isStartAutomatically should the animation start automatically
        */
        explicit                                                FadeInOutAnimator(game::components::GameObject &owner,
                                                                                  float startAlpha,
                                                                                  float endAlpha,
                                                                                  int duration,
                                                                                  bool isLooping,
                                                                                  bool isStartAutomatically);

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

        /** @brief add a render component as one of the targets of this animator
        *
        * this function add a render component as one of the targets of this animator
        *
        * @param target  the drawable to be animated on
        */
        void                                                    addTarget(RenderComponent* animated);

        /** @brief remove a render component as one of the targets of this animator
        *
        * this function remove a render component from the list of targets
        *
        * @param target  the drawable to be remove from the animation list
        */
        void                                                    removeTarget(RenderComponent* animated);


    private:
        float                                                   mStartAlpha;        /*!< the alpha value of the elements when animation start */
        float                                                   mEndAlpha;          /*!< the alpha value of the elements when animation ends */
        float                                                   mCurrentAlpha;      /*!< the current alpha value of the elements */
        std::vector<RenderComponent*>                           mTargets;           /*!< targets of the animator */
    };
}

#endif //GAME_FADEINOUTANIMATOR_H
