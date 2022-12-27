//
// Created by zyang464 on 22/10/22.
//

#ifndef GAME_POINTERDATA_H
#define GAME_POINTERDATA_H

#include <SFML/System/Vector2.hpp>
#include <Input/InputEnums.h>
#include <memory>
#include <Core/ObjectHandle.h>
namespace game::input {
    //right now, for the sake of simplicity, we only care about the position of mouse in a frame, and how is it
    //different from the last frame

    /** @brief bookkeeping class for pointer data in the current frame
     *
     *  this class bookkeeps all the relevant pointer data in the current frame, and it is updated by input manager every frame
     *
     *  @author Zheng Yang
     */
    struct PointerData {

        /** @brief pointer data constructor
         *
         *  pointer data constructor
         *
         *  @param id button id of the pointer data
         */
                                                                    PointerData(MouseButton id);
                                                                    PointerData(PointerData&) = delete;

        MouseButton                                                 buttonID;               /*!< button id */

        sf::Vector2i                                                pos;                    /*!< pointer position */
        sf::Vector2i                                                deltaPos;               /*!< how much the pointer moved after last frame */

        bool                                                        pressedThisFrame;       /*!< does the pointer get pressed this frame */


        //the cached gameobjects from last frame could have been deleted in this frame, need to figure out a way to
        //accessing invalid gameobjects
        core::GoHandle                                              pointerEnter;           /*!< the gameobject that gets entered*/
        core::GoHandle                                              pointerPressed;         /*!< the gameobject that gets pressed last frame or earlier */
        //core::GoHandle                                              pointerReleased;

    };
}


#endif //GAME_POINTERDATA_H
