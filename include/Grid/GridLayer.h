//
// Created by Zheng Yang on 12/11/22.
//

#ifndef GAME_GRIDLAYER_H
#define GAME_GRIDLAYER_H

#include <string>
#include <Renderer/RenderLayer.h>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <LDtkLoader/Layer.hpp>
#include <SFML/Graphics.hpp>

namespace game::components {
    class GridEntity;
}

namespace game::grid {
    class GridSystem;
    class Grid;


    /** @brief all the grid layers
     *
     *  this enum defines all the grid layers
     *
     *  @author Zheng Yang
     */
    enum Layer {
        BACKGROUND,         /*!< background layer */
        PATH,               /*!< path layer - this is where enemies are at */
        SLOTS,              /*!< slot layer - this is where towers are at */
        DECORATIONS         /*!< decoration layer */
    };


    /** @brief layer data
     *
     *  this data structure defines all the static information of a layer
     *
     *  @author Zheng Yang
     */
    struct LayerInfo {
        std::string                                     layerName;          /*!< layer name */
        game::renderer::RenderLayer                     renderLayer;        /*!< render layer of grids in the grid layer */
        int                                             depth;              /*!< depth in the render layer */
        bool                                            isBackground;       /*!< true if it is the background layer, otherwise false */
    };

    /** @brief grid layer that manages a group of grid cells
     *
     *  grid layer class manages a group of grid cells, this is to ensure grid entities can only interact with entities in the same
     *  layer - for example, enemies can only interact with enemies and towers can only interact with towers
     *
     *  @author Zheng Yang
     */
    class GridLayer: private sf::NonCopyable {
    public:

        /** @brief grid layer constructor
         *
         *  grid layer constructor
         *
         *  @param layer grid layer enum
         *  @param layerDefine layer data
         *  @param layerInfo layer static info
         *  @param size grid size
         */
                                                        GridLayer(Layer layer, const ldtk::Layer& layerDefine, const LayerInfo layerInfo, const sf::Vector2i size);


        /** @brief grid layer destructor
         *
         *  grid layer destructor
         *
         */
                                                        ~GridLayer();


        /** @brief activate/deactivate all the grid cells in this grid layer
         *
         *  activate/deactivate all the grid cells in this grid layer
         *
         *  @param isActive activate or deactivate
         */
        void                                            setActive(bool isActive);


        /** @brief get all grid cells in this grid layer
         *
         *  get all grid cells in this grid layer
         *
         *  @return a list of grids which are all belong to the current grid layer
         */
        const std::vector<std::unique_ptr<Grid>>&       getAllGrids() const;


        /** @brief grid layer identifier getter
         *
         *  get identifier of the current grid layer
         *
         *  @return identifier of the current grid layer
         */
        Layer                                           getLayerID() const;

        /** @brief get grid based on world position
         *
         *  this function takes a point in the world and find if the bounding box of any grid in the current layer contains that point
         *
         *  @param worldPos world position
         *  @return grid if found, nullptr otherwise
         */
        Grid*                                           getGridByWorldPosition(sf::Vector2f worldPos);


        /** @brief get grid based on its index
         *
         *  this function takes a grid index and returns a grid based on its index
         *
         *  @param gridIndexX grid index in x axis
         *  @param gridIndexY grid index in y axis
         *  @return grid if found, nullptr otherwise
         */
        Grid*                                           getGridByIndex(int gridIndexX, int gridIndexY);


        /** @brief grid layer size getter
         *
         *  get size of the current grid layer
         *
         *  @return size of the current grid layer
         */
        const sf::Vector2i&                             getGridSize() const;


        /** @brief grid cell size getter
         *
         *  get size of the grid cell
         *
         *  @return size of the grid cell
         */
        const sf::Vector2i&                             getGridCellSize() const;


        /** @brief add a grid entity to one of the grid in current grid layer
         *
         *  add a grid entity to one of the grid in current grid layer based on the grid index
         *
         *  @param entity grid entity to be added
         *  @param gridIndexX index of the grid in x-axis
         *  @param gridIndexY index of the grid in y-axis
         */
        void                                            registerGridEntity(components::GridEntity* entity, int gridIndexX, int gridIndexY);


        /** @brief remove a grid entity from one of the grid in current grid layer
         *
         *  remove a grid entity from one of the grid in current grid layer based on the grid index
         *
         *  @param entity grid entity to be removed
         *  @param gridIndexX index of the grid in x-axis
         *  @param gridIndexY index of the grid in y-axis
         */
        void                                            unRegisterGridEntity(components::GridEntity* entity, int gridIndexX, int gridIndexY);

    private:
        Layer                                           mLayerID;               /*!< grid layer identifier */
        const sf::Vector2i                              mSize;                  /*!< grid layer size */
        const sf::Vector2i                              mGridCellSize;          /*!< grid cell size */
        const sf::Vector2i                              mGridSize;              /*!< number of grids in column and rows */
        const LayerInfo                                 mLayerInfo;             /*!< grid static info */
        const ldtk::Layer&                              mLayerDefine;           /*!< grid data */
        std::vector<std::unique_ptr<Grid>>              mGrids;                 /*!< all grids */
        std::unordered_map<int, int>                    mIndexToGridMapping;    /*!< grid index to grid reference mapping */
    };
}




#endif //GAME_GRIDLAYER_H
