//
// Created by zyang464 on 24/10/22.
//

#include <Input/PointerData.h>
#include <Core/GameManager.h>

namespace game::input {
    using namespace game::core;

    PointerData::PointerData(game::input::MouseButton id)
            :buttonID(id)
            ,pos(sf::Vector2f(0, 0))
            ,deltaPos(sf::Vector2f(0,0))
            ,pressedThisFrame(false)
            ,pointerEnter(GameManager::getInstance().getEmptyGoHandle())
            ,pointerPressed(GameManager::getInstance().getEmptyGoHandle()) {
    }
}