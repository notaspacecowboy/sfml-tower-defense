//
// Created by Zheng Yang on 22/11/22.
//

#include <Components.h>
#include <Grids.h>

using namespace game::grid;

namespace game::components {
    GridEntity::GridEntity(game::components::GameObject &owner, grid::GridLayer& layer)
    : Component(owner)
    , mGridLayer(layer)
    , mGridSize(layer.getGridCellSize())
    , mCurrentGridIndex(-1, -1) {
    }

    GridEntity::~GridEntity() noexcept {
    }

    void GridEntity::onEnable() {
        mGridLayer.registerGridEntity(this, mCurrentGridIndex.x, mCurrentGridIndex.y);
    }

    void GridEntity::onDisable() {
        mGridLayer.unRegisterGridEntity(this, mCurrentGridIndex.x, mCurrentGridIndex.y);
    }

    void GridEntity::calculateCurrentGrid() {
        sf::Vector2f worldPos = mOwner.getTransform()->getWorldPosition();
        sf::Vector2i newGrid((int)worldPos.x / mGridSize.x, (int)worldPos.y / mGridSize.y);
        if(mCurrentGridIndex.x == newGrid.x && mCurrentGridIndex.y == newGrid.y)
            return;

        mGridLayer.unRegisterGridEntity(this, mCurrentGridIndex.x, mCurrentGridIndex.y);
        mGridLayer.registerGridEntity(this, newGrid.x, newGrid.y);

        mCurrentGridIndex = newGrid;
    }

    void GridEntity::unregister() {
        mGridLayer.unRegisterGridEntity(this, mCurrentGridIndex.x, mCurrentGridIndex.y);
    }

    sf::Vector2i GridEntity::getGridIndex() {
        return mCurrentGridIndex;
    }

    void GridEntity::setGridIndex(int x, int y) {
        mCurrentGridIndex.x = x;
        mCurrentGridIndex.y = y;
        mGridLayer.unRegisterGridEntity(this, mCurrentGridIndex.x, mCurrentGridIndex.y);
        mGridLayer.registerGridEntity(this, x, y);
    }
}
