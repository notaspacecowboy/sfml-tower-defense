//
// Created by zyang464 on 22/10/22.
//

#ifndef GAME_INPUTENUMS_H
#define GAME_INPUTENUMS_H

namespace game::input {

    /** @brief all mouse buttons
     *
     *  this enum defines enumerators for all mouse buttons. Currently game only handles left button events
     *
     *  @author Zheng Yang
     */
    enum MouseButton {
        LEFT = 0,       /*!< left button */
        MIDDLE = 1,     /*!< middle button */
        RIGHT = 2       /*!< right button */
    };
}

#endif //GAME_INPUTENUMS_H
