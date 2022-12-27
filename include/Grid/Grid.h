//
// Created by Zheng Yang on 13/11/22.
//

#ifndef GAME_GRID_H
#define GAME_GRID_H

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <LDtkLoader/Tile.hpp>
#include <Renderer/RenderLayer.h>
#include <Core/ObjectHandle.h>
#include <vector>
#include <boost/signals2.hpp>

namespace game::components {
    class GridEntity;
    class SimpleButton;
}

namespace game::grid {
    /** @brief class of a single grid cell
     *
     *  this is the class of a single grid cell, grids are managed by grid layers and they maintain references to all the
     *  grid entities that are currently on the grid
     *
     *  @author Zheng Yang
     */
    class Grid: sf::NonCopyable {
    public:
        /** @brief grid constructor
         *
         *  grid constructor
         *
         *  @param gridDefine grid data
         *  @param tileMap the background texture of the grid
         *  @param size size of the grid
         *  @param index index in the grid layer
         *  @param layer render layer
         *  @param depth depth in the render layer
         *  @param repeated should the grid sprite repeat itself when the size of the grid is greater than the size of the texture
         */
                                                        Grid(const ldtk::Tile& gridDefine,
                                                            sf::Texture* tileMap,
                                                            const sf::Vector2i size,
                                                            const sf::Vector2i index,
                                                            renderer::RenderLayer layer,
                                                            int depth,
                                                            bool repeated);

        /** @brief grid destructor
        *
        *  grid destructor
        *
        */
                                                        ~Grid();


        /** @brief active/deactive the sprite component of the grid
        *
        *  active/deactive the sprite component of the grid
        *
        */
        void                                            setActive(bool isActive);


        /** @brief add grid entity to the grid
        *
        *  call this function to add a grid entity to the grid, grid will then keep a reference of the grid entity
        *
        *  @param entity grid entity to be added
        */
        void                                            addEntity(components::GridEntity* entity);


        /** @brief remove grid entity from the grid
        *
        *  call this function to remove grid entity from the grid
        *
        *  @param entity grid entity to be added
        */
        void                                            removeEntity(components::GridEntity* entity);


        /** @brief return the list of all the grid entities currently on the grid
        *
        *  call this function to return the list of all the grid entities currently on the grid
        *
        *  @return the list of all the grid entities on the grid
        */
        const std::vector<components::GridEntity*>&     getAllEntities() const;


        /** @brief return the number of grid entities in the grid
        *
        *  call this function to return the number of grid entities in the grid
        *
        *  @return the number of grid entities in the grid
        */
        int                                             getEntityCounts() const;


        /** @brief get gameobject root
        *
        *  call this function to return root gameobject handle of the grid
        *
        *  @return root gameobject handle of the grid
        */
        core::GoHandle                                  getRoot() const;


        /** @brief get grid index
        *
        *  call this function to return grid index
        *
        *  @return grid index
        */
        sf::Vector2i                                    getIndex() const;

    private:
        std::vector<components::GridEntity*>            mEntities;          /*!< grid entities currently on the grid */
        const ldtk::Tile&                               mGridDefine;        /*!< grid data */
        sf::Texture*                                    mTileMap;           /*!< texture of grid background */
        sf::Vector2i                                    mIndex;             /*!< cached index in the grid layer */
        const renderer::RenderLayer                     mRenderLayer;       /*!< grid render layer */
        const int                                       mDepth;             /*!< grid depth in the render layer */
        core::GoHandle                                  mRoot;              /*!< grid root gameobject handle */
        bool                                            mIsRepeated;        /*!< is grid background sprite repeating */
    };
}

#endif //GAME_GRID_H
