//
// Created by Zheng Yang on 06/11/22.
//

#ifndef GAME_SAVESLOTPREFAB_H
#define GAME_SAVESLOTPREFAB_H

#include <Prefabs/PrefabFactory.h>

namespace game::components {
    class Sprite;
    class Text;
}

namespace game::prefabs {

    /** @brief predefined game save slot menu
     *
     *  this class is the predefined game save slot menu that can be reused in different game states
     *
     *  @author Zheng Yang
     */
    class SaveSlotPrefab: public IPrefab {
    public:

        /** @brief SaveSlotPrefab constructor
         *
         *  SaveSlotPrefab constructor - it initializes all the gameobjects and components for the save slot menu
         *
         */
                                            SaveSlotPrefab();


        /** @brief root gameobject getter
         *
         *  get the root gameobject handle of the prefab
         *
         * @return root gameobject handle
         */
        core::GoHandle                      getGoHandle() override;


        /** @brief background frame getter
         *
         *  get the background frame of the prefab
         *
         * @return save slot background frame sprite
         */
        components::Sprite*                 getFrame() const;


        /** @brief selected sprite getter
         *
         *  get the selected sprite of the prefab
         *
         * @return selected sprite
         */
        components::Sprite*                 getSelectedSprite() const;


        /** @brief level text getter
         *
         *  get the level text of the prefab
         *
         * @return level text
         */
        components::Text*                   getLevelText() const;


        /** @brief gold text getter
         *
         *  get the gold text of the prefab
         *
         * @return gold text
         */
        components::Text*                   getGoldText() const;


        /** @brief time text getter
         *
         *  get the time text of the prefab
         *
         * @return time text
         */
        components::Text*                   getTimeText() const;



    private:
        core::GoHandle                      mRoot;                  /*!< root gameobject handle */
        components::Sprite*                 mFrame;                 /*!< cached frame sprite */
        components::Sprite*                 mSelectedSprite;        /*!< cached selected sprite */
        components::Text*                   mLevelText;             /*!< cached level text */
        components::Text*                   mGoldText;              /*!< cached gold text */
        components::Text*                   mTimeText;              /*!< cached time text */
    };
}

#endif //GAME_SAVESLOTPREFAB_H
