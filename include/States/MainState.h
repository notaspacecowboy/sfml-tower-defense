//
// Created by Zheng Yang on 31/10/22.
//

#ifndef GAME_MAINSTATE_H
#define GAME_MAINSTATE_H

#include <States/State.h>
#include <boost/signals2.hpp>

namespace game::states {


    /** @brief loading state
     *
     *  this state will be pushed to state machine when player goes to the main menu
     *
     *  @author Zheng Yang
     */
    class MainState: public State {
    public:

        /** @brief MainState constructor
         *
         * MainState constructor
         *
         * @param owner state machine
         *
         */
                                                        MainState(StateMachine* owner);

        /** @brief MainState destructor
        *
        * MainState destructor
        *
        */
                                                        ~MainState();


        /** @brief initialization of state
         *
         * initialization of state, called by state machine after state is created and put to the stack
         *
         */
        void                                            init() override;


        /** @brief callback for fade in animation complete event
         *
         * callback function for fade in animation complete event
         *
         */
        void                                            onFadeIn();


        /** @brief callback for start button click event
         *
         * callback function for start button click event
         *
         */
        void                                            onStartButtonClicked();


        /** @brief callback for quit button click event
         *
         * callback function for quit button click event
         *
         */
        void                                            onQuitButtonClicked();


        /** @brief callback for option button click event
         *
         * callback function for option button click event
         *
         */
        void                                            onOptionButtonClicked();


        /** @brief callback for shop button click event
         *
         * callback function for shop button click event
         *
         */
        void                                            onShopButtonClicked();


        /** @brief callback for save button click event
         *
         * callback function for save button click event
         *
         */
        void                                            onSaveAndLoadButtonClicked();


        /** @brief callback for test button click event
         *
         * callback function for test button click event
         *
         */
        void                                            onTestButtonClicked();

    private:
        boost::signals2::connection                     mStartButtonListener;               /*!< start button click listener */
        boost::signals2::connection                     mQuitButtonListener;                /*!< quit button click listener */
        boost::signals2::connection                     mOptionButtonListener;              /*!< option button click listener */
        boost::signals2::connection                     mShopButtonListener;                /*!< shop button click listener */
        boost::signals2::connection                     mSaveAndLoadButtonListener;         /*!< save button click listener */
        boost::signals2::connection                     mTestButtonListener;                /*!< test button click listener */
        boost::signals2::connection                     mFadeInListener;                    /*!< fade in animation complete event listener */

        bool                                            mFadeInComplete;                    /*!< is fade in animation completed */
    };
}

#endif //GAME_MAINSTATE_H
