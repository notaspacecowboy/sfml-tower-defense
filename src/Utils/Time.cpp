//
// Created by Zheng Yang on 06/11/22.
//

#include <Utils/Time.h>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>

namespace game::utils {
    float Time::deltaTime = 0.f;

    std::string Time::getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
        return ss.str();
    }

    float Time::getDeltaTime() {
        return deltaTime;
    }

    void Time::setDeltaTime(float time) {
        deltaTime = time;
    }


}