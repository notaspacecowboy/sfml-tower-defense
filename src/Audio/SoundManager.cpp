//
// Created by Zheng Yang on 04/11/22.
//

#include <Audio.h>
#include <Resource/ResourceManager.h>

using namespace game::resource;

namespace game::audio {
    SoundManager::SoundManager() {}

    void SoundManager::init() {}

    void SoundManager::play(int soundId) {
        auto soundBuffer = SoundBufferManager::getInstance().getByID(soundId);
        mSounds.emplace_back(sf::Sound(*soundBuffer));

        auto &sound = mSounds.back();
        sound.play();
    }

    void SoundManager::tick() {
        clean();
    }

    void SoundManager::clean() {
        mSounds.remove_if([](sf::Sound &s) -> bool {
            return s.getStatus() == sf::SoundSource::Stopped;
        });
    }

}
