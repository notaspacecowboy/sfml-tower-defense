//
// Created by Zheng Yang on 28/10/22.
//

#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include "RenderComponent.h"
#include <SFML/Graphics.hpp>
#include <boost/signals2.hpp>

namespace game::components {

    /** @brief wrapper class for sf::sprite
     *
     *  if you want to draw something to the game window with a local texture, use this class
     *  must set up a referenced texture before it can be properly render to the game window
     *
     *  @author Zheng Yang
     */
    class Sprite: public RenderComponent {
    public:

        /** @brief sprite constructor
         *
         *  sprite constructor
         *
         *  @param owner owner of the component
         *  @param layer render layer of quad
         *  @param depth render depth of quad
         */
                                                    Sprite(GameObject& owner, renderer::RenderLayer layer, int depth);

        /** @brief sprite destructor
        *
        *  sprite destructor
        *
        */
                                                    ~Sprite() override;

        /** @brief draw quad to screen
        *
        *  do not call it - this function should only be called by game renderer every frame
        *  this is where drawable components actually gets drawed to the screen
        *
        *  @param window the game window to render the quad on
        */
        void                                        draw(sf::RenderWindow &window) override;

        /** @brief set the referenced texture
        *
        *  set the texture to be used by sprite object - texture must exist as long as the sprite uses it
        *
        *  @param texture new texture
        */
        void                                        setTexture(sf::Texture *texture);

        /** @brief set the referenced texture by using its unique identifier
        *
        *  set the texture to be used by sprite object - texture must exist as long as the sprite uses it
        *
        *  @param texture unique identifier of the new texture
        */
        void                                        setTexture(int tid);

        /** @brief set the texture coordinates of referenced texture
        *
        *  set the texture coordinates of referenced texture, this defines the region of the texture to be displayed
        *
        *  @param offsetX x position
        *  @param offsetY y position
        *  @param width width of the region of texture to be displayed
        *  @param height height of the region of texture to be displayed
        */
        void                                        setTextureRect(int offsetX, int offsetY, int width, int height);

        /** @brief set the size of the sprite to follow its native size
        *
        *  set the size of the sprite to follow its native size (size of the texture, or the region of the texture to be displayed)
        *
        */
        void                                        setSpriteNativeSize();

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

        /** @brief set the alpha value of the drawable
        *
        * set the alpha value of the drawable
        *
        * @param alpha 1 means entirely opaque, 0 means entirely transparent
        */
        void                                        setAlpha(float alpha) override;

        /** @brief set the color of the drawable
        *
        * set the color of the drawable
        *
        * @param color new color
        */
        void                                        setColor(sf::Color color);

    private:
        sf::Sprite                                  mSprite;                /*!< the actual sprite provided by sfml */
        sf::Texture*                                mReferencedTexture;     /*!< my referenced texture */
        sf::IntRect                                 mTextureRect;           /*!< the rigion of the texture to be displayed */
        Pivot                                       mPivot;                 /*!< my cached pivot */
        sf::Vector2f                                mSize;                  /*!< my cached size */
    };

}

#endif //GAME_SPRITE_H
