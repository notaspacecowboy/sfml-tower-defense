//
// Created by Zheng Yang on 08/10/22.
//

#ifndef GAME_GAMEOBJECT_H
#define GAME_GAMEOBJECT_H
#include <string>
#include <vector>
#include <memory>
#include <assert.h>
#include <Utils/GuidGenerator.h>
#include "Components/Drawables/Sprite.h"

//forward declare
namespace game::core {
    class GameManager;
}

namespace game::components {


    /** @brief container class for a group of components
     *
     *  gameobject class functions as a pure container of a group of components that defines the behavior of a logical entity
     *  each gameobject has a unique runtime guid, and have a state identifier
     *
     *  @author Zheng Yang
     */
    class GameObject: private sf::NonCopyable {
        friend class game::core::GameManager;

    public:
        /** @brief all gameobject states
         *
         *  all gameobject states
         *
         *  @author Zheng Yang
         */
        enum class GoState {
            ACTIVE,                 /*!< gameobject is active */
            DISABLED,               /*!< gameobject is disabled */
            MARK_TO_DESTROY         /*!< gameobject is marked to be destroyed at the end of the frame */
        };


        /** @brief gameobject destructor
         *
         *  gameobject destructor
         *
         */
                                                        ~GameObject();

        /** @brief gameobject transform component getter
        *
        *  gameobject transform component getter
        *
        * @return  transform component
        */
        inline Transform*                               getTransform();


        /** @brief parent transform component getter
        *
        *  parent transform component getter
        *
        * @return  parent transform component
        */
        inline Transform*                               getParent();


        /** @brief gameobject guid component getter
        *
        *  gameobject guid getter
        *
        * @return  gameobject guid
        */
        inline GUID                                     getGUID() const;


        /** @brief reset the state of the gameobject
        *
        *  reset the state of the gameobject, this function can be called recursively if gameobjects has children
        *
        * @param state new state
        */
        void                                            setState(GoState state);


        /** @brief gameobject state getter
        *
        *  gameobject state getter
        *
        * @return  gameobject state
        */
        GoState                                         getState();


        /** @brief add a new component to gameobject
        *
        *  add a new component to gameobject
        *
        * @param args component constructor parameter list
        */
        template<class TComponent, typename... Args>
        TComponent*                                     addComponent(Args&&... args);



        /** @brief get a component from gameobject
        *
        *  get a component from gameobject based on its type
        *  this function uses runtime type check
        *
        */
        template<class TComponent>
        TComponent*                                     getComponent();


        /** @brief return a list of components which have a same base type
        *
        *  return a list of components which have a same base type
        *
        * @param components vector to hold the return value
        */
        template<class TComponent>
        void                                            getComponents(std::vector<TComponent*> &components);



        /** @brief remove a component from gameobject
        *
        *  remove a component from gameobject based on its type
        *  this function uses runtime type check
        *
        */
        template<class TComponent>
        bool                                            removeComponent();

    private:
        /** @brief gameobject constructor
         *
         *  private constructor to make sure GOs can only be managed by GameManager
         *
         */
                                                        GameObject(GUID id, GoState state = GoState::ACTIVE);

        /** @brief tick gameobject and its component list every frame
        *
        *  this function is called every frame to tick the gameobject and its components
        *
        */
        void                                            tick(float deltaTime);

        GUID                                            mID;                /*!< my guid */
        GoState                                         mState;             /*!< my state */
        std::vector<std::unique_ptr<Component>>         mComponents;        /*!< my component list */
        Transform*                                      mTransform;         /*!< my cached transform component */
    };
} // game::components

#include <Components/GameObject.inl>

#endif //GAME_GAMEOBJECT_H
