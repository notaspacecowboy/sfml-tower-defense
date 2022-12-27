//
// Created by Zheng Yang on 29/09/22.
//

#ifndef GAME_GAMEMANAGER_H
#define GAME_GAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include "Utils/Singleton.h"
#include <chrono>
#include <vector>
#include <string>
#include <Components/GameObject.h>
#include <States/StateMachine.h>
#include <Renderer/GameRenderer.h>
#include <Utils/GuidGenerator.h>
#include <Core/ObjectHandle.h>
#include <Core/AsyncTask.h>
#include <Core/PlayerState.h>
#include <mutex>


namespace game::core {


    /** @brief manager class that initialize, runs, updates and closes the game window
     *
     *  this is the manager class that initialize, runs, updates and closes the game window. It maintains the global
     *  lookup table for all gameobjects created during the game, and it manages all the background thread created with
     *  the AsyncTask class. It maintains the main game loop and it ensures the application can be closed properly when
     *  getting terminated.
     *
     *  @author Zheng Yang
     */
    class GameManager: public utils::Singleton<GameManager> {
        friend class Singleton<GameManager>;

    public:

        /** @brief initialize some configurations of the game
         *
         *  initialize some configurations of the game and calls the initialization of other singleton managers
         *
         */
        void                                                    init();


        /** @brief run game
         *
         *  this is where the main loop of the game takes place at. The game terminates when this function terminates
         *
         */
        void                                                    run();


        /** @brief clean up before closing game window
         *
         *  this function gets called before game terminates to make sure all the resource are properly returned and all the threads
         *  are joined
         *
         */
        void                                                    terminate();


        /** @brief instantiate an empty gameobject and return a handle to this gameobject to caller
         *
         *  this function instantiate an empty gameobject, set its states, give it a guid, and return a handle to this gameobject to caller
         *
         *  @param state state of the new gameobject
         *  @return handle to the newly created gameobject
         */
        GoHandle                                                instantiateGameObject(components::GameObject::GoState state = components::GameObject::GoState::ACTIVE);


        /** @brief game renderer getter
         *
         *  game renderer getter
         *
         *  @return reference to the game renderer object
         */
        renderer::GameRenderer&                                 getRenderer();


        /** @brief get an empty gameobject handle
         *
         *  this function creates a new empty gameobject handle and return it to caller
         *
         *  @return an empty gameobject handle
         */
        GoHandle                                                getEmptyGoHandle();


        /** @brief window size getter
         *
         *  this function returns the current game window size
         *
         *  @return current game window size
         */
        sf::Vector2u                                            getCurrentWindowSize();


        /** @brief register asynchronous task
         *
         *  this function register asynchronous task, so when game terminites the asynchronous task can be joined and destroyed
         *  properly
         *
         *  @param task new asynchronous task
         */
        AsyncTask*                                              registerAsyncTask(LoadingTask task);


        /** @brief player state getter
         *
         *  this function returns the current player state object
         *
         *  @param PlayerState player state pointer
         */
        PlayerState*                                            getPlayerState();


        /** @brief frame per second getter
         *
         *  this function returns the current fps of the game
         *
         *  @return current fps of the game
         */
        int                                                     getFPS();


        /** @brief game camera getter
         *
         *  this function returns the game camera
         *
         *  @return game camera
         */
        sf::View*                                               getGameCamera();

        /** @brief game window getter
         *
         *  this function returns the game window
         *
         *  @return game window
         */
        sf::RenderWindow*                                       getGameWindow();

    private:
        /** @brief private constructor
         *
         *  private constructor to ensure the singleton pattern
         *
         */
                                                                GameManager();


        /** @brief GameManager destructor
         *
         *  GameManager destructor
         *
         */
                                                                ~GameManager();


        /** @brief update the fps of the game by passing in the time elapsed between last frame and current frame
         *
         *  this function update the fps of the game by passing in the time elapsed between last frame and current frame
         *
         *  @param deltaTime time elapsed between last frame and current frame
         *
         */
        void                                                    updateFPS(float deltaTime);


        /** @brief update the game world
         *
         *  this function gets called every logical frame to update the game world. Every active entities in the game that needs to
         *  be updated every frame will be updated here
         *
         *  @param deltaTime time elapsed between last frame and current frame
         *
         */
        void                                                    tickLogic(float deltaTime);


        /** @brief render the game world
         *
         *  this function gets called every actual frame to render all the active drawable component to the game screen
         *
         *
         */
        void                                                    tickRenderer();


        /** @brief destroy a gameobject that is marked to be destroyed
         *
         *  this function gets called at the end of each logical tick to destroy all the gameobjects that are marked to be
         *  destroyed at that frame
         *
         *  @param toDestroy the gameobject marked to be destroyed
         */
        void                                                    DestroyGameObject(game::components::GameObject* toDestroy);


        /** @brief destroy a gameobject that is marked to be destroyed
         *
         *  this function gets called at the end of each logical tick to destroy all the gameobjects that are marked to be
         *  destroyed at that frame
         *
         *  @param toDestroy the guid of the gameobject marked to be destroyed
         */
        void                                                    DestroyGameObject(GUID guid);


    public:
        static const float                                      DefaultTimePerFrame;                /*!< maximum fps allowed */
        static const int                                        GoMaximum;                          /*!< maximum number of gameobjects allowed */

    private:
        bool                                                    mIsGameRunning;                     /*!< true if game is runnning, false otherwise */
        bool                                                    mIsTickingLogic;                    /*!< true if tickLogic() is running */
        float                                                   mTimePerFrame;                      /*!< current fps of game */
        sf::RenderWindow                                        mGameWindow;                        /*!< game window */
        std::chrono::steady_clock::time_point                   mTimePointForLastTick;              /*!< the point of time when the last logical tick happens */

        int                                                     mFPS;                               /*!< frame count */
        int                                                     mFrameCount;                        /*!< frame count */
        float                                                   mTimeElapsedAfterLastSecond;        /*!< time elapsed from last second to now */
        float                                                   mActualTimeElapsedBetweenRender;    /*!< time elapsed from last game render to now */

        std::unique_ptr<PlayerState>                            mPlayerState;                       /*!< current player state */

        //gameobjects
        std::vector<GoWrapper>                                  mActiveGoQueue;                     /*!< queue of all active gameobjects */
        std::vector<GUID>                                       mPendingGoQueue;                    /*!< queue of all gameobjects that just got created this frame */
        std::vector<GUID>                                       mToDeleteGoQueue;                   /*!< queue of all gameobject that are marked to be destroyed */

        //threads
        std::vector<std::unique_ptr<AsyncTask>>                 mActiveTasks;                       /*!< active asynchronous tasks */
        std::mutex                                              mLock;                              /*!< mutual lock */

        //state machine
        states::StateMachine                                    mStateMachine;                      /*!< game state machine */

        //game renderer
        renderer::GameRenderer                                  mRenderer;                          /*!< game renderer */

        //TODO eventually cameras should be moved to renderer class
        sf::View                                                mGameCamera;                        /*!< game world camera */
        sf::View                                                mUiCamera;                          /*!< GUI camera */
    };

}

#endif //GAME_GAMEMANAGER_H
