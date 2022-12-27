//
    // Created by Zheng Yang on 29/10/22.
//

#ifndef GAME_BUTTONDEFINE_H
#define GAME_BUTTONDEFINE_H

#include <string>
#include <rapidjson/document.h>
#include "JsonBase.h"

namespace game::data {
    /** @brief data structure to hold button data
     *
     *  this is the data structure to hold button data defined in ButtonDefine.json
     *
     *  @author Zheng Yang
     */
    struct ButtonDefine: public JsonBase {

        /** @brief ButtonDefine constructor
         *
         *  ButtonDefine constructor which deserializes a json object
         *
         * @param json object of the button data
         */
                                            ButtonDefine(const rapidjson::Value& json) { fromJson(json); }
                                            ButtonDefine(const ButtonDefine& other) = delete;
        ButtonDefine&                       operator=(const ButtonDefine& other) = delete;
        int                           tID;                      /*!< unique identifier */
        int                           textureID;                /*!< referenced texture id */
        float                         scale;                    /*!< scale of button sprite */
        bool                          isSpriteSheet;            /*!< is texture in a sprite sheet */
        int                           offsetX;                  /*!< x axis offset of sprite in sheet */
        int                           offsetY;                  /*!< y axis offset of sprite in sheet */
        int                           width;                    /*!< width of texture in sheet */
        int                           height;                   /*!< height of texture in sheet */

        bool                          hasPressedSprite;         /*!< does button have unique pressed sprite */
        int                           pressed_textureID;        /*!< referenced pressed texture id */
        bool                          pressed_isSpriteSheet;    /*!< is texture in a sprite sheet */
        int                           pressed_offsetX;          /*!< x axis offset of sprite in sheet */
        int                           pressed_offsetY;          /*!< y axis offset of sprite in sheet */
        int                           pressed_width;            /*!< width of texture in sheet */
        int                           pressed_height;           /*!< height of texture in sheet */

        bool                          hasText;                  /*!< does button have text */
        int                           fontID;                   /*!< text font id */
        std::string                   text;                     /*!< default text */
        int                           textSize;                 /*!< text size */
        int                           textOffsetX;              /*!< text offset in x axis in button */
        int                           textOffsetY;              /*!< text offset in y axis in button */
        int                           pressed_textOffsetX;      /*!< text offset in x axis when pressed */
        int                           pressed_textOffsetY;      /*!< text offset in y axis when pressed  */

        int                           sfx_onclick;              /*!< sound effect of button when pressed  */

        void fromJson(const rapidjson::Value& json) {
            tID = json["tid"].GetInt();
            textureID = json["textureID"].GetInt();
            scale = json["scale"].GetFloat();
            isSpriteSheet = json["isSpriteSheet"].GetBool();
            offsetX = json["offsetX"].GetInt();
            offsetY = json["offsetY"].GetInt();
            width = json["width"].GetInt();
            height = json["height"].GetInt();
            hasPressedSprite = json["hasPressedSprite"].GetBool();
            pressed_textureID = json["pressed_textureID"].GetInt();
            pressed_isSpriteSheet = json["pressed_isSpriteSheet"].GetBool();
            pressed_offsetX = json["pressed_offsetX"].GetInt();
            pressed_offsetY = json["pressed_offsetY"].GetInt();
            pressed_width = json["pressed_width"].GetInt();
            pressed_height = json["pressed_height"].GetInt();
            hasText = json["hasText"].GetBool();
            fontID = json["fontID"].GetInt();
            textSize = json["textSize"].GetInt();
            textOffsetX = json["textOffsetX"].GetInt();
            textOffsetY = json["textOffsetY"].GetInt();
            pressed_textOffsetX = json["pressed_textOffsetX"].GetInt();
            pressed_textOffsetY = json["pressed_textOffsetY"].GetInt();
            sfx_onclick = json["sfx_onclick"].GetInt();
        }

        void toJson(rapidjson::Writer<rapidjson::StringBuffer> *writer) override {}
    };
}

#endif //GAME_BUTTONDEFINE_H
