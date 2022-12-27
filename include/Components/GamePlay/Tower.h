//
// Created by Zheng Yang on 25/11/22.
//

#ifndef GAME_TOWER_H
#define GAME_TOWER_H

#include <Components/GamePlay/GridEntity.h>
#include <Data/TowerDefine.h>
#include <SFML/System/Vector2.hpp>
#include <boost/signals2.hpp>

namespace game::components {

    /** @brief base class for all types of towers in the game
     *
     *  in the current design, we do not necessarily need any derived class for towers. Instead, all tower behavior
     *  should be defined in the TowerDefine json file. So this class should be purely data driven and should be capable
     *  of handling any tower behavior defined in the json data file
     *
     *  @author Zheng Yang
     */
    class Tower: public GridEntity {
    public:

        /** @brief Tower constructor
         *
         *  Tower constructor
         *
         *  @param owner owner of the component
         *  @param data tower data
         *  @param layer the grid layer of the tower entity
         */
        Tower(GameObject& owner,
              const data::TowerDefine& data,
              grid::GridLayer& towerLayer,
              grid::GridLayer& enemyLayer);

        /** @brief Tower destructor
        *
        *  Tower destructor
        *
        */
        ~Tower();


        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically every frame. This is where every component in the game gets updated
        *
        * @param deltaTime the time elpased between now and last frame
        */
        void                                                            tick(float deltaTime) override;


        /** @brief get enemy define
        *
        * get enemy define
        *
        * @return enemy define data
        */
        const data::TowerDefine&                                        getData() const;


        /** @brief final initialization of tower before render it to grid
        *
        * final initialization of tower before make it alive and put it to grid
        *
        */
        void                                                            spawn();

    private:

        /** @brief register all of the enemies animation states to its character animator
        *
        * register all of the enemies animation states to its character animator
        */
        void                                                            registerAnimation();


        /** @brief search the closest enemy that is in the tower's attack range
        *
        * search the closest enemy that is in the tower's attack range in the grid
        */
        GridEntity*                                                     searchEnemy();

        const data::TowerDefine&                                        mData;                          /*!< my enemy data */


        Sprite*                                                         mSprite;                        /*!< my sprite */
        CharacterAnimator*                                              mAnimator;                      /*!< my character animator */
        grid::GridLayer&                                                mEnemyLayer;                    /*!< enemy layer */
        float                                                           mTimeElapsedFromLastAttack;     /*!< the elapsed time from last tower attack */
        bool                                                            mIsSpawned;                     /*!< is the tower ready to attack */
    };
}

#endif //GAME_TOWER_H
