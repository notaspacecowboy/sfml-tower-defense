//
// Created by Zheng Yang on 04/11/22.
//

#ifndef GAME_SOUNDMANAGER_H
#define GAME_SOUNDMANAGER_H

#include <Utils/Singleton.h>
#include <list>
#include <SFML/Audio.hpp>


namespace game::audio {
    /** @brief manager singleton class for in-game sound fx player
    *
    *  this class is a singleton manager class, and it is used to control and play all the in-game short sound fx
    *
    * @author Zheng Yang
    */
    class SoundManager: public utils::Singleton<SoundManager> {
        friend class Singleton<SoundManager>;
    public:

        /** @brief sound initialization and configuration
        *
        *  this function should be called before any other APIs, it initializes the sound settings
        *
        */
        void                                                init();

        /** @brief called every frame to clean completed sound instances
        *
        *  this function is called by game manager every frame to clean out all the completed sound instances
        *
        */
        void                                                tick();

        /** @brief play sound fx based on its unique identifier
        *
        *  this function takes a sound id, and plays the corresponding audio effect
        *
        *  @param soundId unique id of the sound to be played
        */
        void                                                play(int soundId);

        /** @brief called by tick every frame to clean completed sound instances
        *
        *  this function does the actual cleaning of the completed sound effect instance
        *
        */
        void                                                clean();

    private:
        /** @brief private constructor to ensure the singleton pattern
        *
        *  the constructor is private because it is a singleton class
        *
        */
                                                            SoundManager();

        std::list<sf::Sound>                                mSounds;    /*!< all the active sound effects that are currently being played */
    };
}

#endif //GAME_SOUNDMANAGER_H
