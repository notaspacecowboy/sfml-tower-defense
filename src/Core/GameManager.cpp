//
// Created by Zheng Yang on 29/09/22.
//

#include <Core/GameManager.h>
#include "Input/InputManager.h"
#include "Data/DataManager.h"
#include "Resource/ResourceManager.h"
#include <Resource/Localization.h>
#include <Utils/Logger.h>
#include <boost/bind/bind.hpp>
#include <Audio.h>
#include <States.h>

namespace game::core {
    using namespace data;
    using namespace input;
    using namespace resource;
    using namespace audio;
    using namespace boost::placeholders;

    //default to 60 FPS
    const float GameManager::DefaultTimePerFrame = 1.f / 60.f;
    const int GameManager::GoMaximum = 600;

    GameManager::GameManager()
    : mGameWindow(sf::VideoMode(1280, 720), "Sea Defense")
    , mGameCamera(mGameWindow.getDefaultView())
    , mUiCamera(mGameWindow.getDefaultView())
    , mIsTickingLogic(false)
    , mTimePerFrame(DefaultTimePerFrame)   //set it to default for now, may read from save files in the future
    , mTimePointForLastTick(std::chrono::steady_clock::now())
    , mRenderer(mGameWindow, mUiCamera, mGameCamera)
    , mActiveGoQueue(GoMaximum)
    , mPendingGoQueue()
    , mToDeleteGoQueue()
    , mStateMachine()
    , mPlayerState(new PlayerState())
    , mFPS(0)
    , mFrameCount(0)
    , mTimeElapsedAfterLastSecond(0)
    , mActualTimeElapsedBetweenRender(0)
    , mIsGameRunning(false)
    {
    }

    GameManager::~GameManager() {
        for(auto &iter: mActiveGoQueue) {
            iter.reset();
        }
    }

    void GameManager::init() {
        utils::Logger::setLogLevel(2);

        utils::Logger::log("GameManager->init");
        //test state machine

        //TODO eventually we should create a loading state and move all the following tasks there
        InputManager::getInstance().init(&mGameWindow, &mUiCamera, &mGameCamera);
        InputManager::getInstance().GameWindowCloseEvent.connect(boost::bind(&GameManager::terminate, this));

        mRenderer.init();
        DataManager::getInstance().init();
        TextureManager::getInstance().init();
        FontManager ::getInstance().init();
        SoundBufferManager::getInstance().init();
        MusicManager::getInstance().init();
        SoundManager::getInstance().init();

        auto state = mStateMachine.push<states::StartState>();
    }

    void GameManager::terminate() {
        if(!mIsGameRunning)
            return;

        utils::Logger::log("Game Terminated", 5);

        mIsGameRunning = false;
        //finish all unfinished tasks first
        for(auto &iter: mActiveTasks) {
            iter->join();
        }

        while(!mStateMachine.isEmpty()) {
            mStateMachine.pop();
        }

        DataManager::getInstance().savePlayerAtIndex(DataManager::getInstance().getCurrentPlayerIndex());
        mGameWindow.close();
    }

    void GameManager::run() {
        utils::Logger::log("GameManager->run");
        float deltaTime;
        bool logicTickHappenedThisFrame = false;

        mIsGameRunning = true;
        while (mGameWindow.isOpen())
        {
            //calculate delta time
            {
                using namespace std::chrono;
                steady_clock::time_point mTimePointForThisTick = steady_clock::now();
                std::chrono::duration<float> duration = duration_cast<std::chrono::duration<float> >(mTimePointForThisTick - mTimePointForLastTick);
                mActualTimeElapsedBetweenRender += duration.count();
                deltaTime += duration.count();
                mTimePointForLastTick = mTimePointForThisTick;
            }

            while(deltaTime > mTimePerFrame) {
                logicTickHappenedThisFrame = true;
                utils::Time::setDeltaTime(mTimePerFrame);
                InputManager::getInstance().tick();
                tickLogic(mTimePerFrame);           //stick with fixed update
                deltaTime -= mTimePerFrame;

                //shutdown game if all states have been poped out
                if (mStateMachine.isEmpty()) {
                    utils::Logger::log("no more active states, closing window...");
                    terminate();
                }
            }

            //rendering only happens when game logic ticked
            if(logicTickHappenedThisFrame) {
                logicTickHappenedThisFrame = false;
                tickRenderer();
                updateFPS(mActualTimeElapsedBetweenRender);
                mActualTimeElapsedBetweenRender = 0;
            }
        }
    }

