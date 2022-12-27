//
// Created by zyang464 on 05/11/22.
//

#ifndef GAME_SHOPITEM_H
#define GAME_SHOPITEM_H

#include <Components/Component.h>
#include <Data/ShopItemDefine.h>
#include <Input/InputEventHandler.h>
#include <boost/signals2.hpp>

namespace game::components {
    class Sprite;
    class Text;
    class Shape;

    typedef boost::signals2::signal<void(const data::ShopItemDefine*)>     ShopItemSelectedDelegate;


    /** @brief controller class for shop icon in the shop state
     *
     *  this is the controller class for shop icon in the shop state
     *
     *  @author Zheng Yang
     */
    class ShopItem: public Component, public input::IPointerClick {
    public:

        /** @brief shop icon constructor
         *
         *  shop icon constructor
         *
         *  @param owner owner of the component
         *  @param data shop icon data
         *  @param icon shop icon sprite
         *  @param frame shop icon frame sprite
         *  @param text shop icon name
         */
                                                                ShopItem(GameObject &owner,
                                                                         const data::ShopItemDefine* data,
                                                                         Sprite* icon,
                                                                         Sprite* frame,
                                                                         Text *text);


        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is enabled
        *
        */
        void                                                    onEnable() override;

        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is disabled
        *
        */
        void                                                    onDisable() override;


        /** @brief callback for pointer click event
        *
        * callback for pointer click event - set shop icon to be selected or deselected
        *
        */
        void                                                    onPointerClick() override;
        ShopItemSelectedDelegate                                onItemSelected;     /*!< shop icon selected event */

    private:
        const data::ShopItemDefine*                             mData;              /*!< my data */
        Sprite*                                                 mIcon;              /*!< my icon sprite */
        Sprite*                                                 mClickable;         /*!< my clickable sprite */
        Text*                                                   mName;              /*!< my name text */
        boost::signals2::connection                             mClickListener;     /*!< my pointer click event listener */
    };
}

#endif //GAME_SHOPITEM_H
