//
// Created by Zheng Yang on 13/11/22.
//

#include <Grids.h>
#include <Data.h>
#include <Resource/ResourceManager.h>
#include <Utils/Logger.h>

using namespace game::data;
using namespace game::resource;
using namespace game::renderer;
using namespace game::utils;

namespace game::grid {
    GridLayer::GridLayer(Layer layer, const ldtk::Layer &layerDefine, const LayerInfo layerInfo, const sf::Vector2i size)
    : mLayerID(layer)
    , mLayerDefine(layerDefine)
    , mLayerInfo(layerInfo)
    , mSize(size)
    , mGridCellSize(size.x / layerDefine.getGridSize().x, size.y / layerDefine.getGridSize().y)
    , mGridSize(layerDefine.getGridSize().x, layerDefine.getGridSize().y){
        const auto& tileset = mLayerDefine.getTileset();

        auto texture = TextureManager::getInstance().getByName(tileset.name);
        texture->setSmooth(false);

        int i = 0;
        for(const auto& tile: layerDefine.allTiles()) {
            auto pos = tile.getGridPosition();
            int index = pos.y *mGridSize.x + pos.x;
            mIndexToGridMapping.insert(std::make_pair(index, i++));
            mGrids.emplace_back(new Grid(tile, texture, mGridCellSize, sf::Vector2i(pos.x, pos.y), layerInfo.renderLayer, layerInfo.depth, false));
        }
    }

    GridLayer::~GridLayer() {
        mGrids.clear();
    }

    void GridLayer::setActive(bool isActive) {
        for(auto &grid: mGrids) {
            grid->setActive(isActive);
        }
    }

    const std::vector<std::unique_ptr<Grid>> &GridLayer::getAllGrids() const {
        return mGrids;
    }

    Layer GridLayer::getLayerID() const {
        return mLayerID;
    }

    const sf::Vector2i &GridLayer::getGridSize() const {
        return mGridSize;
    }

    const sf::Vector2i &GridLayer::getGridCellSize() const {
        return mGridCellSize;
    }

    void GridLayer::registerGridEntity(components::GridEntity *entity, int gridIndexX, int gridIndexY) {
        if(gridIndexX < 0 || gridIndexY < 0)
            return;

        //Logger::log("add entity at index: (" + std::to_string(gridIndexX) + ", " + std::to_string(gridIndexY) + ")", 5);
        int index = gridIndexY * mGridSize.x + gridIndexX;
        int realIndex = mIndexToGridMapping[index];
        mGrids[realIndex]->addEntity(entity);
    }

    void GridLayer::unRegisterGridEntity(components::GridEntity *entity, int gridIndexX, int gridIndexY) {
        if(gridIndexX < 0 || gridIndexY < 0)
            return;

        //Logger::log("remove entity at index: (" + std::to_string(gridIndexX) + ", " + std::to_string(gridIndexY) + ")", 5);
        int index = gridIndexY * mGridSize.x + gridIndexX;
        int realIndex = mIndexToGridMapping[index];
        mGrids[realIndex]->removeEntity(entity);
    }

    Grid *GridLayer::getGridByWorldPosition(sf::Vector2f worldPos) {
        int indexX = worldPos.x / mGridCellSize.x;
        int indexY = worldPos.y / mGridCellSize.y;

        Logger::log(sf::Vector2i(indexX, indexY), 5);
        return getGridByIndex(indexX, indexY);
    }

    Grid *GridLayer::getGridByIndex(int gridIndexX, int gridIndexY) {
        if(gridIndexX < 0 || gridIndexY < 0)
            return nullptr;

        int index = gridIndexY * mGridSize.x + gridIndexX;
        auto find = mIndexToGridMapping.find(index);
        if(find != mIndexToGridMapping.end())
            return mGrids[find->second].get();

        return nullptr;
    }
}