//
// Created by Zheng Yang on 20/10/22.
//

#include <Utils/Logger.h>
#include <iostream>
#include <SFML/Graphics.hpp>


namespace game::utils {
    int Logger::LogLevel = 1;

    void Logger::log(const std::string logMessage, int logLevel) {
        if(logLevel < Logger::LogLevel)
            return;
        std::cout << logMessage << std::endl;
    }

    void Logger::log(const sf::Vector2i vector, int logLevel) {
        if(logLevel < Logger::LogLevel)
            return;
        std::cout << "(" << vector.x << ", " << vector.y << ")" << std::endl;
    }

    void Logger::log(const sf::Vector2f vector, int logLevel) {
        if(logLevel < Logger::LogLevel)
            return;
        std::cout << "(" << vector.x << ", " << vector.y << ")" << std::endl;
    }

    void Logger::log(const sf::FloatRect rect, int logLevel) {
        if(logLevel < Logger::LogLevel)
            return;
        std::cout << "(" << rect.left << ", " << rect.top << ", " << rect.width << ", " << rect.height << ")" << std::endl;
    }

    void Logger::log(int value, int logLevel) {
        if(logLevel < Logger::LogLevel)
            return;
        std::cout << std::to_string(value) << std::endl;
    }

    void Logger::log(float value, int logLevel) {
        if(logLevel < Logger::LogLevel)
            return;
        std::cout << std::to_string(value) << std::endl;
    }

    void Logger::setLogLevel(int newLogLevel) {
        LogLevel = newLogLevel;
    }
}
