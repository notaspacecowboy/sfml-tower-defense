//
// Created by Zheng Yang on 14/11/22.
//

#ifndef GAME_QUAD_H
#define GAME_QUAD_H

#include <Components/Drawables/RenderComponent.h>

namespace game::components {

    /** @brief drawables to make use of the vertex array provided by SFML
     *
     *  currently, this class is only used with tiles in the grid system to eliminate black artifacts at the edge of the tile,
     *  if you want to draw normal GUI elements, use Sprite class instead
     *
     *  @author Zheng Yang
     */
    class Quad: public RenderComponent {
    public:

        /** @brief quad constructor
         *
         *  quad constructor
         *
         *  @param owner owner of the component
         *  @param layer render layer of quad
         *  @param depth render depth of quad
         */
        Quad(GameObject& owner, renderer::RenderLayer layer, int depth);

        /** @brief quad destructor
         *
         *  quad destructor
         *
         */
        ~Quad() override;

        /** @brief draw quad to screen
         *
         *  do not call it - this function should only be called by game renderer every frame
         *  this is where drawable components actually gets drawed to the screen
         *
         *  @param window the game window to render the quad on
         */
        void                                        draw(sf::RenderWindow &window) override;

        /** @brief set the texture to be used for rendering, and set the texture coordinate in the texture that we want to draw with
         *
         *  must call this function before a quad can be properly draw to the screen
         *  set the texture to be used for rendering, and set the texture coordinate in the texture that we want to draw with
         *
         *  @param texture the texture to be drawn with
         *  @param texCoords the texture coordinate in the texture that we want to draw with
         */
        void                                        set(sf::Texture *texture, sf::FloatRect texCoords);

        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is enabled
        *
        */
        void                                        onEnable() override;

        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is disabled
        *
        */
        void                                        onDisable() override;

        /** @brief determines if a render component can be detected by input system and block pointer
        *
        * determines if a render component can be detected by input system
        *
        * @return true if drawable can be detected by pointer, false otherwise
        */
        bool                                        isRaycastable() override;

    private:
        sf::VertexArray                             mQuad;                  /*!< the actually vertexes provided by sfml */
        sf::Texture*                                mReferencedTexture;     /*!< the texture to be drawn with */
        sf::FloatRect                               mTexCoords;             /*!< the texture coordinates on the referenced texture to be drawn with */
        sf::Vector2f                                mSize;                  /*!< cached size of the drawable */
    };
}

#endif //GAME_QUAD_H
