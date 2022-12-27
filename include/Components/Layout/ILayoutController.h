//
// Created by Zheng Yang on 05/11/22.
//

#ifndef GAME_IGRIDCONTROLLER_H
#define GAME_IGRIDCONTROLLER_H

namespace game::components {

    class Transform;


    /** @brief interface that a grid layer controller should follow
     *
     *  this defines a interface that a grid layer controller should follow
     *
     *  @author Zheng Yang
     */
    class IGridLayoutController {
    public:

        /** @brief set grid element size
        *
        * call this API to reset the size of grid elements after initialization
        *
        * @param width new width
        * @param height new height
        */
        virtual void                    setGridElementSize(int width, int height) = 0;


        /** @brief add a new grid element
        *
        * call this API to add a new grid element
        *
        * @param element new grid element
        */
        virtual void                    addGridElement(Transform* element) = 0;



        /** @brief recalculate the width of the grid system
        *
        * recalculate the width of the grid system; called everytime a grid layout property got updated, or new element added
        *
        */
        virtual void                    setLayoutHorizontal() = 0;


        /** @brief recalculate the height of the grid system
        *
        * recalculate the height of the grid system; called everytime a grid layout property got updated, or new element added
        *
        */
        virtual void                    setLayoutVertical() = 0;


        /** @brief set position of a grid element
        *
        * set position of a grid element
        *
        * @param element element to be set
        * @p index new index
        */
        virtual void                    setElementPosition(Transform* element, int index) = 0;
    };
}

#endif //GAME_IGRIDCONTROLLER_H
