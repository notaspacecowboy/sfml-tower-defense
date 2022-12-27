//
// Created by Zheng Yang on 18/11/22.
//

#ifndef GAME_ENEMYDEFINE_H
#define GAME_ENEMYDEFINE_H

#include <Data/JsonBase.h>
#include <vector>
#include <memory>

namespace game::data {
    /** @brief data structure to hold enemy animation data
     *
     *  this is the data structure to hold animation data defined in EnemyDefine.json
     *
     *  @author Zheng Yang
     */
    struct EnemyAnimDefine: public JsonBase {


        /** @brief EnemyAnimDefine constructor
         *
         *  EnemyAnimDefine constructor which deserializes a json object
         *
         * @param json object of the enemy animation data
         */
        explicit                            EnemyAnimDefine(const rapidjson::Value& json) { fromJson(json); }
                                            EnemyAnimDefine(const EnemyAnimDefine& other) = delete;
        EnemyAnimDefine&                    operator=(const EnemyAnimDefine& other) = delete;

        int                                 animStateID;        /*!< animation state identifier */
        int                                 animID;             /*!< animation identifier */
        bool                                makeInitialState;   /*!< make this the initial animation  */



        void fromJson(const rapidjson::Value& json) override {
            animStateID         = json["animStateID"].GetInt();
            animID              = json["animID"].GetInt();
            makeInitialState    = json["makeInitialState"].GetBool();
        }

        void toJson(rapidjson::Writer<rapidjson::StringBuffer> *writer) override {}
    };

    /** @brief data structure to hold enemy data
     *
     *  this is the data structure to hold enemy data defined in EnemyDefine.json
     *
     *  @author Zheng Yang
     */
    struct EnemyDefine: public JsonBase {
        /** @brief EnemyDefine constructor
         *
         *  EnemyDefine constructor which deserializes a json object
         *
         * @param json object of the enemy data
         */
        explicit                                            EnemyDefine(const rapidjson::Value& json) { fromJson(json); }
                                                            EnemyDefine(const EnemyDefine& other) = delete;
        EnemyDefine&                                        operator=(const EnemyDefine& other) = delete;

        int                                                 tID;                /*!< unique identifier */
        bool                                                isElite;            /*!< is enemy elite */
        int                                                 speed;              /*!< moving speed */
        float                                               rotateSpeed;        /*!< rotation speed */
        int                                                 hp;                 /*!< maximum hp */
        int                                                 point;              /*!< point given when killed */
        int                                                 damage;             /*!< damage it does to player */

        float                                               scaleSpriteX;       /*!< scale enemy sprite in x-axis */
        float                                               scaleSpriteY;       /*!< scale enemy sprite in y-axis */
        bool                                                isFacingRight;      /*!< is enemy sprite originally facing right */
        std::vector<std::unique_ptr<EnemyAnimDefine>>       animations;         /*!< enemy animation define */


        void fromJson(const rapidjson::Value& json) override {
            tID             = json["tid"].GetInt();
            isElite         = json["isElite"].GetBool();
            speed           = json["speed"].GetInt();
            rotateSpeed     = json["rotateSpeed"].GetFloat();
            hp              = json["hp"].GetInt();
            point           = json["point"].GetInt();
            damage          = json["damage"].GetInt();
            scaleSpriteX    = json["scaleSpriteX"].GetFloat();
            scaleSpriteY    = json["scaleSpriteY"].GetFloat();
            isFacingRight   = json["isFacingRight"].GetBool();

            animations.clear();
            const rapidjson::Value &array = json["animations"];
            for(size_t i = 0; i < array.Size(); i++) {
                const rapidjson::Value& animationJson = array[i];

                animations.emplace_back(new EnemyAnimDefine(animationJson));
            }
        }

        void toJson(rapidjson::Writer<rapidjson::StringBuffer> *writer) override {}
    };
}

#endif //GAME_ENEMYDEFINE_H
