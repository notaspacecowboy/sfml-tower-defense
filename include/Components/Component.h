//
// Created by Zheng Yang on 08/10/22.
//

#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

#include <SFML/System/NonCopyable.hpp>
#include <Utils/GuidGenerator.h>

namespace game::components {
    class GameObject;


    /** @brief base class for all components
     *
     *  this is the base class for all derived components. It defines a series of life cycle functions that gets called
     *  at a certain point of a component's lifetime. All components are managed by gameobjects.
     *  lifetime design: construct -> onenable -> tick^* -> ondisable -> destruct
     *  component can be enabled and disabled before destruct to restart its lifetime
     *
     *  @author Zheng Yang
     */
    class Component: private sf::NonCopyable {
            friend class GameObject;
    public:


        /** @brief get component owner
         *
         *  get component owner
         *
         *  @return owner of the component
         */
        GameObject&                     getGameObject();


        /** @brief Component constructor
         *
         *  Component constructor
         *
         *  @param owner owner of the component
         */
        virtual                         ~Component() { }


        /** @brief get owner guid
         *
         *  get owner guid
         *
         *  @return  owner guid
         */
        GUID                            getGUID() const;

    protected:


        /** @brief Component constructor
         *
         *  Component constructor
         *
         *  @param owner owner of the component
         */
                                        Component(GameObject &owner);

        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is enabled
        *
        */
        virtual void                    onEnable();


        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically every frame. This is where every component in the game gets updated
        *
        * @param deltaTime the time elpased between now and last frame
        */
        virtual void                    tick(float deltaTime);


        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is disabled
        *
        */
        virtual void                    onDisable();

        GameObject&                     mOwner;          /*!< my owner */

    };

} // game::components

#endif //GAME_COMPONENT_H
