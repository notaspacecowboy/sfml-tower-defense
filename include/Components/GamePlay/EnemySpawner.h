//
// Created by zyang464 on 20/11/22.
//

#ifndef GAME_ENEMYSPAWNER_H
#define GAME_ENEMYSPAWNER_H

#include <Components/Component.h>
#include <Data/EnemySpawnRuleDefine.h>
#include <SFML/System/Vector2.hpp>
#include <LDtkLoader/Level.hpp>
#include <boost/signals2.hpp>

namespace game::grid {
    class GridSystem;
};

namespace game::components {
    class Enemy;
    class GameObject;

    typedef boost::signals2::signal<void(Enemy*)>                        EnemySpawnedDelegate;
    typedef boost::signals2::signal<void()>                              AllEnemiesSpawnedDelegate;

    /** @brief enemy spawner class used to generate new enemies during gameplay
     *
     *  this class handles enemy generation & initialization when player hit the generate button
     *
     *  @author Zheng Yang
     */
    class EnemySpawner: public Component {
    public:

        /** @brief enemy spawner constructor
         *
         *  enemy spawner constructor
         *
         *  @param owner owner of the component
         *  @param world the game world data
         *  @param gridSystem the grid system on where enemies are put
         */
                                                                        EnemySpawner(GameObject& owner,
                                                                                     grid::GridSystem* gridSystem);

        /** @brief enemy spawner destructor
        *
        *  enemy spawner destructor
        *
        */
                                                                        ~EnemySpawner();


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


        /** @brief load the necessary information of enemies in a certain game level
        *
        * load the necessary information (path, hp modifier) of enemies in a certain game level
        *
        * @param level the new game level
        */
        void                                                            loadLevel(const ldtk::Level* level);

        /** @brief call this API to start spawning enemies
        *
        * call this API to start spawning enemies, enemies are not generated all together at once, the actual generation
        * is done in tick()
        *
        */
        void                                                            Spawn();

        /** @brief check if the fights are over
        *
        * check if the fights are over
        *
        * @return true if fights are over, otherwise false
        */
        bool                                                            hasMoreFights() const;


        /** @brief get the current fight number
        *
        * get the current fight number
        *
        * @return current fight number
        */
        int                                                             getCurrentFightIndex() const;

        /** @brief get total number of fights in current game level
        *
        *  get total number of fights in current game level
        *
        * @return total number of fights in current game level
        */
        int                                                             getTotalFights() const;


        EnemySpawnedDelegate                                            onEnemySpawned;                  /*!< enemy spawned event */
        AllEnemiesSpawnedDelegate                                       onAllEnemiesSpawned;             /*!< all enemy in current fight spawned event */

    private:
        const data::EnemySpawnRuleDefine*                               mData;                          /*!< spawn rule data */
        const ldtk::Level*                                              mGameLevel;                     /*!< cached game world data */
        grid::GridSystem*                                               mGridSystem;                    /*!< cached grid system */
        std::vector<const data::EnemyDefine*>                           mRegularEnemyTypes;             /*!< all types of regular enemies can be generated in this level */
        std::vector<const data::EnemyDefine*>                           mEliteEnemyTypes;               /*!< all types of elite enemies can be genrated in this level */
        std::vector<Enemy*>                                             mEnemies;                       /*!< all enemies generated */
        std::vector<std::vector<sf::Vector2i>>                          mEnemyPaths;                    /*!< enemy patrol paths */
        int                                                             mCurrentFightIndex;             /*!< index of current fight */

        float                                                           mTimeElapsedAfterLastSpawn;     /*!< time elpased after generating last enemy */
        float                                                           mTimeToSpawnNextEnemy;          /*!< duration between generate two enemies */
        int                                                             mTotalRegularEnemyToSpawn;      /*!< total number of regular enemies in current fight */
        int                                                             mTotalEliteEnemyToSpawn;        /*!< total number of elite enemies in current fight */
        bool                                                            mIsSpawning;                    /*!< spawner state flag */
    };
}

#endif //GAME_ENEMYSPAWNER_H
