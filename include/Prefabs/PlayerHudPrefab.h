//
// Created by Zheng Yang on 16/11/22.
//

#ifndef GAME_PLAYERHUDPREFAB_H
#define GAME_PLAYERHUDPREFAB_H

#include <Prefabs/PrefabFactory.h>

namespace game::components {
    class Text;
    class GameObject;
    class Sprite;
    class Button;
}

namespace game::prefabs {

    /** @brief predefined player HUD menu
     *
     *  this class is the predefined player HUD menu that can be reused in different game states
     *
     *  @author Zheng Yang
     */
    class PlayerHudPrefab: public IPrefab {
    public:


        /** @brief PlayerHudPrefab constructor
         *
         *  PlayerHudPrefab constructor - it initializes all the gameobjects and components for the player HUD window
         *
         */
                                            PlayerHudPrefab();


        /** @brief root gameobject getter
         *
         *  get the root gameobject handle of the prefab
         *
         * @return root gameobject handle
         */
        core::GoHandle                      getGoHandle() override;


        /** @brief player hp text setter
         *
         *  set player hp text
         *
         * @param newHP new hp
         */
        void                                setHP(int newHP);


        /** @brief player point text setter
         *
         *  set player point text
         *
         * @param newMoney new point
         */
        void                                setPoint(int newMoney);


        /** @brief time elapsed from game start text setter
         *
         *  set time elapsed from game start text
         *
         * @param timeInSeconds new time
         */
        void                                setTimeElapsed(int timeInSeconds);


    private:


        /** @brief recalculate size of HUD frame when texts changes
         *
         *  recalculate size of HUD frame when texts changes
         *
         */
        void                                reCalculateBgSize();

        core::GoHandle                      mRoot;              /*!< root gameobject handle */
        components::GameObject*             mTopLeftGO;         /*!< cached top left frame  */
        components::Text*                   mHpText;            /*!< cached hp text */
        components::Text*                   mPointText;         /*!< cached point text */
        components::Text*                   mTimeElapsedText;   /*!< cached time elapsed text */
    };
}

#endif //GAME_PLAYERHUDPREFAB_H
