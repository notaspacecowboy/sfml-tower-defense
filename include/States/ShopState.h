//
// Created by Zheng Yang on 05/11/22.
//

#ifndef GAME_SHOPSTATE_H
#define GAME_SHOPSTATE_H

#include "State.h"
#include <Data/ShopItemDefine.h>

namespace game::components {
    class Text;
    class Sprite;
};

namespace game::core {
    class PlayerState;
}

namespace game::states {


    /** @brief shop state
     *
     *  this state will be pushed to state machine when player goes to the shop menu
     *
     *  @author Zheng Yang
     */
    class ShopState: public State {
    public:

        /** @brief ShopState constructor
         *
         * ShopState constructor
         *
         * @param owner state machine
         *
         */
                                                        ShopState(StateMachine* owner);


        /** @brief ShopState destructor
         *
         * ShopState destructor
         *
         */
                                                        ~ShopState();


        /** @brief initialization of state
         *
         * initialization of state, called by state machine after state is created and put to the stack
         *
         */
        void                                            init() override;


        /** @brief callback for item selected event
         *
         * callback function for item selected event
         *
         * @param data item data
         */
        void                                            onItemSelect(const data::ShopItemDefine* data);


        /** @brief callback for buy button click event
         *
         * callback function for buy button click event
         *
         */
        void                                            onBuyButtonClick();


        /** @brief callback for back button click event
         *
         * callback function for back button click event
         *
         */
        void                                            onBackButtonClick();


        /** @brief check if purchase is valid
         *
         * check if purchase is valid when player tries to buy an item
         *
         */
        void                                            checkValidity();

    private:
        const data::ShopItemDefine*                     mCurrentSelected;           /*!< currently selected item */
        game::components::Button*                       mPurchaseButton;            /*!< purchase button */
        game::components::Text*                         mCurrentName;               /*!< item name text */
        game::components::Sprite*                       mCurrentIcon;               /*!< item icon sprite */
        game::components::Text*                         mCurrentDescription;        /*!< item description text */
        game::components::Text*                         mCurrentCost;               /*!< item cost text */
        game::components::Text*                         mCurrentGold;               /*!< player gold text */
        game::components::Text*                         mItemOwned;                 /*!< item owned text */
        game::components::Text*                         mNotEnoughGold;             /*!< not enough gold text */

        boost::signals2::connection                     mBuyButtonListener;         /*!< buy button listener */
        boost::signals2::connection                     mBackButtonListener;        /*!< back button listener */

        core::PlayerState*                              mPlayerState;
    };
}


#endif //GAME_SHOPSTATE_H
