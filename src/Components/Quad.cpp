//
// Created by Zheng Yang on 15/11/22.
//

#include <Components.h>
#include <Utils/Logger.h>

using namespace game::utils;

namespace game::components {
    Quad::Quad(game::components::GameObject &owner, renderer::RenderLayer layer, int depth)
            : RenderComponent(owner, layer, depth)
            , mQuad(sf::Quads, 4)
            , mReferencedTexture(nullptr)
            , mTexCoords(0,0,0,0){
    }

    Quad::~Quad() {
    }

    void Quad::onEnable() {
        RenderComponent::onEnable();
    }

    void Quad::onDisable() {
        RenderComponent::onDisable();
    }

    void Quad::set(sf::Texture *texture, sf::FloatRect texCoords) {
        mReferencedTexture = texture;
        mTexCoords = texCoords;

        auto position = mTransform->getWorldPosition();
        auto size = mTransform->getSize();
        mQuad[0].position = position;

        mQuad[1].position = position;
        mQuad[1].position.x += size.x;

        mQuad[2].position = position;
        mQuad[2].position.x += size.x;
        mQuad[2].position.y += size.y;

        mQuad[3].position = position;
        mQuad[3].position.y += size.y;

        mQuad[0].texCoords.x = texCoords.left;
        mQuad[0].texCoords.y = texCoords.top;

        mQuad[1].texCoords.x = texCoords.left + texCoords.width;
        mQuad[1].texCoords.y = texCoords.top;

        mQuad[2].texCoords.x = texCoords.left + texCoords.width;
        mQuad[2].texCoords.y = texCoords.top + texCoords.height;

        mQuad[3].texCoords.x = texCoords.left;
        mQuad[3].texCoords.y = texCoords.top + texCoords.height;
    }

    bool Quad::isRaycastable() {
        if(mReferencedTexture != nullptr && mIsRaycastable)
            return true;

        return false;
    }

    void Quad::draw(sf::RenderWindow &window) {
        if(mReferencedTexture == nullptr)
            return;

        auto position = mTransform->getWorldPosition();
        auto size = mTransform->getSize();

        if(mSize != size) {
            mQuad[0].position = position;

            mQuad[1].position = position;
            mQuad[1].position.x += size.x;

            mQuad[2].position = position;
            mQuad[2].position.x += size.x;
            mQuad[2].position.y += size.y;

            mQuad[3].position = position;
            mQuad[3].position.y += size.y;

            mSize = size;
        }

        window.draw(mQuad, mReferencedTexture);
    }
}
