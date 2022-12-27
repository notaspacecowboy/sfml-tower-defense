//
// Created by Zheng Yang on 05/11/22.
//


#ifndef GAME_IPREFAB_H
#define GAME_IPREFAB_H

#include <Core/ObjectHandle.h>

namespace game::prefabs {
    class IPrefab {


        /** @brief root gameobject getter
         *
         *  get the root gameobject handle of the prefab
         *
         * @return root gameobject handle
         */
        virtual core::GoHandle getGoHandle() = 0;
    };
}
#endif //GAME_IPREFAB_H
