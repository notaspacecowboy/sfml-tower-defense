//
// Created by zyang464 on 26/10/22.
//

#ifndef GAME_OBJECTWRAPPER_H
#define GAME_OBJECTWRAPPER_H

#include <cstdint>
#include <Utils/GuidGenerator.h>

namespace game::components {
    class GameObject;
}

namespace game::core {


    /** @brief wrapper class for object that may be referenced by object handler class
     *
     *  this class is the wrapper class for object that may be referenced by object handler class
     *
     *  @author Zheng Yang
     */
    template<class TObject>
    struct ObjectWrapper {

        /** @brief ObjectWrapper default constructor
         *
         *  ObjectWrapper default constructor
         *
         */
                                                ObjectWrapper();


        /** @brief ObjectWrapper constructor
         *
         *  ObjectWrapper constructor
         *  @param id guid of the object
         *  @param obj actual object
         *
         */
                                                ObjectWrapper(GUID id, TObject* obj);
                                                ObjectWrapper(ObjectWrapper<TObject>& other) = delete;
                                                ObjectWrapper(ObjectWrapper<TObject>&& other) noexcept;


        /** @brief ObjectWrapper destructor
         *
         *  ObjectWrapper destructor
         *
         */
                                                ~ObjectWrapper();

        ObjectWrapper<TObject>&                 operator=(ObjectWrapper<TObject>& other) = delete;
        ObjectWrapper<TObject>&                 operator=(ObjectWrapper<TObject>&& other) noexcept;



        /** @brief reset object wrapper to a default state
         *
         *  reset object wrapper to a default state
         *
         */
        void                                    reset();

        uint32_t                                guid;                   /*!< object guid */
        TObject*                                objectPtr;              /*!< pointer to the actual object */
        bool                                    allocatedThisFrame;     /*!< true if object is allocated this frame, otherwise false */
    };

    template<class TObject>
    ObjectWrapper<TObject>::ObjectWrapper()
            : guid(UINT32_MAX)
            , objectPtr(nullptr) {
    }

    template<class TObject>
    ObjectWrapper<TObject>::ObjectWrapper(GUID id, TObject *obj)
    : guid(id)
    , objectPtr(obj)
    , allocatedThisFrame(false) {
    }

    template<class TObject>
    ObjectWrapper<TObject>::ObjectWrapper(ObjectWrapper<TObject> &&other) noexcept  {
        guid = other.guid;
        objectPtr = other.objectPtr;
        allocatedThisFrame = other.allocatedThisFrame;

        other.guid = UINT32_MAX;
        other.objectPtr = nullptr;
        other.allocatedThisFrame = false;
    }

    template<class TObject>
    ObjectWrapper<TObject>::~ObjectWrapper() {
        if(objectPtr != nullptr) {
            delete objectPtr;
            objectPtr = nullptr;
        }
    }

    template<class TObject>
    ObjectWrapper<TObject> &ObjectWrapper<TObject>::operator=(ObjectWrapper<TObject> &&other) noexcept {
        guid = other.guid;
        objectPtr = other.objectPtr;
        allocatedThisFrame = other.allocatedThisFrame;

        other.guid = UINT32_MAX;
        other.objectPtr = nullptr;
        other.allocatedThisFrame = false;

        return *this;
    }

    template<class TObject>
    void ObjectWrapper<TObject>::reset() {
        if(objectPtr != nullptr) {
            delete objectPtr;
            objectPtr = nullptr;
        }
    }


    typedef ObjectWrapper<components::GameObject> GoWrapper;
}

#endif //GAME_OBJECTWRAPPER_H
