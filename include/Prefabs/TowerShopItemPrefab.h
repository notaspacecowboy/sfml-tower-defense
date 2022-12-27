//
// Created by Zheng Yang on 25/11/22.
//

#ifndef GAME_TOWERSHOPPREFAB_H
#define GAME_TOWERSHOPPREFAB_H

#include <Prefabs/PrefabFactory.h>

namespace game::components {
    class Sprite;
    class SimpleButton;
}

namespace game::prefabs {


    /** @brief predefined tower shop menu
     *
     *  this class is the predefined tower UI menu that can be reused in different game states
     *
     *  @author Zheng Yang
     */
    class TowerShopItemPrefab: public IPrefab {
    public:

        /** @brief TowerShopItemPrefab constructor
         *
         *  TowerShopItemPrefab constructor - it initializes all the gameobjects and components for the tower shop item UI
         *
         */
        TowerShopItemPrefab();


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

    private:
        core::GoHandle                      mRoot;          /*!< root gameobject handle */
        components::Sprite*                 mIcon;          /*!< cached icon sprite */
    };
}

#endif //GAME_TOWERSHOPPREFAB_H
