//
// Created by Zheng Yang on 06/11/22.
//

#ifndef GAME_TIME_H
#define GAME_TIME_H

#include <string>

namespace game::utils {
    /** @brief a static class to deal with in-game time
     *
     *  This class is pure static and is meant to deal with time-related values in game
     *
     *  @author Zheng Yang
     */
    class Time {
    public:
        /** @brief get current local time
        *
        *  this function returns the current local time to the function caller
        *
        *  @return the current local time
        */
        static std::string                  getCurrentTime();

        /** @brief get the time elapsed from last frame to current frame
        *
        *  this function returns the time elapsed from last frame to current frame
        *
        *  @return the time elapsed from last frame to current frame
        */
        static float                        getDeltaTime();

        /** @brief set the time elapsed from last frame to current frame
        *
        *  this function set the time elapsed from last frame to current frame
        *
        *  @param time the time elapsed from last frame to current frame
        */
        static void                         setDeltaTime(float time);

    private:

        /** @brief time elapsed between frames
        *
        *  this is the cached time elapsed from last frame to this frame
        */
        static float                        deltaTime;
    };
}

#endif //GAME_TIME_H
