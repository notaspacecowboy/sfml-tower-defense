//
// Created by zyang464 on 26/10/22.
//

#ifndef GAME_OBJECTHANDLE_H
#define GAME_OBJECTHANDLE_H

#include <vector>
#include <memory>
#include <Core/ObjectWrapper.h>
#include <assert.h>

namespace game::components {
    class GameObject;
}

namespace game::core {


    /** @brief object reference handle
     *
     *  this class is an alternative / more efficient solution compared to std::shared_ptr & std::weak_ptr,
     *  instead of storing the actual object reference, this class caches the object guid and the index of the object in a global lookup table.
     *  To get the actual object reference from the object handle, it query the global look up table and compare the two guids. If guids are equal,
     *  then the object handle is still valid and we return object reference to caller, otherwise the object is invalid and we return nullptr
     *
     *  @author Zheng Yang
     */
    template<class TObject>
    class ObjectHandle {
    public:
        typedef std::vector<ObjectWrapper<TObject>> LookupTable;

        /** @brief ObjectHandle default constructor
         *
         *  ObjectHandle default constructor
         *
         */
                                                    ObjectHandle();


        /** @brief ObjectHandle constructor
         *
         *  ObjectHandle constructor
         *
         *  @param lookup global lookup table
         *  @param guid guid of the object it reference to
         */
                                                    ObjectHandle(LookupTable *lookup, uint32_t guid);


        /** @brief update guid of the object
         *
         *  update guid of the object
         *
         *  @param newID new guid
         */
        void                                        updateGUID(GUID newID);


        /** @brief reset object handle to empty
         *
         *  reset object handle to empty
         *
         */
        void                                        reset();


        /** @brief get the actual object handled by this object handle
         *
         *  get the actual object handled by this object handle
         * @return actual object if it is still valid, otherwise return nullptr
         */
        TObject*                                    get() const;


        /** @brief overload -> operator
         *
         *  overload -> operator
         */
        TObject*                                    operator->() const;


        /** @brief overload bool conversion
         *
         *  overload bool conversion
         *
         *  @return true if object reference is still valid, otherwise false
         */
        operator                                    bool() const;


    private:
        LookupTable*                                mLookup;            /*!< cached reference to global lookup table */
        uint32_t                                    mGUID;              /*!< guid of the object */
    };

    typedef ObjectHandle<components::GameObject>    GoHandle;

    template<class TObject>
    ObjectHandle<TObject>::ObjectHandle()
            :mLookup(nullptr)
            ,mGUID(UINT32_MAX){
    }

    template<class TObject>
    ObjectHandle<TObject>::ObjectHandle(LookupTable *lookup, uint32_t guid)
            :mLookup(lookup)
            ,mGUID(guid){
    }

    template<class TObject>
    void ObjectHandle<TObject>::updateGUID(GUID newID) {
        mGUID = newID;
    }

    template<class TObject>
    void ObjectHandle<TObject>::reset() {
        mGUID = INT32_MAX;
    }


    template<class TObject>
    TObject* ObjectHandle<TObject>::get() const {
        if(mGUID == INT32_MAX|| mLookup == nullptr)
            return nullptr;

        ObjectWrapper<TObject> &info = (*mLookup)[mGUID % mLookup->size()];
        if(mGUID != info.guid)
            return nullptr;

        return info.objectPtr;
    }

    template<class TObject>
    TObject *ObjectHandle<TObject>::operator->() const {
        auto ptr = get();
        //make sure to perform null check before using this!
        //change handle->mem_func() to
        //if(handle) {handle->mem_func()}
        assert(ptr != nullptr);
        return ptr;
    }

    template<class TObject>
    ObjectHandle<TObject>::operator bool() const {
        return get() != nullptr;
    }
}

#endif //GAME_OBJECTHANDLE_H
