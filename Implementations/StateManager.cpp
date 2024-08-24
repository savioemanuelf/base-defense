#include "../Headers/StateManager.h"

void StateManager::changeState(std::unique_ptr<State> state) {
    if (!states.empty()) {
        states.pop();
    }
    states.push(std::move(state));
}

std::unique_ptr<State>& StateManager::getState() { return states.top(); }