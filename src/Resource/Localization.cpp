//
// Created by Zheng Yang on 31/10/22.
//

#include <Resource/Localization.h>
#include <fstream>
#include <Utils/Logger.h>

namespace game::resource {
    Localization::Localization(): mLookup() {}

    void Localization::init() {}

    void Localization::loadMasterText() {
        std::ifstream file("./assets/mastertext.tsv");
        std::string str;

        //header line, ignore
        std::getline(file, str);
        while (std::getline(file, str))
        {
            int idEnd = str.find('\t');
            std::string id = str.substr(0, idEnd - 0);
            std::string text = str.substr(idEnd + 1);
            mLookup.insert(std::make_pair(id, text));
        }
    }

    std::string Localization::get(std::string textID) {
        auto find = mLookup.find(textID);
        if(find != mLookup.end()) {
            return find->second;
        }

        return textID;
    }
}