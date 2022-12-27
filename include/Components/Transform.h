//
// Created by Zheng Yang on 08/10/22.
//

#ifndef GAME_TRANSFORM_H
#define GAME_TRANSFORM_H

#include <Components/Component.h>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace game::components {
    enum Anchor: short {
        ANCHOR_TOP_LEFT,
        ANCHOR_TOP_MIDDLE,
        ANCHOR_TOP_RIGHT,
        ANCHOR_MIDDLE_LEFT,
        ANCHOR_CENTER,
        ANCHOR_MIDDLE_RIGHT,
        ANCHOR_BOT_LEFT,
        ANCHOR_BOT_MIDDLE,
        ANCHOR_BOT_RIGHT
    };

    enum Pivot: short {
        PIVOT_TOP_LEFT = 0,
        PIVOT_TOP_MIDDLE = 1,
        PIVOT_TOP_RIGHT = 2,
        PIVOT_MIDDLE_LEFT = 3,
        PIVOT_CENTER = 4,
        PIVOT_MIDDLE_RIGHT = 5,
        PIVOT_BOT_LEFT = 6,
        PIVOT_BOT_MIDDLE = 7,
        PIVOT_BOT_RIGHT = 8
    };



    /** @brief transform component of a gameobject
     *
     *  this class defines the size, position, rotation and scale of a gameobject in the game world
     *  it also defines a hierarchy system of gameobjects - a transform can be set to be the parent of other transforms, this set
     *  the origin of the local positions of its child to be the position of the current transform
     *
     *  @author Zheng Yang
     */
    class Transform: public Component {
        friend class GameObject;
    public:

        /** @brief transform destructor
         *
         *  transform destructor
         *
         */
                                    ~Transform();


        /** @brief set parent of current transform
         *
         *  set parent of current transform
         * @param owner new parent
         */
        void                        setParent(Transform* owner);


        /** @brief get parent of current transform
         *
         *  get parent of current transform
         * @return parent transform
         */
        Transform*                  getParent() const;


        /** @brief set local position of current transform
         *
         *  set local position of current transform
         * @param newPos new local position
         */
        void                        setLocalPosition(sf::Vector2f newPos);


        /** @brief set local position of current transform
         *
         *  set local position of current transform
         * @param x new position in x axis
         * @param y new position in y axis
         */
        void                        setLocalPosition(float x, float y);


        /** @brief get local position of current transform
         *
         *  get local position of current transform
         * @return local position
         */
        sf::Vector2f                getLocalPosition() const;


        /** @brief get world position of current transform
         *
         *  get world position of current transform
         * @return world position
         */
        sf::Vector2f                getWorldPosition();


        /** @brief set anchor of the transform
         *
         *  set anchor of the transform
         * @param newAnchor new anchor
         */
        void                        setAnchor(Anchor newAnchor);


        /** @brief get anchor of current transform
         *
         *  get anchor of current transform
         * @return anchor
         */
        Anchor                      getAnchor() const;


        /** @brief set pivot of the transform
         *
         *  set pivot of the transform
         * @param newPivot new pivot
         */
        void                        setPivot(Pivot newPivot);


        /** @brief get pivot of current transform
         *
         *  get pivot of current transform
         * @return pivot
         */
        Pivot                       getPivot() const;


        /** @brief set size of the transform
         *
         *  set size of the transform
         * @param newSize new size
         */
        void                        setSize(sf::Vector2f newSize);


        /** @brief set size of the transform
         *
         *  set size of the transform
         * @param width new width
         * @param height new height
         */
        void                        setSize(float width, float height);


        /** @brief get size of current transform
         *
         *  get size of current transform
         * @return size
         */
        sf::Vector2f                getSize() const;


        /** @brief get scale of current transform
         *
         *  get scale of current transform
         * @return scale
         */
        sf::Vector2f                getScale() const;


        /** @brief set scale of the transform
         *
         *  set scale of the transform
         * @param x new scale in x axis
         * @param y new scale in y axis
         */
        void                        setScale(float x, float y);


        /** @brief set the size and position of the current transform to match its parent
         *
         *  set the size and position of the current transform to match its parent
         *
         */
        void                        matchParent();


        /** @brief move a transform from its current position
         *
         *  move a transform from its current position for a certain distance
         *
         *  @param width translation of transform in x axis
         *  @param height translation of transform in y axis
         */
        void                        move(float width, float height);


        /** @brief set rotation of the transform
         *
         *  set rotation of the transform
         * @param angle new angle
         */
        void                        setRotate(float angle);


        /** @brief rotate transform for a certain angle
         *
         * rotate transform for a certain angle
         * @param angle rotate angle
         */
        void                        rotate(float angle);


        /** @brief get rotation of current transform
         *
         *  get rotation of current transform
         * @return rotation
         */
        float                       getRotate() const;


        /** @brief get number of children in current transform
         *
         *  get number of children in current transform
         * @return number of children in current transform
         */
        int                         getChildrenCount() const;

    private:


        /** @brief Transform constructor
         *
         *  Transform constructor
         *
         *  @param owner owner of the component
         */
                                    Transform(GameObject &owner);


        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is enabled
        *
        */
        void                        onEnable();


        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is disabled
        *
        */
        void                        onDisable();


        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically every frame. This is where every component in the game gets updated
        *
        * @param deltaTime the time elpased between now and last frame
        */
        void                        tick(float deltaTime);


        /** @brief set the dirty flag of current transform
        *
        * set the dirty flag of current transform - this function can be called recursively if the transform has a parent
        * this->setdirty() => parent->setdirty() => parent->parent->setDirty => ...
        *
        */
        void                        setDirty();


        /** @brief add a child for current transform
        *
        * add a child for current transform, also set the parent of the child as current transform
        *
        * @param child new child
        */
        void                        attachChild(Transform* child);


        /** @brief remove a child from child list
        *
        * remove a child from child list, also set the parent of the child as nullptr
        *
        * @param child child to be removed
        */
        void                        detachChild(const Transform* child);


        /** @brief reset transform
        *
        * reset transform to a default state
        *
        */
        void                        reset();

        Transform*                  mParent;                    /*!< my parent transform */
        std::vector<Transform*>     mChildren;                  /*!< my children list */

        bool                        mIsDirty;                   /*!< my dirty flag */

        sf::Vector2f                mSize;                      /*!< my size */
        sf::Vector2f                mLocalPosition;             /*!< my local position */
        sf::Vector2f                mCachedWorldPosition;       /*!< my cached world position */
        float                       mRotate;                    /*!< my rotation */
        sf::Vector2f                mScale;                     /*!< my scale */
        Anchor                      mAnchor;                    /*!< my anchor */
        Pivot                       mPivot;                     /*!< my pivot */

    };
} // game::components

#endif //GAME_TRANSFORM_H
