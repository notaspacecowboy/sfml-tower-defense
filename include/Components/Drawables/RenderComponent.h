//
// Created by Zheng Yang on 20/10/22.
//

#ifndef GAME_RENDERABLECOMPONENT_H
#define GAME_RENDERABLECOMPONENT_H

#include "Components/Transform.h"
#include <SFML/Graphics.hpp>
#include "Renderer/RenderLayer.h"


namespace game::components {

/** @brief base class for all the drawables in the game
 *
 *  everything in our game that can be saw by the player contains a drawable component inherited from this class
 *  this is an abstract class
 *
 *  @author Zheng Yang
 */
class RenderComponent: public Component {
    public:

        /** @brief render component constructor
         *
         *  render component constructor
         *
         *  @param owner owner of the component
         *  @param layer render layer of drawable
         *  @param depth render depth of drawable
         */
                                        RenderComponent(GameObject& owner, renderer::RenderLayer layer, int depth);

        /** @brief render component destructor
        *
        *  render component destructor
        *
        */
         virtual                        ~RenderComponent();        //do we really want this to be virtual?

        /** @brief draw quad to screen
        *
        *  do not call it - this function should only be called by game renderer every frame
        *  this is where drawable components actually gets drawed to the screen
        *
        *  @param window the game window to render the quad on
        */
         virtual void                   draw(sf::RenderWindow &window);

        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is enabled
        *
        */
         virtual void                   onEnable() override;

        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is disabled
        *
        */
         virtual void                   onDisable() override;

        /** @brief set the alpha value of the drawable
        *
        * set the alpha value of the drawable
        *
        * @param alpha 1 means entirely opaque, 0 means entirely transparent
        */
         virtual void                   setAlpha(float alpha);

        /** @brief set the rotation value of the drawable
        *
        * set the rotation value of the drawable
        *
        * @param angle the angle between the drawable and +x axis
        */
         virtual void                   setRotate(float angle);

        /** @brief rotate drawable
        *
        * rotate drawable of a certain angle
        *
        * @param angle the angle between its current rotation to the new rotation
        */
         virtual void                   rotate(float angle);

        /** @brief determines if a render component can be detected by input system and block pointer
        *
        * determines if a render component can be detected by input system
        *
        * @return true if drawable can be detected by pointer, false otherwise
        */
         virtual bool                   isRaycastable();

        /** @brief set if a drawable can be detected by input system and block pointer
        *
        * set if a drawable can be detected by input system and block pointer
        *
        * @param isRaycastable true if you want the drawable to be detected and block pointer, false otherwise
        */
         void                           setRaycastable(bool isRaycastable);

        /** @brief get the size of the drawable
        *
        * get the size of the drawable
        *
        * @return size of the drawable
        */
         sf::Vector2f                   getSize() const;

        /** @brief get the bounding box of the drawable
        *
        * get the bounding box of the drawable
        *
        * @return bounding box of the drawable
        */
         sf::FloatRect                  getBoundingBox() const;

        /** @brief get the depth of the drawable
        *
        * get the depth of the drawable
        *
        * @return depth of the drawable
        */
         int                            getDepth() const;

        /** @brief get the layer of the drawable
        *
        * get the layer of the drawable
        *
        * @return layer of the drawable
        */
         renderer::RenderLayer          getLayer() const;


    protected:
        Transform*                      mTransform;          /*!< my cached transform */
        renderer::RenderLayer           mLayer;              /*!< my cached render layer */
        int                             mDepth;              /*!< my cached depth in my render layer */
        static const int                LayerModifier;       /*!< the layer modifier */
        bool                            mIsRaycastable;      /*!< true if render component is raycastable and blocks pointer, false otherwise */
    };
}

#endif //GAME_RENDERABLECOMPONENT_H
