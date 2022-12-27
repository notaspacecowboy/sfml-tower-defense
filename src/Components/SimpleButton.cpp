//
// Created by Zheng Yang on 17/11/22.
//

#include <Components.h>


namespace game::components {
    SimpleButton::SimpleButton(game::components::GameObject &owner): Component(owner) {}

    SimpleButton::~SimpleButton() noexcept {}

    void SimpleButton::onEnable() {
        mDrawable = mOwner.getComponent<RenderComponent>();
    }

    void SimpleButton::onDisable() {
    }

    RenderComponent *SimpleButton::getDrawable() const {
        return mDrawable;
    }

    void SimpleButton::setRaycastable(bool isRaycastable) {
        if(mDrawable != nullptr)
            mDrawable->setRaycastable(isRaycastable);
    }

    void SimpleButton::onPointerClick() {
        if(!onClick.empty())
            onClick();
    }
}
