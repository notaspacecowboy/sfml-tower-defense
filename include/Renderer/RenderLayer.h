//
// Created by zyang464 on 20/10/22.
//

#ifndef GAME_RENDERLAYER_H
#define GAME_RENDERLAYER_H

namespace game::renderer {

    /** @brief all render layers
     *
     *  this enum defines enumerators for all render layers
     *  current render order: background -> entity -> UI
     *
     *  @author Zheng Yang
     */
    enum RenderLayer {
        BACKGROUND,     /*!< backgeound layer */
        ENTITY,         /*!< entity layer */
        UI              /*!< UI layer */
    };
}


#endif //GAME_RENDERLAYER_H
