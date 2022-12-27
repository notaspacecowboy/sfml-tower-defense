//
// Created by Zheng Yang on 04/11/22.
//

#include <Audio.h>
#include <Data.h>


using namespace game::data;

namespace game::audio {
    MusicManager::MusicManager()
    : mMusic()
    , mVolumn(0) {}

    void MusicManager::init() {
        mMusic.setVolume(mVolumn);
        mMusic.setLoop(true);
    }

    void MusicManager::play(MusicType musicType) {
        auto idPathExist = mTypeToPathMapping.find(musicType);
        assert(idPathExist != mTypeToPathMapping.end());

        mMusic.openFromFile(idPathExist->second);
        mMusic.play();
    }

    void MusicManager::stop() {
        mMusic.stop();
    }

    void MusicManager::setPause(bool isPaused) {
        if(isPaused)
            mMusic.pause();
        else
            mMusic.play();
    }

    void MusicManager::setVolumn(float volumn) {
        mMusic.setVolume(volumn);
    }

    void MusicManager::registerMusic(game::audio::MusicType type, std::string path) {
        auto idPathExist = mTypeToPathMapping.find(type);
        if(idPathExist != mTypeToPathMapping.end())
            return;
        mTypeToPathMapping.insert(std::make_pair(type, path));
    }
}
