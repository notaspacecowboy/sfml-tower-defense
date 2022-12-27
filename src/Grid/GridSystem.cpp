//
// Created by Zheng Yang on 12/11/22.
//

#include <Grid/GridSystem.h>
#include <Utils/Logger.h>
using namespace game::renderer;
using namespace game::utils;

namespace game::grid {
    const std::string MAP_HP_FIELD          = "PlayerInitialHP";
    const std::string MAP_POINT_FIELD       = "PlayerInitialPoint";

    GridSystem::GridSystem()
    : mCurrentLoadedLevel(nullptr) {
    }

    void GridSystem::registerLayer(Layer layer, std::string layerName, RenderLayer renderLayer, int depth, bool isBackground) {
        mLayerToInfoMapping.insert(std::make_pair(layer, LayerInfo {layerName, renderLayer, depth, isBackground}));
    }

    void GridSystem::loadLevel(const ldtk::Level *level) {
        mActiveLayers.clear();

        mCurrentLoadedLevel = level;
        Logger::log("loading game world: " + level->name, 5);

        for(auto iter: mLayerToInfoMapping) {
            auto layerInfo = iter.second;
            const auto& layerDefine = level->getLayer(layerInfo.layerName);
            mActiveLayers.emplace_back(new GridLayer(iter.first,
                                                     layerDefine,
                                                     layerInfo,
                                                     sf::Vector2i(level->size.x, level->size.y)));
        }
    }

    void GridSystem::unload() {
        mActiveLayers.clear();

        mCurrentLoadedLevel = nullptr;
    }

    void GridSystem::setActive(bool isActive) {
        if(mActiveLayers.empty())
            return;

        for(auto& layer: mActiveLayers) {
            layer->setActive(isActive);
        }
    }

    sf::Vector2i GridSystem::getWorldSize() const {
        if(mCurrentLoadedLevel != nullptr) {
            auto size = mCurrentLoadedLevel->size;
            return sf::Vector2i(size.x, size.y);
        }

        utils::Logger::log("level has not been loaded yet!");
        return sf::Vector2i(0, 0);
    }

    GridLayer *GridSystem::getGridLayerByID(grid::Layer layer) {
        for(auto& gridLayer: mActiveLayers) {
            if(gridLayer->getLayerID() == layer)
                return gridLayer.get();
        }

        return nullptr;
    }
}

