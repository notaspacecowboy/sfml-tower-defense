//
// Created by Zheng Yang on 31/10/22.
//

#ifndef GAME_LOCALIZATION_H
#define GAME_LOCALIZATION_H

#include <Utils/Singleton.h>
#include <unordered_map>
#include <string>

namespace game::resource {


    /** @brief game text localization manager
     *
     *  this class maintains a mapping between in-game text reference ids and the actual texts, which are defined in the
     *  master text file in csv format
     *
     *  @author Zheng Yang
     */
    class Localization: public utils::Singleton<Localization> {
        friend class utils::Singleton<Localization>;
    public:

        /** @brief localization manager initialization
         *
         *  call this function to initialization localization manager before using any of its APIs
         *
         */
        void                                                init();


        /** @brief load game master text
         *
         *  load game master text from project directory, the master text is defined in csv format
         *
         */
        void                                                loadMasterText();


        /** @brief get game text by its referenced id
         *
         *  get game text by its referenced id
         *
         *  @param textID text reference id
         *
         */
        std::string                                         get(std::string textID);

    private:


        /** @brief private constructor
         *
         *  private constructor to ensure singleton pattern
         *
         *
         */
                                                            Localization();

        std::unordered_map<std::string, std::string>        mLookup;            /*!< ref id to text mapping */
    };
}

#endif //GAME_LOCALIZATION_H
