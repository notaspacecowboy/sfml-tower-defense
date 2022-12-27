//
// Created by Zheng Yang on 31/10/22.
//

#ifndef GAME_ASYNCTASK_H
#define GAME_ASYNCTASK_H

#include <SFML/System/Mutex.hpp>
#include <SFML/System/Lock.hpp>
#include <SFML/System/Clock.hpp>
#include <boost/signals2.hpp>
#include <thread>
#include <mutex>

namespace game::core {
    typedef boost::signals2::signal<void(void)>             TaskCompleteDelegate;
    typedef std::function<void(void)>                       LoadingTask;


    /** @brief asynchronous task executer and handler
     *
     *  this class takes a time-consuming loading task as a asynchronous task, runs it using a std::thread and execute a
     *  task completion event when the task is completed
     *
     *  @author Zheng Yang
     */
    class AsyncTask {
    public:


        /** @brief AsyncTask constructor
         *
         *  AsyncTask constructor
         *
         *  @param task asynchronous task
         */
                                                            AsyncTask(LoadingTask task);


        /** @brief AsyncTask destructor
         *
         *  AsyncTask destructor
         *
         */
                                                            ~AsyncTask();


        /** @brief start executing the asynchronous task
         *
         *  start executing the asynchronous task
         *
         */
        void                                                execute();


        /** @brief called every frame to check the current state of the asynchronous task
         *
         *  called every frame to check the current state of the asynchronous task, close the task if the asynchronous task
         *  has been completed
         *
         */
        void                                                tick();


        /** @brief join the async task thread to the main thread
         *
         *  join the async task thread to the main thread
         *
         */
        void                                                join();

        TaskCompleteDelegate                                onTaskCompleted;    /*!< async task complete event */

    private:
        static std::mutex                                   Lock;               /*!< mutual lock object */


        /** @brief start running the asynchronous task
         *
         *  start running the asynchronous task
         *
         */
        void                                                runTask();

        LoadingTask                                         mTask;              /*!< my async task */
        std::thread*                                        mThread;            /*!< thread that the async task is running on */
        bool                                                mIsRunning;         /*!< async task state flag */
        bool                                                mFinished;          /*!< true if async task is finished, otherwise false */
    };
}

#endif //GAME_ASYNCTASK_H
