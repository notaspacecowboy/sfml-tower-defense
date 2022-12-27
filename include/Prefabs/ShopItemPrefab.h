//
// Created by Zheng Yang on 05/11/22.
//

#ifndef GAME_SHOPITEMPREFAB_H
#define GAME_SHOPITEMPREFAB_H

#include "PrefabFactory.h"
#include <Core/ObjectHandle.h>

namespace game::components {
    class Sprite;
    class Text;
}

namespace game::prefabs {


    /** @brief predefined game shop item UI
     *
     *  this class is the predefined game shop item UI that can be reused in different game states
     *
     *  @author Zheng Yang
     */
    class ShopItemPrefab: public IPrefab {
    public:

        /** @brief ShopItemPrefab constructor
         *
         *  ShopItemPrefab constructor - it initializes all the gameobjects and components for the shop item UI
         *
         */
                                            ShopItemPrefab();


        /** @brief root gameobject getter
         *
         *  get the root gameobject handle of the prefab
         *
         * @return root gameobject handle
         */
        core::GoHandle                      getGoHandle() override;


        /** @brief item icon getter
         *
         *  get the item icon of the prefab
         *
         * @return item icon
         */
        components::Sprite*                 getIcon() const;


        /** @brief background frame getter
         *
         *  get the background frame of the prefab
         *
         * @return background frame
         */
        components::Sprite*                 getFrame() const;


        /** @brief item name text getter
         *
         *  get the item name text of the prefab
         *
         * @return item name text
         */
        components::Text*                   getText() const;

    private:
        core::GoHandle                      mRoot;          /*!< root gameobject handle */
        components::Sprite*                 mIcon;          /*!< cached icon sprite */
        components::Sprite*                 mFrame;         /*!< cached frame sprite */
        components::Text*                   mName;          /*!< cached item name text */
    };
}

#endif //GAME_SHOPITEMPREFAB_H
