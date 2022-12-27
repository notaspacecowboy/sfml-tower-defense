//
// Created by Zheng Yang on 06/11/22.
//

#ifndef GAME_SAVESLOT_H
#define GAME_SAVESLOT_H

#include <Data/PlayerData.h>
#include <boost/signals2.hpp>
#include <Components/Component.h>
#include <Components/GameObject.h>
#include <Input/InputEventHandler.h>
#include <Prefabs/SaveSlotPrefab.h>

namespace game::components {
    class SaveSlot;
    typedef boost::signals2::signal<void(SaveSlot*)>                    PlayerDataSelectedDelegate;

    /** @brief controller class for player save slot in the save and load state
     *
     *  this is the controller class for player save slot in the save and load state
     *
     *  @author Zheng Yang
     */
    class SaveSlot: public Component, public input::IPointerClick {
    public:

        /** @brief save slot constructor
         *
         *  save slot constructor
         *
         *  @param owner owner of the component
         *  @param data player save data
         *  @param prefab save slot prefab
         *  @param index index of my save data
         *  @param isSelected is the save slot selected
         */
                                                                        SaveSlot(GameObject &owner,
                                                                                const data::PlayerData* data,
                                                                                prefabs::SaveSlotPrefab prefab,
                                                                                int index,
                                                                                bool isSelected);


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


        /** @brief callback for pointer click event
        *
        * callback for pointer click event - set save slot to be selected or deselected
        *
        */
        void                                                            onPointerClick() override;


        /** @brief get index of the save slot
        *
        *  get index of the save slot
        * @return index of the save slot
        */
        int                                                             getIndex() const;


        PlayerDataSelectedDelegate                                      onPlayerDataSelected;       /*!< player data selected event */

    private:
        const data::PlayerData*                                         mData;                      /*!< my save data */
        prefabs::SaveSlotPrefab                                         mPrefab;                    /*!< my prefab */
        int                                                             mIndex;                     /*!< my index */
        bool                                                            mIsSelected;                /*!< select state flag */
    };
}

#endif //GAME_SAVESLOT_H
