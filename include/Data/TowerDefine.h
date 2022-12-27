//
// Created by Zheng Yang on 25/11/22.
//

#ifndef GAME_TOWERDEFINE_JSONM_H
#define GAME_TOWERDEFINE_JSONM_H

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
    struct TowerAnimDefine: public JsonBase {


        /** @brief TowerAnimDefine constructor
         *
         *  TowerAnimDefine constructor which deserializes a json object
         *
         * @param json object of the tower animation data
         */
        explicit                            TowerAnimDefine(const rapidjson::Value& json) { fromJson(json); }
                                            TowerAnimDefine(const TowerAnimDefine& other) = delete;
        TowerAnimDefine&                    operator=(const TowerAnimDefine& other) = delete;

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

    /** @brief data structure to hold tower data
     *
     *  this is the data structure to hold tower data defined in TowerDefine.json
     *
     *  @author Zheng Yang
     */
    struct TowerDefine: public JsonBase {
        /** @brief EnemyDefine constructor
         *
         *  EnemyDefine constructor which deserializes a json object
         *
         * @param json object of the enemy data
         */
        explicit                                            TowerDefine(const rapidjson::Value& json) { fromJson(json); }
                                                            TowerDefine(const TowerDefine& other) = delete;
        TowerDefine&                                        operator=(const TowerDefine& other) = delete;

        int                                                 tID;                /*!< unique identifier */
        float                                               attackInterval;     /*!< attack interval */
        int                                                 attackRange;        /*!< attack range */
        int                                                 damage;             /*!< damage */
        int                                                 projectileID;       /*!< projectile id*/
        int                                                 cost;               /*!< cost of points */
        int                                                 textureID;          /*!< texture id */
        float                                               textureScaleX;      /*!< texture scale x */
        float                                               textureScaleY;      /*!< texture scale y */

        std::vector<std::unique_ptr<TowerAnimDefine>>       animations;         /*!< enemy animation define */


        void fromJson(const rapidjson::Value& json) override {
            tID             = json["tid"].GetInt();
            attackInterval  = json["attackInterval"].GetFloat();
            attackRange     = json["attackRange"].GetInt();
            damage          = json["damage"].GetInt();
            projectileID    = json["projectileID"].GetInt();
            cost            = json["cost"].GetInt();
            textureID       = json["textureID"].GetInt();
            textureScaleX   = json["textureScaleX"].GetFloat();
            textureScaleY   = json["textureScaleY"].GetFloat();

            animations.clear();
            const rapidjson::Value &array = json["animations"];
            for(size_t i = 0; i < array.Size(); i++) {
                const rapidjson::Value& animationJson = array[i];

                animations.emplace_back(new TowerAnimDefine(animationJson));
            }
        }

        void toJson(rapidjson::Writer<rapidjson::StringBuffer> *writer) override {}
    };
}

#endif //GAME_TOWERDEFINE_JSONM_H
