//
// Created by Zheng Yang on 06/11/22.
//

#ifndef GAME_PLAYERSTATE_H
#define GAME_PLAYERSTATE_H

#include <SFML/System/NonCopyable.hpp>
#include <Data/PlayerData.h>
#include "boost/signals2.hpp"

namespace game::core {
    typedef boost::signals2::signal<void(int)>      PlayerHpChangeDelegate;
    typedef boost::signals2::signal<void(int)>      PlayerPointChangeDelegate;
    typedef boost::signals2::signal<void(int)>      PlayerGoldChangeDelegate;
    typedef boost::signals2::signal<void(void)>     PlayerDeadDelegate;


    /** @brief data structure for player state during gameplay
     *
     *  this class maintains and updates player state during gameplay, and it offers some convinient APIs to easily
     *  write/read player state to/from save file
     *
     *  @author Zheng Yang
     */
    class PlayerState: private sf::NonCopyable {
    public:

        /** @brief PlayerState constructor
         *
         *  PlayerState constructor
         *
         */
                                                    PlayerState();


        /** @brief load player state from save file
         *
         *  load player state from save file
         *
         *  @param data player save file data
         */
        void                                        load(data::PlayerData* data);


        /** @brief save player state to game save file
         *
         *  save player state to game save file
         *
         *  @param data player save file data
         */
        void                                        save(data::PlayerData* data);


        /** @brief get current game level
         *
         *  get current game level
         *
         *  @return current game level
         */
        int                                         getGameLevel() const;


        /** @brief set current game level
         *
         *  set current game level
         *
         *  @param newLevel new game level
         */
        void                                        setGameLevel(int newLevel);


        /** @brief get current player hp
         *
         *  get current player hp
         *
         *  @return current player hp
         */
        int                                         getCurrentHP() const;


        /** @brief set current player hp
         *
         *  set current player hp
         *
         *  @param newHP new player hp
         */
        void                                        setHP(int newHP);


        /** @brief heal player hp
         *
         *  heal player hp
         *
         *  @param healAmount heal amount
         */
        void                                        heal(int healAmount);


        /** @brief decrease player hp
         *
         *  decrease player hp
         *
         *  @param damageAmount damage amount
         */
        void                                        damage(int damageAmount);


        /** @brief get current player point
         *
         *  get current player point
         *
         *  @return current player point
         */
        int                                         getCurrentPoint() const;


        /** @brief set current player point
         *
         *  set current player point
         *
         *  @param newPoint new player point
         */
        void                                        setPoint(int newPoint);


        /** @brief change player point with a certain amount
         *
         *  change player point with a certain amount
         *
         *  @param changedAmount change amount
         */
        void                                        changePoint(int changedAmount);


        /** @brief get current player gold
         *
         *  get current player gold
         *
         *  @return current player gold
         */
        int                                         getCurrentGold() const;


        /** @brief change player gold with a certain amount
         *
         *  change player gold with a certain amount
         *
         *  @param changedAmount change amount
         */
        void                                        changeGold(int changedAmount);


        /** @brief get current player gold
         *
         *  get current player gold
         *
         *  @return current player gold
         */
        const std::vector<int>&                     getCurrentPowerUps() const;


        /** @brief add new powerup item to player storage
         *
         *  add new powerup item to player storage
         *
         *  @param id unique id of the new item
         */
        void                                        addPowerUp(int id);


        /** @brief get current locked towers
         *
         *  get current player locked towers
         *
         *  @return current player locked towers
         */
        const std::vector<int>&                     getCurrentLockedTowers() const;

        /** @brief add new tower to player collection
         *
         *  add new tower to player collection
         *
         *  @param id unique id of the new tower
         */
        void                                        unlockTower(int id);


        /** @brief get current player completed achievements
         *
         *  get current player completed achievements
         *
         *  @return current player completed achievements
         */
        const std::vector<int>&                     getCurrentCompletedAchievements() const;


        /** @brief complete a achievement by its id
         *
         *  complete a achievement by its id
         *
         *  @param id unique id of the achievement
         */
        void                                        completeAchievement(int id);


        /** @brief reset player to initial state
         *
         *  reset player to initial state
         *
         */
        void                                        reset();

        PlayerHpChangeDelegate                      playerHpChangeEvent;            /*!< player hp change event */
        PlayerDeadDelegate                          playerDeadEvent;                /*!< player dead event */

        PlayerGoldChangeDelegate                    playerGoldChangeEvent;          /*!< player gold change event */
        PlayerPointChangeDelegate                   playerPointChangeEvent;         /*!< player point change event */


    private:
        int                                         mGameLevel;                     /*!< current game level */
        int                                         mHp;                            /*!< current player hp */
        int                                         mPoint;                         /*!< current player point */
        int                                         mCurrentGold;                   /*!< current player gold */
        std::vector<int>                            mPowerUps;                      /*!< current powerup items */
        std::vector<int>                            mUnlockedTowers;                /*!< current towers */
        std::vector<int>                            mCompletedAchievements;         /*!< all completed achievements */
    };
}
#endif //GAME_PLAYERSTATE_H
