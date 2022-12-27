//
// Created by Zheng Yang on 03/11/22.
//

#ifndef GAME_SHAPE_H
#define GAME_SHAPE_H

#include "RenderComponent.h"
#include <SFML/Graphics.hpp>

namespace game::components {

    /** @brief drawable for simple shapes without texture
     *
     *  if you want to draw a rectangle with pure color and no texture, use this component instead of sprite
     *
     *  @author Zheng Yang
     */
    class Shape: public RenderComponent {
    public:
        /** @brief shape constructor
         *
         *  shape constructor
         *
         *  @param owner owner of the component
         *  @param layer render layer of quad
         *  @param depth render depth of quad
         */
                                                Shape(GameObject& owner, sf::Color color, renderer::RenderLayer layer, int depth);

        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is enabled
        *
        */
        void                                    onEnable() override;

        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is disabled
        *
        */
        void                                    onDisable() override;

        /** @brief draw quad to screen
         *
         *  do not call it - this function should only be called by game renderer every frame
         *  this is where drawable components actually gets drawed to the screen
         *
         *  @param window the game window to render the quad on
         */
        void                                    draw(sf::RenderWindow &window) override;

        /** @brief set the alpha value of the drawable
        *
        * set the alpha value of the drawable
        *
        * @param alpha 1 means entirely opaque, 0 means entirely transparent
        */
        void                                    setAlpha(float alpha) override;

    private:
        sf::Color                               mColor;         /*!< my current color */
        sf::RectangleShape                      mShape;         /*!< the actual shape provided by sfml */
    };
}

#endif //GAME_SHAPE_H
