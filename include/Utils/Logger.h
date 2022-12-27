//
// Created by Zheng Yang on 20/10/22.
//

#ifndef GAME_LOGGER_H
#define GAME_LOGGER_H

#include <string>
#include <SFML/Graphics.hpp>

namespace game::utils {

    /** @brief a simple logger class
     *
     *  This class contains only static method that logs different type of data structures to console
     *
     *  @author Zheng Yang
     */
    class Logger {

    public:
        /** @brief print string to console
         *
         *  this function takes the log message and the log level and print the log to console if log level meets the
         *  requirement
         *
         *  @param logMessage the log message to be printed
         *  @param logLevel the level of this log message
         */
        static void                     log(const std::string logMessage, int logLevel = 1);

        /** @brief print Vector2i to console
         *
         *  this function takes a vector and the log level and print the vector to console if log level meets the
         *  requirement
         *
         *  @param vector the vector to be printed
         *  @param logLevel the level of this log message
         */
        static void                     log(const sf::Vector2i vector, int logLevel = 1);

        /** @brief print Vector2f to console
         *
         *  this function takes a vector and the log level and print the vector to console if log level meets the
         *  requirement
         *
         *  @param vector the vector to be printed
         *  @param logLevel the level of this log message
         */
        static void                     log(const sf::Vector2f vector, int logLevel = 1);

        /** @brief print FloatRect to console
         *
         *  this function takes a FloatRect and the log level and print the FloatRect to console if log level meets the
         *  requirement
         *
         *  @param rect the rect to be printed
         *  @param logLevel the level of this log message
         */
        static void                     log(const sf::FloatRect rect, int logLevel = 1);

        /** @brief print integer to console
         *
         *  this function takes a integer and the log level and print the integer to console if log level meets the
         *  requirement
         *
         *  @param value the integer to be printed
         *  @param logLevel the level of this log message
         */
        static void                     log(int value, int logLevel = 1);

        /** @brief print float to console
         *
         *  this function takes a float and the log level and print the float to console if log level meets the
         *  requirement
         *
         *  @param value the float to be printed
         *  @param logLevel the level of this log message
         */
        static void                     log(float value, int logLevel = 1);

        /** @brief set the current log level
         *
         *  this function set the current log level of the program to restrict the number of logs to be printed in the console
         *
         *  @param newLogLevel the new log level
         */
        static void                     setLogLevel(int newLogLevel);

    private:
        /** @brief the current log level
         *
         *  member functions of the log class select which message to print to the console based on this value
         */
        static int                      LogLevel;
    };
}

#endif //GAME_LOGGER_H
