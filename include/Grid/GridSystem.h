//
// Created by Zheng Yang on 12/11/22.
//

#ifndef GAME_GRIDSYSTEM_H
#define GAME_GRIDSYSTEM_H

#include <SFML/System/NonCopyable.hpp>
#include <string>
#include <LDtkLoader/Level.hpp>
#include <LDtkLoader/World.hpp>
#include <Grid/GridLayer.h>
#include <unordered_map>
#include <Renderer/RenderLayer.h>


namespace game::grid {


    /** @brief grid system that manages a group of grid layers
     *
     *  grid system class manages a group of grid layers, each grid layer manages a group of grid cells, each grid cell
     *  manages a group of grid entities. This ensures a one-way dependency in the grid module
     *
     *  @author Zheng Yang
     */
    class GridSystem: private sf::NonCopyable {
    public:

        /** @brief grid system constructor
         *
         *  grid system constructor
         *
         */
                                                                    GridSystem();


        /** @brief register a grid layer
         *
         *  register a grid layer which will be generated later when game starts
         *
         *  @param layer layer identifier
         *  @param layerName name of the layer
         *  @param renderLayer render layer of the grid layer
         *  @param depth depth in the render layer
         *  @param isBackground is this the background layer
         */
        void                                                        registerLayer(Layer layer,
                                                                                  std::string layerName,
                                                                                  renderer::RenderLayer renderLayer,
                                                                                  int depth,
                                                                                  bool isBackground);


        /** @brief load a game level
         *
         *  load a game level based on level number
         *
         *  @param levelDefine game level data
         */
        void                                                        loadLevel(const ldtk::Level* level);


        /** @brief unload resources used in the grid system
         *
         *  unload resources used in the grid system before a new game level starts
         *
         */
        void                                                        unload();


        /** @brief activate/deactivate grid layers
         *
         *  activate/deactivate all grid layers in the grid system
         *
         *  @param isActive activate or deactivate
         */
        void                                                        setActive(bool isActive);


        /** @brief world size getter
         *
         *  get the world size of the currently loaded game level
         *
         *  @return world size of current game level
         */
        sf::Vector2i                                                getWorldSize() const;

        /** @brief grid layer getter
         *
         *  get a specific grid layer based on its unique identifier
         *
         *  @return grid layer
         */
        GridLayer*                                                  getGridLayerByID(grid::Layer layer);

    private:
        std::unordered_map<Layer, const LayerInfo>                  mLayerToInfoMapping;        /*!< grid id to static data mapping */
        std::vector<std::unique_ptr<GridLayer>>                     mActiveLayers;              /*!< all active grid layers */
        const ldtk::Level*                                          mCurrentLoadedLevel;        /*!< current game level data */
    };
}

#endif //GAME_GRIDSYSTEM_H
