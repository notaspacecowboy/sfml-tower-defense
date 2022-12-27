//
// Created by Zheng Yang on 04/11/22.
//

#ifndef GAME_MUSICMANAGER_H
#define GAME_MUSICMANAGER_H

#include <Utils/Singleton.h>
#include <SFML/Audio.hpp>

namespace game::audio {

    /** @brief a enum class for all the available music in the game
     *
     *  This class is a enum class that provide unique identifier for every available music in the game
     *
     *  @author Zheng Yang
     */
    enum class MusicType: int {
        MUSIC_START             = 1,            /*!< music to be played in the start scene  */
        MUSIC_MAIN              = 2,            /*!< music to be played in the main scene   */
        MUSIC_BATTLE            = 3,            /*!< music to be played in the battle scene */

    };


    /** @brief manager singleton class for in-game background music
    *
    *  this class is a singleton manager class, and it is used to control all the in-game music resources.
    *
    */
    class MusicManager: public utils::Singleton<MusicManager> {
        friend class Singleton<MusicManager>;
    public:
        /** @brief music initialization and configuration
        *
        *  this function should be called before any other APIs, it initializes the music settings
        *
        */
        void                                            init();

        /** @brief play BGM based on its unique identifier
        *
        *  this function takes a music id, and plays the corresponding music
        *
        *  @param musicType id of the music to be played
        */
        void                                            play(MusicType musicType);

        /** @brief stop BGM
        *
        *  this function stops the background music, if there is any
        *
        */
        void                                            stop();

        /** @brief music volumn setter
        *
        *  this is the setter function of music volumn
        *
        *  @param volumn new music volumn, which should be a number between 0 and 100
        */
        void                                            setVolumn(float volumn);

        /** @brief pause/continue the current music
        *
        *  this function pauses or continues the current music based on a boolean flag
        *
        *  @param isPaused true if you want to pause the music, otherwise false
        */
        void                                            setPause(bool isPaused);

        /** @brief register a id to resource path pair for a in-game background music
        *
        *  this function register a id to resource path pair for a in-game background music
        *
        *  @param type the unique identifier of a music file
        *  @param path the resource path of a music file
        */
        void                                            registerMusic(MusicType type, std::string path);

    private:
        /** @brief private constructor to ensure the singleton pattern
        *
        *  the constructor is private because it is a singleton class
        *
        */
                                                        MusicManager();

        std::unordered_map<MusicType, std::string>      mTypeToPathMapping;     /*!< registered music type to path mapping */
        sf::Music                                       mMusic;                 /*!< actual music player provided by SFML */
        float                                           mVolumn;                /*!< global state of current music volumn */
    };
}


#endif //GAME_MUSICMANAGER_H
