//
// Created by Zheng Yang on 05/11/22.
//

#ifndef GAME_GRIDLAYOUT_H
#define GAME_GRIDLAYOUT_H

#include "ILayoutController.h"
#include <Components/Component.h>
#include <SFML/System.hpp>


namespace game::components {
    class Sprite;

    /** @brief simple implementation of a layer controller
     *
     *  this is a simple implementation of a layer controller. it takes a group of drawables and layout them into m x n grid
     *
     *  @author Zheng Yang
     */
    class GridLayout: public Component, public IGridLayoutController {
    public:


        /** @brief GridLayout constructor
         *
         *  GridLayout constructor
         *
         *  @param owner owner of the component
         *  @param gridSize size of the grid
         *  @param gridMargin margin between grids
         *  @param elementSize size of each grid element
         */
                                                    GridLayout(game::components::GameObject &owner,
                                                               sf::Vector2i gridSize,
                                                               sf::Vector2i gridMargin,
                                                               sf::Vector2i elementSize);


        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is enabled
        *
        */
        void                                        onEnable() override;


        /** @brief set grid element size
        *
        * call this API to reset the size of grid elements after initialization
        *
        * @param width new width
        * @param height new height
        */
        void                                        setGridElementSize(int width, int height) override;


        /** @brief set margin between each grid element
        *
        * call this API to reset the margin between each grid element after initialization
        *
        * @param x new margin x
        * @param y new margin y
        */
        void                                        setMargin(int x, int y);


        /** @brief set size of grid
        *
        * call this API to reset the size of grid after initialization
        *
        * @param x new size in x-axis
        * @param y new size in y-axis
        */
        void                                        setGridSize(int x, int y);


        /** @brief add a new grid element
        *
        * call this API to add a new grid element
        *
        * @param element new grid element
        */
        void                                        addGridElement(game::components::Transform *element) override;


        /** @brief recalculate the width of the grid system
        *
        * recalculate the width of the grid system; called everytime a grid layout property got updated, or new element added
        *
        */
        void                                        setLayoutHorizontal() override;


        /** @brief recalculate the height of the grid system
        *
        * recalculate the height of the grid system; called everytime a grid layout property got updated, or new element added
        *
        */
        void                                        setLayoutVertical() override;


        /** @brief set position of a grid element
        *
        * set position of a grid element
        *
        * @param element element to be set
        * @p index new index
        */
        void                                        setElementPosition(Transform* element, int index) override;

    private:
        Transform*                                  mTransform;         /*!< my cached transform */
        sf::Vector2i                                mElementSize;       /*!< my element size */
        sf::Vector2i                                mGridSize;          /*!< my grid size */
        sf::Vector2f                                mGridMargin;        /*!< my margin between grid element */
    };
}



#endif //GAME_GRIDLAYOUT_H
