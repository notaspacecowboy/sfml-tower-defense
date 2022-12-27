//
// Created by Zheng Yang on 20/11/22.
//

#ifndef GAME_ENEMYSPAWNRULEDEFINE_H
#define GAME_ENEMYSPAWNRULEDEFINE_H

#include <Data/JsonBase.h>
#include <vector>
#include <memory>

namespace game::data {

    /** @brief data structure to hold fight rule data
     *
     *  this is the data structure to hold fight rule data defined in SpawnRuleDefine.json
     *
     *  @author Zheng Yang
     */
    struct FightRuleDefine: public JsonBase {

        /** @brief FightRuleDefine constructor
         *
         *  FightRuleDefine constructor which deserializes a json object
         *
         * @param json object of the fight rule data
         */
        explicit                            FightRuleDefine(const rapidjson::Value& json) { fromJson(json); }
                                            FightRuleDefine(const FightRuleDefine& other) = delete;
        FightRuleDefine&                    operator=(const FightRuleDefine& other) = delete;

        int                                 totalEnemies;       /*!< identifier */
        float                               regularEnemies;     /*!< portion of regular enemies */
        float                               eliteEnemies;       /*!< portion of elite enemies */
        float                               minimumWaitTime;    /*!< min waiting time */
        float                               maximumWaitTime;    /*!< max waiting time */


        void fromJson(const rapidjson::Value& json) override {
            totalEnemies                = json["totalEnemies"].GetInt();
            regularEnemies              = json["regularEnemies"].GetFloat();
            eliteEnemies                = json["eliteEnemies"].GetFloat();
            minimumWaitTime             = json["minimumWaitTime"].GetFloat();
            maximumWaitTime             = json["maximumWaitTime"].GetFloat();
        }

        void toJson(rapidjson::Writer<rapidjson::StringBuffer> *writer) override {}
    };


    /** @brief data structure to hold spawn rule data
     *
     *  this is the data structure to hold spawn rule data defined in SpawnRuleDefine.json
     *
     *  @author Zheng Yang
     */
    struct EnemySpawnRuleDefine: public JsonBase {

        /** @brief EnemySpawnRuleDefine constructor
         *
         *  EnemySpawnRuleDefine constructor which deserializes a json object
         *
         * @param json object of the spawn rule data
         */
        explicit                                            EnemySpawnRuleDefine(const rapidjson::Value& json) { fromJson(json); }
                                                            EnemySpawnRuleDefine(const EnemySpawnRuleDefine& other) = delete;
        EnemySpawnRuleDefine&                               operator=(const EnemySpawnRuleDefine& other) = delete;

        int                                                 tID;                /*!< identifier */
        int                                                 totalFights;        /*!< total fights in this game level */

        std::vector<int>                                    enemyList;          /*!< enemy list */
        std::vector<std::unique_ptr<FightRuleDefine>>       fights;             /*!< fights */


        void fromJson(const rapidjson::Value& json) override {
            tID             = json["tid"].GetInt();
            totalFights     = json["totalFights"].GetInt();

            enemyList.clear();
            const rapidjson::Value &enemyListArray = json["enemyList"];
            for(size_t i = 0; i < enemyListArray.Size(); i++) {
                enemyList.emplace_back(enemyListArray[i].GetInt());
            }

            fights.clear();
            const rapidjson::Value &array = json["fights"];
            for(size_t i = 0; i < array.Size(); i++) {
                const rapidjson::Value& fightJson = array[i];

                fights.emplace_back(new FightRuleDefine(fightJson));
            }
        }

        void toJson(rapidjson::Writer<rapidjson::StringBuffer> *writer) override {}
    };
}

#endif //GAME_ENEMYSPAWNRULEDEFINE_H
