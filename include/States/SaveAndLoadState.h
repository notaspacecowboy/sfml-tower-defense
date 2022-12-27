//
// Created by Zheng Yang on 06/11/22.
//

#ifndef GAME_SAVEANDLOADSTATE_H
#define GAME_SAVEANDLOADSTATE_H

#include <States/State.h>

namespace game::components {
    class SaveSlot;
}

namespace game::states {


    /** @brief save and load state
     *
     *  this state will be pushed to state machine when player go to the save menu
     *
     *  @author Zheng Yang
     */
    class SaveAndLoadState: public State {
    public:

        /** @brief SaveAndLoadState constructor
         *
         * SaveAndLoadState constructor
         *
         * @param owner state machine
         *
         */
                                                        SaveAndLoadState(StateMachine* owner);


        /** @brief SaveAndLoadState destructor
         *
         * SaveAndLoadState destructor
         *
         */
                                                        ~SaveAndLoadState();


        /** @brief initialization of state
         *
         * initialization of state, called by state machine after state is created and put to the stack
         *
         */
        void                                            init() override;


        /** @brief callback for back button click event
         *
         * callback function for back button click event
         *
         */
        void                                            onBackButtonClick();


        /** @brief callback for save button click event
         *
         * callback function for save button click event
         *
         */
        void                                            onSaveFileSelected(components::SaveSlot* selected);

    private:
        boost::signals2::connection                     mBackButtonListener;         /*!< back button click listener */

    };
}

#endif //GAME_SAVEANDLOADSTATE_H
