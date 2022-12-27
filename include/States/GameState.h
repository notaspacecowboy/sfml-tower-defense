//
// Created by Zheng Yang on 13/11/22.
//

#ifndef GAME_GAMESTATE_H
#define GAME_GAMESTATE_H

#include <States/State.h>
#include <Grid/GridSystem.h>
#include <boost/signals2.hpp>

namespace game::components {
    class Sprite;
    class Enemy;
    class Button;
    class SimpleButton;
}

namespace game::states {

    /** @brief game state
     *
     *  this state will be pushed to state machine when player start the game - this is the main game state that will always
     *  be in the state machine during gameplay
     *
     *  @author Zheng Yang
     */
    class GameState: public State {
    public:

        /** @brief GameState constructor
         *
         * GameState constructor
         *
         */
        explicit                                GameState(StateMachine* owner);


        /** @brief GameState destructor
         *
         * GameState destructor
         *
         */
                                                ~GameState();


        /** @brief initialization of state
         *
         * initialization of state, called by state machine after state is created and put to the stack
         *
         */
        void                                    init() override;


        /** @brief load game world
         *
         * load game world - this include initialize grid system, initialize enemy spawner and create player hud menu
         *
         */
        void                                    loadGameWord();


        /** @brief callback for map load complete event
         *
         * callback function for  map load complete event
         *
         */
        void                                    onMapLoadCompleted();


        /** @brief disable user input in the current state
         *
         * call this function to disable user input in the current state
         *
         */
        void                                    disableInput() override;


        /** @brief enable user input in the current state
         *
         * call this function to enable user input in the current state
         *
         */
        void                                    enableInput() override;


        /** @brief callback for game lose event
         *
         * callback function for game lose event
         *
         */
        void                                    loseGame();


        /** @brief callback for game win event
         *
         * callback function for game win event
         *
         */
        void                                    winGame();


        /** @brief adjust game camera based on player position in the game world
         *
         * adjust game camera based on player position in the game world
         *
         */
        void                                    adjustGameCamera();
        void                                    onWheelScrolled(int delta);


        /** @brief callback for mouse dragging event
         *
         * callback function for mouse dragging event
         *
         */
        void                                    onMouseDrag(int deltaX, int deltaY);


        /** @brief callback for spawn button click event
         *
         * callback function for spawn button click event
         *
         */
        void                                    onSpawnButtonClicked();


        /** @brief callback for pause button click event
         *
         * callback function for gpause button click event
         *
         */
        void                                    onPauseButtonClicked();

        //game logic callbacks


        /** @brief callback for pause button click event
         *
         * callback function for pause button click event
         *
         */
        void                                    onEnemySpawned(components::Enemy* enemy);


        /** @brief callback for all enemy spawned event
         *
         * callback function for all enemy spawned event
         *
         */
        void                                    onAllEnemiesSpawned();


        /** @brief callback for enemy spawned event
         *
         * callback function for enemy spawned event
         *
         * @param enemy enemy
         */
        void                                    onEnemyDead(const data::EnemyDefine* enemy);


        /** @brief callback for enemy arriving destination event
         *
         * callback function for enemy arriving destination event
         *
         * @param enemy enemy
         */
        void                                    onEnemyArriveDestination(const data::EnemyDefine* enemy);

    private:
        core::GoHandle                          mGameRoot;                      /*!< root gameobject handle */
        const ldtk::World&                      mGameWorld;                     /*!< game world adta */
        static float                            scrollSpeed;                    /*!< mouse scroll speed */
        static float                            cameraMoveSpeed;                /*!< camera move speed */

        sf::View*                               mGameCamera;                    /*!< cached game camera */
        std::unique_ptr<grid::GridSystem>       mGridSystem;                    /*!< grid system */
        components::EnemySpawner*               mEnemySpawner;                  /*!< enemy spawner */
        components::PlayerHud*                  mPlayerHud;                     /*!< player hud */
        components::Button*                     mEnemySpawnButton;              /*!< enemy spawn button */
        components::SimpleButton*               mPauseButton;                   /*!< pause button */
        boost::signals2::connection             mLoadingTaskListener;           /*!< loading task listener */
        boost::signals2::connection             mWheelScrolledListener;         /*!< wheel button listener */
        boost::signals2::connection             mKeyPressedListener;            /*!< keyboard pressed listener */
        boost::signals2::connection             mMouseDragListener;             /*!< mouse dragging event listener */
        boost::signals2::connection             mPauseButtonClickListener;      /*!< pause button click listener */
        boost::signals2::connection             mSpawnButtonClickListener;      /*!< spawn button click listener */

        int                                     mEnemyCount;                    /*!< total number of active enemies in the scene */

        components::TowerShop*                  mTowerShop;                     /*!< cached tower shop component */
    };
}
#endif //GAME_GAMESTATE_H
