//
// Created by Zheng Yang on 30/10/22.
//

#ifndef GAME_INPUTEVENTHANDLER_H
#define GAME_INPUTEVENTHANDLER_H

namespace game::input {
    /** @brief interface for pointer enter event handlers
     *
     *  interface for pointer enter event handlers
     *  when pointer enters the bounding box of a gameobject, all the components on the gameobject that implements this
     *  interface will be notified
     *
     *  @author Zheng Yang
     */
    class IPointerEnter {
    public:


        /** @brief callback function for pointer enter events
         *
         *  callback function for pointer enter events
         *
         */
        virtual void                            onPointerEnter() = 0;
    };

    /** @brief interface for pointer leaves event handlers
     *
     *  interface for pointer enter event handlers
     *  when pointer leaves the bounding box of a gameobject, all the components on the gameobject that implements this
     *  interface will be notified
     *
     *  @author Zheng Yang
     */
    class IPointerLeave {
    public:
        /** @brief callback function for pointer leave events
         *
         *  callback function for pointer leave events
         *
         */
        virtual void                            onPointerLeave() = 0;
    };


    /** @brief interface for pointer presses event handlers
     *
     *  interface for pointer presses event handlers
     *  when player presses pointer inside the bounding box of a gameobject, all the components on the gameobject that implements this
     *  interface will be notified
     *
     *  @author Zheng Yang
     */
    class IPointerPress {
    public:

        /** @brief callback function for pointer press events
         *
         *  callback function for pointer press events
         *
         */
        virtual void                            onPointerPress() = 0;
    };



    /** @brief interface for pointer releases event handlers
     *
     *  interface for pointer releases event handlers
     *  when player releases pointer after pressing it inside the bounding box of a gameobject, all the components on the gameobject that implements this
     *  interface will be notified
     *
     *  @author Zheng Yang
     */
    class IPointerRelease {
    public:

        /** @brief callback function for pointer release events
         *
         *  callback function for pointer release events
         *
         */
        virtual void                            onPointerRelease() = 0;
    };


    /** @brief interface for pointer clicks event handlers
     *
     *  interface for pointer clicks event handlers
     *  when player click the pointer inside the bounding box of a gameobject(this means pointer must be clicked and released
     *  inside the same bounding box), all the components on the gameobject that implements this
     *  interface will be notified
     *
     *  @author Zheng Yang
     */
    class IPointerClick {
    public:

        /** @brief callback function for pointer click events
         *
         *  callback function for pointer click events
         *
         */
        virtual void                            onPointerClick() = 0;
    };
}

#endif //GAME_INPUTEVENTHANDLER_H
