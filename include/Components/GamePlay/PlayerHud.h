//
// Created by Zheng Yang on 17/11/22.
//

#ifndef GAME_PLAYERHUD_H
#define GAME_PLAYERHUD_H

#include <Components/Component.h>
#include <Prefabs/PlayerHudPrefab.h>

namespace game::core {
    class PlayerState;
}

namespace game::components {
    /** @brief controller class for all the HUD UI elements displayed during gameplay
     *
     *  this is the controller class for all the HUD UI elements displayed during gameplay
     *  player hp, gold, points... more to be added in the future!
     *
     *  @author Zheng Yang
     */
    class PlayerHud: public Component {
    public:

        /** @brief player hud constructor
         *
         *  player hud constructor
         *
         *  @param owner owner of the component
         *  @param prefab player hud prefab
         */
                                                                        PlayerHud(GameObject &owner,
                                                                                 prefabs::PlayerHudPrefab prefab);


        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is enabled
        *
        */
        void                                                            onEnable() override;


        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is disabled
        *
        */
        void                                                            onDisable() override;


        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically every frame. This is where every component in the game gets updated
        *
        * @param deltaTime the time elpased between now and last frame
        */
        void                                                            tick(float deltaTime) override;


        /** @brief show player hud on screen
        *
        * call this API to show player hud on screen
        *
        */
        void                                                            show();

        /** @brief hide player hud from screen
        *
        * call this API to hide player hud from screen
        *
        */
        void                                                            hide();


    private:

        /** @brief callback for player hp change event
        *
        * callback for player hp change event - update player hp on player hud
        *
        */
        void                                                            OnPlayerHpChange(int changeAmount);


        /** @brief callback for player point change event
        *
        * callback for player hp change event - update player point on player hud
        *
        */
        void                                                            OnPlayerPointChange(int changeAmount);

        prefabs::PlayerHudPrefab                                        mPrefab;                    /*!< my prefab */
        core::PlayerState*                                              mPlayerState;               /*!< current player state */
        float                                                           mTimeElapsed;               /*!< time elapsed from the start of the game level */

        boost::signals2::connection                                     mPlayerHpChangeListener;    /*!< player hp change listener */
        boost::signals2::connection                                     mPlayerPointChangeListener; /*!< player point change listener */
    };
}

#endif //GAME_PLAYERHUD_H
