#include <Components/GameObject.h>

namespace game::components {

    inline Transform *GameObject::getTransform() {
        return mTransform;
    }

    inline Transform *GameObject::getParent() {
        return this->getTransform()->getParent();
    }

    GUID GameObject::getGUID() const {
        return mID;
    }


    template<class TComponent, typename ...Args>
    TComponent* GameObject::addComponent(Args&&... args) {
        TComponent* ptr = nullptr;
        for(auto &component: mComponents) {
                assert(dynamic_cast<TComponent*>(component.get()) == nullptr);    //we don't want any components to be added to the same go twice
        }

        std::unique_ptr<TComponent> component(new TComponent(*this, args...));
        if(mState == GoState::ACTIVE)
            component->onEnable();

        mComponents.push_back(std::move(component));
        return getComponent<TComponent>();
    }

    template<class TComponent>
    TComponent* GameObject::getComponent() {
        TComponent* ptr = nullptr;
        for(auto &component: mComponents) {
            ptr = dynamic_cast<TComponent*>(component.get());
            if(ptr != nullptr)
                return ptr;
        }

        return nullptr;
    }

    template<class TComponent>
    void GameObject::getComponents(std::vector<TComponent *> &components) {
        components.clear();
        TComponent* ptr = nullptr;
        for(auto &component: mComponents) {
            ptr = dynamic_cast<TComponent*>(component.get());
            if(ptr != nullptr)
                components.push_back(ptr);
        }
    }

    template<class TComponent>
    bool GameObject::removeComponent() {
        TComponent* ptr = nullptr;
        bool found = false;
        for(auto &iter: mComponents) {
            if(dynamic_cast<TComponent*>(iter.get()) != nullptr) {
                found = true;
                iter.swap(mComponents[mComponents.size() - 1]);
                break;
            }
        }

        if(found) {
            mComponents.pop_back();
            return true;
        }

        return false;
    }


}