//
// Created by Zheng Yang on 26/09/22.
//

#ifndef DEMO_SINGLETON_H
#define DEMO_SINGLETON_H

namespace game::utils {

    /** @brief a implementation of the singleton pattern with lazy initialization
     *
     *  This class is a simple implementation of the singleton pattern, the singleton object is lazy initialized at the
     *  first time getInstance method get called
     *
     *  @author Zheng Yang
     */
    template<typename T>
    class Singleton {

    public:
        /** @brief get the singleton object of T class
        *
        *  this function maintains a static local variable as the singleton object of T, it gets initialized the first time
        *  this function gets called
        *
        *  @return the singleton object of T class
        */
        static T&                           getInstance() {
            static T instance;
            return instance;
        }

    protected:
        /** @brief private constructor as required in the singleton pattern
        *
        *  the constructor of the singleton class is made to be private because we do not want other authority to be able to
        *  create instances of a singleton class
        *
        */
                                            Singleton() {}

    public:
        /** @brief copy constructor is deleted
        *
        *  copy constructor is deleted as required for the singleton pattern
        *
        */
        Singleton(const T&)                 = delete;

        /** @brief copy assignment operator is deleted
        *
        *  copy assignment operator
        *
        */
        void                                operator=(const T&) = delete;
    };
}


#endif //DEMO_SINGLETON_H
