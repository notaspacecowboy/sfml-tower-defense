//
// Created by Zheng Yang on 29/09/22.
//

#include "Core/GameManager.h"
#include "Components/GameObject.h"
#include <iostream>
#include <Input/InputManager.h>
#include <boost/signals2.hpp>
#include "Components/Drawables/Text.h"
#include <Data/ButtonDefine.h>
#include <States/StartState.h>
#include "Components/Animators/FadeInOutAnimator.h"

using namespace game::core;

void PrintPos(sf::Vector2f pos);
void testPivot();
void testAnchor();

int main() {
    //testPivot();
    //testAnchor();
    using namespace std;

    srand((unsigned)time(NULL));
    GameManager::getInstance().init();
    GameManager::getInstance().run();
}


void testAnchor() {
    using namespace game::components;
    using namespace std;


    GameObject* parent = GameManager::getInstance().instantiateGameObject(GameObject::GoState::ACTIVE).get();
    parent->getTransform()->setSize(1920, 1080);

    GameObject* son = GameManager::getInstance().instantiateGameObject(GameObject::GoState::ACTIVE).get();
    son->getTransform()->setSize(100, 100);
    son->getTransform()->setParent(parent->getTransform());
    son->getTransform()->setAnchor(ANCHOR_BOT_RIGHT);
    PrintPos(son->getTransform()->getLocalPosition());
    PrintPos(son->getTransform()->getWorldPosition());

    son->getTransform()->setLocalPosition(0, 0);
    PrintPos(son->getTransform()->getLocalPosition());
    PrintPos(son->getTransform()->getWorldPosition());

    parent->getTransform()->setPivot(PIVOT_CENTER);
    parent->getTransform()->setSize(500, 500);
    PrintPos(son->getTransform()->getLocalPosition());
    PrintPos(son->getTransform()->getWorldPosition());
}



//test pivot
void testPivot() {
    using namespace game::components;
    using namespace std;

    //test gameobject-component
    GameObject* go = GameManager::getInstance().instantiateGameObject(GameObject::GoState::ACTIVE).get();
    go->getTransform()->setSize(sf::Vector2f(5,5));

    go->getTransform()->setPivot(PIVOT_TOP_LEFT);
    PrintPos(go->getTransform()->getLocalPosition());
    go->getTransform()->setPivot(PIVOT_TOP_MIDDLE);
    PrintPos(go->getTransform()->getLocalPosition());
    go->getTransform()->setPivot(PIVOT_TOP_RIGHT);
    PrintPos(go->getTransform()->getLocalPosition());

    go->getTransform()->setPivot(PIVOT_MIDDLE_LEFT);
    PrintPos(go->getTransform()->getLocalPosition());
    go->getTransform()->setPivot(PIVOT_CENTER);
    PrintPos(go->getTransform()->getLocalPosition());
    go->getTransform()->setPivot(PIVOT_MIDDLE_RIGHT);
    PrintPos(go->getTransform()->getLocalPosition());

    go->getTransform()->setPivot(PIVOT_BOT_LEFT);
    PrintPos(go->getTransform()->getLocalPosition());
    go->getTransform()->setPivot(PIVOT_BOT_MIDDLE);
    PrintPos(go->getTransform()->getLocalPosition());
    go->getTransform()->setPivot(PIVOT_BOT_RIGHT);
    PrintPos(go->getTransform()->getLocalPosition());
}

void PrintPos(sf::Vector2f pos) {
    std::cout << "("
         << pos.x
         << ", "
         << pos.y
         << ")"
         << std::endl;
}

