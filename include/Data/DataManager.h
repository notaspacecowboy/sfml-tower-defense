//
// Created by Zheng Yang on 29/09/22.
//

#ifndef GAME_DATAMANAGER_H
#define GAME_DATAMANAGER_H

#include "Utils/Singleton.h"
#include <Data/PlayerData.h>
#include <Data/JsonBase.h>
#include <rapidjson/document.h>
#include <unordered_map>
# include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <LDtkLoader/Project.hpp>

namespace game::data {

    /** @brief all available data types
     *
     *  this defines all the available data types defined in json files in game data directory
     *
     *  @author Zheng Yang
     */
    enum class DataType {
        BUTTON,             /*!< button define data */
        ANIMATION,          /*!< animation define data */
        SHOP_ITEM,          /*!< shop item data */
        ENEMY,              /*!< enemy data */
        ENEMY_SPAWN_RULE,   /*!< enemy spawn rule data */
        TOWER,              /*!< tower data */
        PROJECTION          /*!< projection data */
    };

    typedef std::unordered_map<int, std::unique_ptr<data::JsonBase>>        DataMap;


    /** @brief manager class that handles all the in-game data serialization and deserialization
     *
     *  manager class that handles all the in-game data serialization and deserialization. It loads all the data defined
     *  in game data directory and deserialize them into data structures to be used in game. It also serializes player save
     *  file as json objects and store it at certain checkpoint of game
     *
     *  @author Zheng Yang
     */
    class DataManager: public utils::Singleton<DataManager> {
        friend class Singleton<DataManager>;

    public:

        /** @brief singleton initialization
         *
         *  singleton initialization
         *
         */
        void                                                                init();


        /** @brief load data from json and convert to c++ data structure
         *
         *  load data from json and convert to c++ data structure
         *
         */
        void                                                                loadData();             //might want to add an async version


        /** @brief register data type with its json file address
         *
         *  register data type with its json file address
         *
         *  @param type data type
         *  @param fileAddress json file address
         */
        void                                                                registerDataType(DataType type, std::string fileAddress);


        /** @brief load a specific data type from a json file file
         *
         *  load a specific data type from a json file file
         *
         *  @param type data type
         */
        template<typename TData>
        void                                                                loadData(DataType type);


        /** @brief get data by its type and id
         *
         *  get data by its type and id
         *
         *  @param type data type
         *  @param tid unique data id
         */
        template<typename TData>
        TData*                                                              get(DataType type, int tid);


        /** @brief get all of the data of a specific data type
         *
         *  get all of the data of a specific data type
         *
         *  @param type data type
         */
        std::unordered_map<int, std::unique_ptr<data::JsonBase>>&           getAll(DataType type);


        /** @brief get player save data
         *
         *  get player save data from a save file
         *
         */
        void                                                                loadAllSaveData();


        /** @brief get index of current selected save data
         *
         *  get index of current selected save data
         *
         */
        int                                                                 getCurrentPlayerIndex();


        /** @brief get all of player's save data
         *
         *  get all of player's save data
         *
         *  @return list of all player save data
         */
        const std::vector<std::unique_ptr<PlayerData>>&                     getAllSaveData() const;


        /** @brief read player state from a save data
         *
         *  read player state from a save data
         *
         *  @param save data index
         */
        void                                                                loadPlayerFromIndex(int index);


        /** @brief save player state to a save data slot
         *
         *  save player state to a save data slot
         *
         *  @param save data slot
         */
        void                                                                savePlayerAtIndex(int index);


        /** @brief load game world data
         *
         *  load game world data from its file address
         *
         */
        void                                                                loadGridProject();


        /** @brief get game world data
         *
         *  get game world data define
         *
         *  @return game world data structure
         */
        const ldtk::Project&                                                getGridProject() const;

    private:
        /** @brief private constructor
         *
         *  private constructor to ensure singleton pattern
         *
         */
                                                                            DataManager();


        static const std::string                                            PlayerSaveFileLocation;         /*!< player save file location */

        int                                                                 mCurrentPlayerIndex;            /*!< index of currently selected save data */
        std::vector<std::unique_ptr<PlayerData>>                            mSaves;                         /*!< all player save data */
        std::unordered_map<DataType, std::string>                           mTypeToFileMapping;             /*!< data type to file address mapping */
        std::unordered_map<DataType, DataMap>                               mAllData;                       /*!< all in-game data read from json files */

        ldtk::Project                                                       mGridProject;                   /*!< game world data structure */
    };

    template<typename TData>
    void DataManager::loadData(game::data::DataType type) {
        std::string path = mTypeToFileMapping[type];
        auto &dataMap = mAllData[type];

        using namespace std;
        std::ifstream jsonFIle(path);
        stringstream ss;
        ss << jsonFIle.rdbuf();
        string json = ss.str();
        rapidjson::Document doc;
        if(!doc.Parse(json.c_str()).HasParseError() && doc.IsArray()) {
            const rapidjson::Value &array = doc;
            for(size_t i = 0; i < array.Size(); i++) {
                const rapidjson::Value& json = array[i];
                if(array[i].IsObject()) {
                    dataMap.insert(std::make_pair(json["tid"].GetInt(), new TData {json}));
                }
            }
        }
    }

    template<typename TData>
    TData* DataManager::get(game::data::DataType type, int tid) {
        auto iter = mAllData.find(type);
        if(iter == mAllData.end())
            return nullptr;

        DataMap &map = iter->second;
        auto dataIter = map.find(tid);
        if(dataIter == map.end())
            return nullptr;

        return static_cast<TData*>(dataIter->second.get());
    }
}

#endif //GAME_DATAMANAGER_H
