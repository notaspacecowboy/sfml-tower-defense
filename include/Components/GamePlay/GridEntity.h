//
// Created by Zheng Yang on 22/11/22.
//

#ifndef GAME_GRIDENTITY_H
#define GAME_GRIDENTITY_H

#include <Components/Component.h>
#include <SFML/System/Vector2.hpp>
#include <Grid/GridLayer.h>

namespace game::components {


    /** @brief base class for all the drawables in the game
     *
     *  this is the base class for every game entity that can be put into the grid system (towers, enemies, projections...)
     *  we ensure a one-way dependency chain of grid system -> grid layer -> grid -> grid entity
     *
     *  @author Zheng Yang
     */
    class GridEntity: public Component {
    public:
        /** @brief grid entity constructor
         *
         *  grid entity constructor
         *
         *  @param owner owner of the component
         *  @param layer grid layer of entity
         */
                                    GridEntity(GameObject& owner, grid::GridLayer& layer);

        /** @brief grid entity destructor
        *
        *  grid entity destructor
        *
        */
                                    ~GridEntity();


        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is enabled
        *
        */
        void                        onEnable() override;

        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is disabled
        *
        */
        void                        onDisable() override;

        /** @brief recalculate the current grid of the grid entity
        *
        *  a lot of grid entities in the game are not static, such as enemies and projections.
        *  since they are always moving, we need to call this API to recalculate the grid a grid entity belongs to when
        *  it moves
        *
        */
        virtual void                calculateCurrentGrid();


        /** @brief unregister from current grid
        *
        *  unregister the current grid element from the grid
        *
        */
        virtual void                unregister();

        /** @brief grid index getter
        *
        *  get current grid index
        *
        * @return current grid index
        */
        sf::Vector2i                getGridIndex();


        /** @brief grid index setter
        *
        *  set current grid index
        *
        * @param x index in x axis
        * @param y index in y axis
        *
        */
        void                        setGridIndex(int x, int y);

    protected:
        grid::GridLayer&            mGridLayer;                 /*!< the layer of which the grid entity belongs to */
        sf::Vector2i                mCurrentGridIndex;          /*!< the index of the grid of which the grid entity is currently on */
        sf::Vector2i                mGridSize;                  /*!< size of the grid */
    };
}

#endif //GAME_GRIDENTITY_H
