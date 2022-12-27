//
// Created by Zheng Yang on 06/11/22.
//

#ifndef GAME_PLAYERDATA_H
#define GAME_PLAYERDATA_H

#include <vector>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <Utils/Time.h>
#include <Data/JsonBase.h>

namespace game::data {


    /** @brief data structure to hold player save data
     *
     *  this is the data structure to hold player save data that will eventually be stored in game savefile
     *
     *  @author Zheng Yang
     */


    /** @brief PlayerData constructor
     *
     *  PlayerData default constructor
     *
     */
    struct PlayerData: public JsonBase {
                                            PlayerData()
                                            : JsonBase()
                                            , gameLevel(0)
                                            , currentGold(2000)
                                            , powerUps()
                                            , unlockedTowers()
                                            , completedAchievements()
                                            , saveTime(utils::Time::getCurrentTime()) {}
        explicit                            PlayerData(const rapidjson::Value& json): JsonBase() { fromJson(json); }
                                            PlayerData(const PlayerData& other) = delete;
        PlayerData&                         operator=(const PlayerData& other) = delete;
        int                                 gameLevel;                  /*!< game level */
        int                                 currentGold;                /*!< gold */
        std::string                         saveTime;                   /*!< time when saved */
        std::vector<int>                    powerUps;                   /*!< all powerup items */
        std::vector<int>                    unlockedTowers;             /*!< all unlocked towers */
        std::vector<int>                    completedAchievements;      /*!< all completed achievements */

        void fromJson(const rapidjson::Value& json) {
            powerUps.clear();
            unlockedTowers.clear();
            completedAchievements.clear();

            gameLevel   = json["gameLevel"].GetInt();
            currentGold = json["currentGold"].GetInt();
            saveTime    = json["saveTime"].GetString();

            const rapidjson::Value &allPowerUps = json["powerUps"];
            for(size_t i = 0; i < allPowerUps.Size(); i++) {
                powerUps.push_back(allPowerUps[i]["shopItemId"].GetInt());
            }

            const rapidjson::Value &allUnlockedTowers = json["unlockedTowers"];
            for(size_t i = 0; i < allUnlockedTowers.Size(); i++) {
                unlockedTowers.push_back(allUnlockedTowers[i]["towerId"].GetInt());
            }

            const rapidjson::Value &allCompletedAchievements = json["completedAchievements"];
            for(size_t i = 0; i < allUnlockedTowers.Size(); i++) {
                completedAchievements.push_back(allCompletedAchievements[i]["achievementId"].GetInt());
            }
        }

        void toJson(rapidjson::Writer<rapidjson::StringBuffer> * writer) {
            writer->StartObject();

            writer->String("gameLevel");
            writer->Int(gameLevel);

            writer->String("currentGold");
            writer->Int(currentGold);

            writer->String("saveTime");
            writer->String(saveTime.c_str());

            writer->String("powerUps");
            writer->StartArray();
            for(auto powerUp: powerUps) {
                writer->StartObject();

                writer->String("shopItemId");
                writer->Int(powerUp);

                writer->EndObject();
            }
            writer->EndArray();

            writer->String("unlockedTowers");
            writer->StartArray();
            for(auto tower: unlockedTowers) {
                writer->StartObject();

                writer->String("towerId");
                writer->Int(tower);

                writer->EndObject();
            }
            writer->EndArray();

            writer->String("completedAchievements");
            writer->StartArray();
            for(auto achievement: completedAchievements) {
                writer->StartObject();

                writer->String("achievementId");
                writer->Int(achievement);

                writer->EndObject();
            }
            writer->EndArray();

            writer->EndObject();
        }
    };


}

#endif //GAME_PLAYERDATA_H
