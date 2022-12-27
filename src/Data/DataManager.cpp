//
// Created by Zheng Yang on 29/09/22.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <rapidjson/document.h>
#include <Data.h>
#include <random>
#include <Core/GameManager.h>

using namespace game::core;

namespace game::data {
    const std::string DataManager::PlayerSaveFileLocation = "./saveFile";

    DataManager::DataManager(): mCurrentPlayerIndex(0) {}

    void DataManager::init() {
        registerDataType(DataType::ANIMATION        , "./data/AnimDefine.json");
        registerDataType(DataType::BUTTON           , "./data/ButtonDefine.json");
        registerDataType(DataType::SHOP_ITEM        , "./data/ShopItemDefine.json");
        registerDataType(DataType::ENEMY            , "./data/EnemyDefine.json");
        registerDataType(DataType::ENEMY_SPAWN_RULE , "./data/EnemySpawnRuleDefine.json");
        registerDataType(DataType::TOWER            , "./data/TowerDefine.json");
        registerDataType(DataType::PROJECTION       , "./data/ProjectionDefine.json");
    }

    void DataManager::registerDataType(game::data::DataType type, std::string fileAddress) {
        mTypeToFileMapping.insert(std::make_pair(type, fileAddress));
        mAllData.insert(std::make_pair(type, DataMap()));
    }

    void DataManager::loadData() {
        loadData<AnimDefine>(DataType::ANIMATION);
        loadData<ButtonDefine>(DataType::BUTTON);
        loadData<ShopItemDefine>(DataType::SHOP_ITEM);
        loadData<EnemyDefine>(DataType::ENEMY);
        loadData<EnemySpawnRuleDefine>(DataType::ENEMY_SPAWN_RULE);
        loadData<TowerDefine>(DataType::TOWER);
        loadData<ProjectionDefine>(DataType::PROJECTION);

        loadAllSaveData();
        loadGridProject();
    }

    std::unordered_map<int, std::unique_ptr<data::JsonBase>> &DataManager::getAll(game::data::DataType type) {
        return mAllData[type];
    }

    void DataManager::loadAllSaveData() {
        using namespace std;
        std::ifstream jsonFIle(PlayerSaveFileLocation);

        if(jsonFIle.fail()) {
            for(int i = 0; i < 4; i++) {
                mSaves.emplace_back(nullptr);
            }
            return;
        }
        stringstream ss;
        ss << jsonFIle.rdbuf();
        string json = ss.str();
        rapidjson::Document doc;
        if(!doc.Parse(json.c_str()).HasParseError()) {
            const rapidjson::Value &saveFileInfo = doc;
            mCurrentPlayerIndex = saveFileInfo["lastRunPlayer"].GetInt();

            const rapidjson::Value &allPlayerSaves = saveFileInfo["allSaves"];
            for(int i = 0; i < 4; i++) {
                auto slot = std::to_string(i).c_str();
                if(allPlayerSaves.HasMember(slot)) {
                    const rapidjson::Value& json = allPlayerSaves[slot];
                    mSaves.emplace_back(new PlayerData(json));
                }
                else {
                    mSaves.emplace_back(nullptr);
                }
            }
        }
    }

    void DataManager::loadGridProject() {
        mGridProject.loadFromFile("./data/MapDefine.ldtk");
    }

    const ldtk::Project &DataManager::getGridProject() const {
        return mGridProject;
    }

    int DataManager::getCurrentPlayerIndex() {
        return mCurrentPlayerIndex;
    }

    void DataManager::loadPlayerFromIndex(int index) {
        if(mSaves[index].get() == nullptr) {
            auto newPlayerPtr = std::make_unique<PlayerData>();
            mSaves[index].swap(newPlayerPtr);
        }

        auto newPlayer = mSaves[index].get();
        GameManager::getInstance().getPlayerState()->load(newPlayer);
        mCurrentPlayerIndex = index;
    }

    const std::vector<std::unique_ptr<PlayerData>> &DataManager::getAllSaveData() const {
        return mSaves;
    }

    void DataManager::savePlayerAtIndex(int index) {
        using namespace std;

        if(mSaves[index].get() == nullptr) {
            auto newPlayer = std::make_unique<PlayerData>();
            mSaves[index].swap(newPlayer);
        }

        GameManager::getInstance().getPlayerState()->save(mSaves[index].get());
        mCurrentPlayerIndex = index;

        rapidjson::StringBuffer s;
        rapidjson::Writer<rapidjson::StringBuffer> writer(s);

        writer.StartObject();
        writer.String("lastRunPlayer");
        writer.Int(mCurrentPlayerIndex);

        writer.String("allSaves");
        writer.StartObject();
        for(int i = 0; i < mSaves.size(); i++) {
            if(mSaves[i].get() != nullptr) {
                writer.String(std::to_string(i).c_str());
                mSaves[i]->toJson(&writer);
            }
        }
        writer.EndObject();
        writer.EndObject();

        unique_ptr<string> json(new string(s.GetString()));
        ofstream stream(PlayerSaveFileLocation);
        stream << *json;
        json.reset();
        stream.close();
    }
}