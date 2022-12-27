//
// Created by Zheng Yang on 25/11/22.
//

#ifndef GAME_PROJECTION_H
#define GAME_PROJECTION_H

#include <Components/GamePlay/GridEntity.h>
#include <Data/ProjectionDefine.h>
#include <Data/TowerDefine.h>
#include <SFML/System/Vector2.hpp>
#include <Core/ObjectHandle.h>

namespace game::components {
    class CharacterAnimator;
    class Sprite;

    /** @brief base class for all types of projections in the game
     *
     *  in the current design, we do not necessarily need any derived class for projections. Instead, all projections behavior
     *  should be defined in the ProjectionDefine json file. So this class should be purely data driven and should be capable
     *  of handling any projection behavior defined in the json data file
     *
     *  @author Zheng Yang
     */
    class Projection: public Component {
    public:

        /** @brief projection constructor
         *
         *  projections constructor
         *
         *  @param owner owner of the component
         *  @param projectionData projection data
         *  @param towerData tower data
         */
                                                                        Projection(GameObject& owner,
              core::GoHandle target,
              const data::ProjectionDefine& projectionData,
              const data::TowerDefine& towerData);

        /** @brief projection destructor
        *
        *  projection destructor
        *
        */
                                                                        ~Projection();


        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is enabled
        *
        */
        void                                                            onEnable() override;

        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is disabled
        *
        */
        void                                                            onDisable() override;


        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically every frame. This is where every component in the game gets updated
        *
        * @param deltaTime the time elpased between now and last frame
        */
        void                                                            tick(float deltaTime) override;



        /** @brief calculate the distance between two positions
        *
        * calculate the distance between two positions
        *
        * @param pos1 position 1
        * @param pos2 postion 2
        * @return distance between these two positons
        */
        float                                                           getDistance(sf::Vector2f pos1, sf::Vector2f pos2);

    private:

        /** @brief register all of the enemies animation states to its character animator
        *
        * register all of the enemies animation states to its character animator
        */
        void                                                            registerAnimation();
        //void                                                            tickRotation();


        const data::ProjectionDefine&                                   mData;                      /*!< my projection data */
        const data::TowerDefine&                                        mAttackerData;              /*!< my attacker data */


        core::GoHandle                                                  mTarget;                    /*!< my target enemy */
        Sprite*                                                         mSprite;                    /*!< my sprite */
        CharacterAnimator*                                              mAnimator;                  /*!< my character animator */

    };
}


#endif //GAME_PROJECTION_H
