//
// Created by Zheng Yang on 30/10/22.
//

#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H

#include <Components/Component.h>
#include <boost/signals2.hpp>
#include <Data/ButtonDefine.h>
#include "Components/Drawables/Sprite.h"
#include "Components/Drawables/Text.h"
#include <Input/InputEventHandler.h>

namespace game::components {
    typedef boost::signals2::signal<void()>     ButtonClickDelegate;


    /** @brief button class that provides a on click event for registrations
     *
     *  the button class that provides a on click event for registrations, and render button to screen based on
     *  rules defined in ButtonDefine json file
     *
     *  @author Zheng Yang
     */
    class Button: public Component, public input::IPointerPress, public input::IPointerRelease, public input::IPointerClick {
    public:


        /** @brief Button constructor
         *
         *  Button constructor
         *
         *  @param owner owner of the component
         *  @param buttonDefine button data
         *  @param layer render layer of the button
         *  @param depth depth of the button in its render layer
         */
                                                Button(GameObject& owner, const data::ButtonDefine *buttonDefine, renderer::RenderLayer layer, int depth);


        /** @brief Button destructor
         *
         *  Button destructor
         */
                                                ~Button();


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


        /** @brief callback for pointer press event
        *
        * callback for pointer press event - switch to highlight sprite
        *
        */
        void                                    onPointerPress() override;


        /** @brief callback for pointer release event
        *
        * callback for pointer release event - switch to normal sprite
        *
        */
        void                                    onPointerRelease() override;


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

        /** @brief return the text component of the button
        *
        * return the text component of the button
        *
        * @return text component of the button
        */
        Text*                                   getText() const;


        /** @brief return the sprite component of the button
        *
        * return the sprite component of the button
        *
        * @return sprite component of the button
        */
        Sprite*                                 getSprite() const;

        ButtonClickDelegate                     onClick;                /*!< my on click event */


    public:
        Sprite*                                 mSprite;                /*!< my button sprite */
        Text*                                   mText;                  /*!< my button text */

        sf::Texture*                            mNormalTexture;         /*!< my normal button texture */
        sf::Texture*                            mPressedTexture;        /*!< my highlight button texture */

        const data::ButtonDefine*               mData;                  /*!< my data */
        renderer::RenderLayer                   mLayer;                 /*!< my render layer */
        int                                     mDepth;                 /*!< my depth in current render layer */
    };
};

#endif //GAME_BUTTON_H
