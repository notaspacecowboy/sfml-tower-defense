//
// Created by Zheng Yang on 25/11/22.
//

#ifndef GAME_PROJECTIONDEFINE_H
#define GAME_PROJECTIONDEFINE_H

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
    struct ProjectionAnimDefine: public JsonBase {


        /** @brief ProjectionAnimDefine constructor
         *
         *  ProjectionAnimDefine constructor which deserializes a json object
         *
         * @param json object of the projection animation data
         */
        explicit                            ProjectionAnimDefine(const rapidjson::Value& json) { fromJson(json); }
                                            ProjectionAnimDefine(const ProjectionAnimDefine& other) = delete;
        ProjectionAnimDefine&               operator=(const ProjectionAnimDefine& other) = delete;

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

    /** @brief data structure to hold projection data
     *
     *  this is the data structure to hold projection data defined in ProjectionDefine.json
     *
     *  @author Zheng Yang
     */
    struct ProjectionDefine: public JsonBase {
        /** @brief EnemyDefine constructor
         *
         *  EnemyDefine constructor which deserializes a json object
         *
         * @param json object of the enemy data
         */
        explicit                                            ProjectionDefine(const rapidjson::Value& json) { fromJson(json); }
                                                            ProjectionDefine(const ProjectionDefine& other) = delete;
        ProjectionDefine&                                   operator=(const ProjectionDefine& other) = delete;

        int                                                 tID;                /*!< unique identifier */
        int                                                 speed;              /*!< projection move speed */

        std::vector<std::unique_ptr<ProjectionAnimDefine>>  animations;         /*!< enemy animation define */


        void fromJson(const rapidjson::Value& json) override {
            tID             = json["tid"].GetInt();
            speed           = json["speed"].GetInt();

            animations.clear();
            const rapidjson::Value &array = json["animations"];
            for(size_t i = 0; i < array.Size(); i++) {
                const rapidjson::Value& animationJson = array[i];

                animations.emplace_back(new ProjectionAnimDefine(animationJson));
            }
        }

        void toJson(rapidjson::Writer<rapidjson::StringBuffer> *writer) override {}
    };
}

#endif //GAME_PROJECTIONDEFINE_H
