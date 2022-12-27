//
// Created by Zheng Yang on 17/11/22.
//

#ifndef GAME_SIMPLEBUTTON_H
#define GAME_SIMPLEBUTTON_H

#include "Component.h"
#include <Input/InputEventHandler.h>
#include "Components/Drawables/Sprite.h"
#include <boost/signals2.hpp>

namespace game::components {
    typedef boost::signals2::signal<void()>     ButtonClickDelegate;


    /** @brief button class that can function as a button but does not need a button define file
     *
     *  the button class can be attached to any gameobject with a drawable component and provide a similar functionality as the button class
     *
     *  @author Zheng Yang
     */
    class SimpleButton: public Component, public input::IPointerClick {
    public:

        /** @brief simple button constructor
         *
         *  simple button constructor
         *
         *  @param owner owner of the component
         */
                                                SimpleButton(game::components::GameObject &owner);


        /** @brief simple button destructor
         *
         *  simple button destructor
         *
         */
                                                ~SimpleButton();


        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is enabled
        *
        */
        void                                    onEnable() override;


        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is disabled
        *
        */
        void                                    onDisable() override;


        /** @brief callback for pointer click event
        *
        * callback for pointer release event - notify listeners of the button click event that this button is clicked
        *
        */
        void                                    onPointerClick() override;


        /** @brief set if button can be detected by input system and block pointer
        *
        * set if a button can be detected by input system and block pointer
        *
        * @param isRaycastable true if you want the button to be detected and block pointer, false otherwise
        */
        void                                    setRaycastable(bool isRaycastable);


        /** @brief get the current button sprite
        *
        * get the current button sprite
        *
        * @return the button sprite
        */
        RenderComponent*                        getDrawable() const;

        ButtonClickDelegate                     onClick;            /*!< my on click event */

    public:
        RenderComponent*                        mDrawable;          /*!< my button drawable */
    };
};

#endif //GAME_SIMPLEBUTTON_H
