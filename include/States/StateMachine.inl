namespace game::states {

    template<class TState, typename... Args>
    TState *StateMachine::push(Args&& ...args) {
        std::unique_ptr<State> state(new TState(this, args...));
        auto ptr = state.get();
        mActiveStates.emplace_back(std::move(state));
        ptr->init();
        return dynamic_cast<TState*>(ptr);
    }

}