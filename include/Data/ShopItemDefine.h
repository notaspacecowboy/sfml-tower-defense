//
// Created by Zheng Yang on 05/11/22.
//

#ifndef GAME_SHOPITEMDEFINE_H
#define GAME_SHOPITEMDEFINE_H

#include "JsonBase.h"
#include <string>
#include <rapidjson/document.h>

namespace game::data {

    /** @brief data structure to hold shop item data
     *
     *  this is the data structure to hold shop item data defined in ShopItemDefine.json
     *
     *  @author Zheng Yang
     */
    struct ShopItemDefine: public JsonBase {

        /** @brief ShopItemDefine constructor
         *
         *  ShopItemDefine constructor which deserializes a json object
         *
         * @param json object of the shop item data
         */
        explicit                            ShopItemDefine(const rapidjson::Value& json) { fromJson(json); }
                                            ShopItemDefine(const ShopItemDefine& other) = delete;
        ShopItemDefine&                     operator=(const ShopItemDefine& other) = delete;

        int                                 tID;            /*!< identifier */
        std::string                         name;           /*!< item name */
        std::string                         description;    /*!< item description */
        int                                 cost;           /*!< cost */
        int                                 iconTextureID;  /*!< item icon id */

        void fromJson(const rapidjson::Value& json) {
            tID = json["tid"].GetInt();
            name = json["name"].GetString();
            description = json["description"].GetString();
            cost = json["cost"].GetInt();
            iconTextureID = json["iconTextureID"].GetInt();
        }

        void toJson(rapidjson::Writer<rapidjson::StringBuffer> *writer) override {}
    };
}

#endif //GAME_SHOPITEMDEFINE_H
