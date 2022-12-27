//
// Created by Zheng Yang on 24/10/22.
//

#include "Utils/TransformUtility.h"

namespace game::utils {
    sf::Vector2f TransformUtility::mapScreenPointToWorldPos(sf::RenderWindow &window, sf::View &camera, sf::Vector2i screenPos) {
        return window.mapPixelToCoords(screenPos, camera);
    }

    bool TransformUtility::rectangleContainsScreenPoint(sf::RenderWindow &window, sf::View &camera, sf::Vector2i screenPos, sf::FloatRect rect) {
        auto worldPos = mapScreenPointToWorldPos(window, camera, screenPos);
        return rect.contains(worldPos.x, worldPos.y);
    }
}
