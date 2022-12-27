//
// Created by Zheng Yang on 29/09/22.
//

#include "ResourceManager.h"
#include <assert.h>

namespace game::resource {
    template<typename TResource>
    void ResourceManager<TResource>::init() {
    }

//    template<typename TResource>
//    TResource *ResourceManager<TResource>::get(int tid) const {
//        //assert for now if trying to get an unloaded resource
//        auto result = mResources.find(tid);
//        assert(result != mResources.end());
//
//        return result->second.get();
//    }

    template<typename TResource>
    bool ResourceManager<TResource>::contains(int tid) const {
        //assert for now if trying to get an unloaded resource
        return mResources.find(tid) != mResources.end();
    }


    template<typename TResource>
    ResourceManager<TResource>::ResourceManager() {}





    //version 2
    template<typename TResource>
    void ResourceManager<TResource>::load(int tid, const std::string& path) {
        //if already loaded, do nothing
        if(mResources.find(tid) != mResources.end())
            return;

        auto resource = std::make_unique<TResource>();
        if(!resource->loadFromFile(path))
            throw std::runtime_error("ResourceManager::init() => load failed " + path);

        mResources.insert(std::make_pair(tid, std::move(resource)));
    }


    template<typename TResource>
    void ResourceManager<TResource>::load(int tid) {
        //if already loaded, do nothing
        if(mResources.find(tid) != mResources.end())
            return;

        auto findPath = mIdToPathMapping.find(tid);
        assert(findPath != mIdToPathMapping.end());

        auto path = findPath->second;
        load(tid, path);
    }


    template<typename TResource>
    void ResourceManager<TResource>::loadAll() {
        for(auto idPathPair: mIdToPathMapping) {
            load(idPathPair.first, idPathPair.second);
        }
    }

    template<typename TResource>
    void ResourceManager<TResource>::registerResource(std::string resourceName, int tid, std::string path) {
        auto nameIdExist = mNameToIdMapping.find(resourceName);
        assert(nameIdExist == mNameToIdMapping.end());
        mNameToIdMapping.insert(std::make_pair(resourceName, tid));

        auto idPathExist = mIdToPathMapping.find(tid);
        assert(idPathExist == mIdToPathMapping.end());
        mIdToPathMapping.insert(std::make_pair(tid, path));
    }

    template<typename TResource>
    TResource* ResourceManager<TResource>::getByID(int tid) const {
        //assert for now if trying to get an unloaded resource
        auto result = mResources.find(tid);
        if(result == mResources.end())
            return nullptr;

        return result->second.get();
    }

    template<typename TResource>
    TResource* ResourceManager<TResource>::getByName(std::string name) const {
        auto result = mNameToIdMapping.find(name);
        if(result == mNameToIdMapping.end())
            return nullptr;

        return getByID(result->second);
    }
}