//
// Created by Zheng Yang on 31/10/22.
//

#include <Core/AsyncTask.h>
#include <functional>
#include <thread>
#include <Utils/Logger.h>

namespace game::core {
    std::mutex AsyncTask::Lock;

    AsyncTask::AsyncTask(LoadingTask task): mTask(task), mThread(nullptr), mIsRunning(false), mFinished(false) {
    }

    AsyncTask::~AsyncTask() {
        if(mThread != nullptr)
            delete mThread;

        mThread = nullptr;
    }

    void AsyncTask::execute() {
        assert(!mIsRunning);
        assert(mTask != nullptr);

        mIsRunning = true;
        mThread = new std::thread(std::bind(&AsyncTask::runTask, this));
    }

    void AsyncTask::runTask() {
        mTask();

        Lock.lock();
        mFinished = true;
        Lock.unlock();
    }

    void AsyncTask::join() {
        if(mThread != nullptr)
            mThread->join();
    }

    void AsyncTask::tick() {
        if(!mIsRunning)
            return;

        Lock.lock();
        if(mFinished) {
            mIsRunning = false;
            utils::Logger::log("loading task completed!");
            onTaskCompleted();
        }
        Lock.unlock();

    }
}
