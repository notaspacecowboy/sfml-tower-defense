//
// Created by Zheng Yang on 19/10/22.
//

#include <States/StateMachine.h>
#include <assert.h>

namespace game::states {
    StateMachine::StateMachine() {
    }

    void StateMachine::pop() {
        mActiveStates.pop_back();
    }

    void StateMachine::clear() {
        mActiveStates.clear();
    }

    bool StateMachine::isEmpty() const {
        return mActiveStates.empty();
    }

    State* StateMachine::peak() const {
        if(mActiveStates.size() == 0)
            return nullptr;
        return mActiveStates[mActiveStates.size() - 1].get();
    }
}