    void GameManager::tickLogic(float deltaTime) {
        //tick async tasks
        for(auto &thread: mActiveTasks)
            thread->tick();

        if(!mStateMachine.isEmpty() && mStateMachine.peak()->freezeTime())
            deltaTime = 0;

        //update all active gameobjects
        mIsTickingLogic = true;
        for(int i = 0; i < GoMaximum; i++) {
            auto &info = mActiveGoQueue[i];
            if(info.objectPtr != nullptr && !info.allocatedThisFrame) {
                info.objectPtr->tick(deltaTime);

                if(info.objectPtr->getState() == components::GameObject::GoState::MARK_TO_DESTROY)
                    mToDeleteGoQueue.emplace_back(info.guid);
            }
        }
        mIsTickingLogic = false;

        //putting all pending gameobjects to active queue
        //new gameobject starts tick in nect frame
        for(auto iter: mPendingGoQueue) {
            auto &info = mActiveGoQueue[iter % GoMaximum];
            info.allocatedThisFrame = false;
        }
        mPendingGoQueue.clear();

        //destory all gameobjects marked to be deleted
        for(auto iter: mToDeleteGoQueue) {
            DestroyGameObject(iter);
        }
        mToDeleteGoQueue.clear();
    }

    void GameManager::tickRenderer() {
        if(!mGameWindow.isOpen())
            return;

        //clear buffer
        mGameWindow.clear(sf::Color::Black);

        //draw all GOs
        mRenderer.draw();

        //present buffer
        mGameWindow.display();
    }

    void GameManager::updateFPS(float deltaTime) {
        mFrameCount++;
        mTimeElapsedAfterLastSecond += deltaTime;

        if(mTimeElapsedAfterLastSecond >= 1.0f) {
            mFPS = mFrameCount;
            mFrameCount = 0;
            mTimeElapsedAfterLastSecond -= 1.f;
        }
    }

    int GameManager::getFPS() {
        return mFPS;
    }

    sf::View *GameManager::getGameCamera() {
        return &mGameCamera;
    }

    sf::RenderWindow *GameManager::getGameWindow() {
        return &mGameWindow;
    }

    GoHandle GameManager::instantiateGameObject(components::GameObject::GoState state ) {
        using namespace game::components;

        GUID id = utils::GuidGenerator::generate();
        GameObject *go = new GameObject(id, state);
        GoWrapper info(id, go);

        if(mIsTickingLogic) {
            info.allocatedThisFrame = true;
            mPendingGoQueue.emplace_back(id);
        }

        int index = info.guid % GoMaximum;

        //this is not necessarily a bad thing because we want to reuse the slots,
        //but we need to make sure the gameobject pointed by this index has already been cleaned, otherwise we will
        //need to increase the size of the active gameobject queue
        //the current size of mActiveGoQueue is 200, which is the maximum amount of gameobject that
        //the game is allowed to hold at any given time
        //assert(mActiveGoQueue[index].objectPtr == nullptr);

        mActiveGoQueue[index] = std::move(info);

         return GoHandle(&mActiveGoQueue, id);
    }



    void GameManager::DestroyGameObject(GUID guid) {
        auto &info = mActiveGoQueue[guid % GoMaximum];
        info.reset();
    }

    renderer::GameRenderer& GameManager::getRenderer() {
        return mRenderer;
    }

    GoHandle GameManager::getEmptyGoHandle() {
        return GoHandle(&mActiveGoQueue, INT32_MAX);
    }

    sf::Vector2u GameManager::getCurrentWindowSize() {
        return mGameWindow.getSize();
    }


    //threads
    AsyncTask* GameManager::registerAsyncTask(game::core::LoadingTask task) {
        mLock.lock();
        auto t = std::unique_ptr<AsyncTask>(new AsyncTask(task));
        auto obj = t.get();
        mActiveTasks.emplace_back(std::move(t));
        mLock.unlock();
        return obj;
    }

    PlayerState *GameManager::getPlayerState() {
        return mPlayerState.get();
    }
}