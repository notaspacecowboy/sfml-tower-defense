//
// Created by Zheng Yang on 26/10/22.
//

#ifndef GAME_GUIDGENERATOR_H
#define GAME_GUIDGENERATOR_H

#include <atomic>

typedef uint32_t GUID;

namespace game::utils {

/** @brief a simple runtime guid generator
 *
 *  This class contains a single static method that returns a monotonically increasing integer everytime it gets called
 *
 *  @author Zheng Yang
 */
class GuidGenerator {
public:

     /** @brief a simple guid generation function
     *
     *  this function maintains a static local variable, this variable is incremented and returned to the caller when
     *  this function gets called
     *
     *  @return a monotonically-increasing runtime guid
     */
    static GUID generate();
};
}

#endif //GAME_GUIDGENERATOR_H
