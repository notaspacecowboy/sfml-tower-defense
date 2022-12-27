//
// Created by Zheng Yang on 18/11/22.
//

#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H

#include <Components/GamePlay/GridEntity.h>
#include <Data/EnemyDefine.h>
#include <Data/TowerDefine.h>
#include <SFML/System/Vector2.hpp>

namespace game::components {
    class CharacterAnimator;
    class Sprite;
    class Enemy;

    typedef boost::signals2::signal<void(const data::EnemyDefine*)>                       EnemyArriveDestinationDelegate;
    typedef boost::signals2::signal<void(const data::EnemyDefine*)>                       EnemyDeadDelegate;

    /** @brief base class for all types of enemies in the game
     *
     *  in the current design, we do not necessarily need any derived class for enemies. Instead, all enemy behavior
     *  should be defined in the EnemyDefine json file. So this class should be purely data driven and should be capable
     *  of handling any enemy behavior defined in the json data file
     *
     *  @author Zheng Yang
     */
    class Enemy: public GridEntity {
    public:

        /** @brief enemy constructor
         *
         *  enemy constructor
         *
         *  @param owner owner of the component
         *  @param data enemy data
         *  @param path path that enemy must follows during its lifetime
         *  @param layer the grid layer of the enemy entity
         */
                                                                        Enemy(GameObject& owner,
                                                                              const data::EnemyDefine& data,
                                                                              const std::vector<sf::Vector2i>* path,
                                                                              grid::GridLayer& layer);

        /** @brief enemy destructor
        *
        *  enemy destructor
        *
        */
                                                                        ~Enemy();

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


        /** @brief final initialization of enemy before render it to grid
        *
        * final initialization of enemy before make it alive and put it to grid
        *
        */
        void                                                            spawn();


        /** @brief final initialization of enemy before render it to grid
        *
        * final initialization of enemy before make it alive and put it to grid
        *
        */
        void                                                            hurt(const data::TowerDefine* attacker);

        /** @brief change enemy sprite direction based on its moving direction
        *
        * change enemy sprite direction based on its moving direction
        *
        * @param position new destination
        */
        void                                                            faceTo(sf::Vector2f position);


        /** @brief change enemy sprite direction based on its moving direction
        *
        * change enemy sprite direction based on its moving direction
        *
        * @param position new destination
        */
        void                                                            faceTo(sf::Vector2i position);


        /** @brief get enemy define
        *
        * get enemy define
        *
        * @return enemy define data
        */
        const data::EnemyDefine&                                        getData() const;

        EnemyDeadDelegate                                               onEnemyDead;                    /*!< enemy dead event */
        EnemyArriveDestinationDelegate                                  onEnemyArriveDestination;       /*!< enemy arrive its destination event */

    private:


        /** @brief enemy dead animation complete event handler
        *
        * this is the callback function for enemy dead animation complete event
        *
        */
        void                                                            onDeadAnimationComplete();

        /** @brief register all of the enemies animation states to its character animator
        *
        * register all of the enemies animation states to its character animator
        */
        void                                                            registerAnimation();

        /** @brief called every frame to update enemy position
        *
        * this function is called every frame to recalculate its current position
        */
        void                                                            tickMovement();
        //void                                                            tickRotation();

        /** @brief find enemies next destination
        *
        * when enemy reaches one of the destination defined in the path, call this function to find its next destination
        */
        void                                                            calculateTimeToNextPos();

        const data::EnemyDefine&                                        mData;                      /*!< my enemy data */

        const std::vector<sf::Vector2i>*                                mPath;                      /*!< my patrol path */
        int                                                             mNextPos;                   /*!< my next destination */
        float                                                           mTimeToNextPos;             /*!< total time to move to next destination */
        float                                                           mCurrentTime;               /*!< current time elapsed from reaching last destination */

//        bool                                                            mIsRotating;
//        float                                                           mStartAngle;
//        float                                                           mRotateAngle;
//        float                                                           mTimeToFinishRotate;

        Sprite*                                                         mSprite;                    /*!< my sprite */
        CharacterAnimator*                                              mAnimator;                  /*!< my character animator */
        int                                                             mCurrentHP;                 /*!< my current hp */
        bool                                                            mIsAlive;                   /*!< enemy state flag */

        boost::signals2::connection                                     mDeadAnimCompleteListener;  /*!< dead animation complete event listener */

    };
}

#endif //GAME_ENEMY_H
