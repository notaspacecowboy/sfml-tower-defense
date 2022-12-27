//
// Created by zyang464 on 05/11/22.
//

#ifndef GAME_JSONBASE_H
#define GAME_JSONBASE_H

#include <rapidjson/document.h>
#include <rapidjson/writer.h>

namespace game::data {
    class JsonBase {

        /** @brief deserialize c++ data structure from json object
         *
         *  this function takes a json object, and deserialize c++ data structure from it
         *
         *  @param json serialized json object
         */
        virtual void fromJson(const rapidjson::Value& json) = 0;


        /** @brief serialize a c++ data structure to a json object
         *
         *  this function takes a json writer, and serialize c++ data structure to it
         *
         *  @param writer json writer
         */
        virtual void toJson(rapidjson::Writer<rapidjson::StringBuffer> * writer) = 0;

    };
}

#endif //GAME_JSONBASE_H
