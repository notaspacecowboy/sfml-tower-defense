//
// Created by Zheng Yang on 13/11/22.
//

#include <Grids.h>
#include <Core/GameManager.h>
#include <Components.h>
#include <Utils/Logger.h>
#include <math.h>

using namespace game::core;
using namespace game::components;
using namespace game::utils;

namespace game::grid {
    Grid::Grid(const ldtk::Tile &gridDefine, sf::Texture* tileMap, const sf::Vector2i size, const sf::Vector2i index, renderer::RenderLayer layer, int depth,bool repeated)
    : mGridDefine(gridDefine)
    , mTileMap(tileMap)
    , mIndex(index)
    , mRenderLayer(layer)
    , mDepth(depth)
    , mIsRepeated(repeated)
    , mEntities() {
        mRoot = GameManager::getInstance().instantiateGameObject(components::GameObject::GoState::DISABLED);
        auto go = mRoot.get();
        auto position = gridDefine.getWorldPosition();
        go->getTransform()->setSize(size.x, size.y);
        go->getTransform()->setLocalPosition( position.x, position.y);

        auto quad = go->addComponent<Quad>(layer, depth);
        auto texcoords = mGridDefine.getTextureRect();

        //this is a hacky solution to eliminate the line artifacts around each individual tiles
        quad->set(tileMap, sf::FloatRect(texcoords.x + 1, texcoords.y + 1, texcoords.width - 2, texcoords.height - 2));
        //auto sprite = go->addComponent<Sprite>(layer, depth);
        //sprite->setTexture(tileMap);
    }

    Grid::~Grid() {
        if(mRoot)
            mRoot->setState(components::GameObject::GoState::MARK_TO_DESTROY);

        mEntities.clear();
    }

    void Grid::setActive(bool isActive) {
        if(isActive) {
            mRoot->setState(components::GameObject::GoState::ACTIVE);
        }
        else {
            mRoot->setState(components::GameObject::GoState::DISABLED);
        }
    }

    void Grid::addEntity(components::GridEntity *entity) {
        auto find = std::find(mEntities.begin(), mEntities.end(), entity);
        if(find == mEntities.end())
            mEntities.emplace_back(entity);
    }

    void Grid::removeEntity(components::GridEntity *entity) {
        auto find = std::find(mEntities.begin(), mEntities.end(), entity);
        if(find != mEntities.end())
            mEntities.erase(find);
    }

    const std::vector<components::GridEntity *> &Grid::getAllEntities() const {
        return mEntities;
    }

    int Grid::getEntityCounts() const {
        return mEntities.size();
    }

    GoHandle Grid::getRoot() const {
        return mRoot;
    }

    sf::Vector2i Grid::getIndex() const {
        return mIndex;
    }
}