//
// Created by ZHeng Yang on 03/11/22.
//

#ifndef GAME_ANIMDEFINE_H
#define GAME_ANIMDEFINE_H

#include <rapidjson/document.h>
#include "JsonBase.h"

namespace game::data {

    /** @brief data structure to hold character animation data
     *
     *  this is the data structure to hold animation data defined in AnimDefine.json
     *
     *  @author Zheng Yang
     */
    struct AnimDefine: public JsonBase {

        /** @brief AnimDefine constructor
         *
         *  AnimDefine constructor which deserializes a json object
         *
         * @param json object of the animation data
         */
        explicit                            AnimDefine(const rapidjson::Value& json) { fromJson(json); }
                                            AnimDefine(const AnimDefine& other) = delete;
        AnimDefine&                         operator=(const AnimDefine& other) = delete;

        int                           tID;              /*!< unique identifier */
        int                           textureID;        /*!< referenced texture id */
        int                           column;           /*!< total columns in the texture sheet */
        int                           row;              /*!< total rows in the texture sheet */
        int                           speed;            /*!< animation speed */
        bool                          reverse;          /*!< is sheet reversed */
        bool                          isLooping;        /*!< is animation repeating */

        void fromJson(const rapidjson::Value& json) override {
            tID = json["tid"].GetInt();
            textureID = json["textureID"].GetInt();
            column = json["column"].GetInt();
            row = json["row"].GetInt();
            speed = json["speed"].GetInt();
            reverse = json["reverse"].GetBool();
            isLooping = json["isLooping"].GetBool();
        }

        void toJson(rapidjson::Writer<rapidjson::StringBuffer> *writer) override {}
    };
}

#endif //GAME_ANIMDEFINE_H
