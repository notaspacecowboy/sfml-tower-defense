//
// Created by Zheng Yang on 24/10/22.
//

#ifndef GAME_TRANSFORMUTILITY_H
#define GAME_TRANSFORMUTILITY_H

#include <SFML/Graphics.hpp>

namespace game::utils {

    /** @brief a static class to deal with coordinate transform and collision detection
     *
     *  This class is pure static and is meant to deal with coordinate transform and collision detection
     *
     *  @author Zheng Yang
     */
    class TransformUtility {
    public:
        /** @brief transform a point from screen point to world space
        *
        *  this function takes a camera and a point in the screen space, and calculate the position of the point in world space
        *
        *  @param window current game window
        *  @param camera game camera, which is the origin of the world space
        *  @param screenPos the screen position to be transformed
        *  @return the point in the world space
        */
        static sf::Vector2f                 mapScreenPointToWorldPos(sf::RenderWindow &window, sf::View &camera, sf::Vector2i screenPos);

        /** @brief check if a point in the screen space is in a rectangle bounding box of world space
        *
        *  this function takes a camera, a point in the screen space, and a bounding box in world space, and it
        *  calculate check if the point is inside the rectangle bounding box
        *
        *  @param window current game window
        *  @param camera game camera, which is the origin of the world space
        *  @param screenPos the screen position to be transformed
        *  @param rect the rect bounding box in world space
        *  @return the point in the world space
        */
        static bool                         rectangleContainsScreenPoint(sf::RenderWindow &window, sf::View &camera, sf::Vector2i screenPos, sf::FloatRect rect);
    };
}


#endif //GAME_TRANSFORMUTILITY_H
