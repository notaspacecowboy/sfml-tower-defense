//
// Created by Zheng Yang on 26/10/22.
//

#include <Utils/GuidGenerator.h>
#include <Utils/Logger.h>

namespace game::utils {
    GUID GuidGenerator::generate() {
        static std::atomic_uint32_t guid = 0;
        Logger::log("GuidGenerator->current guid: " + std::to_string(guid + 1), 5);
        return guid++;
    }
}
