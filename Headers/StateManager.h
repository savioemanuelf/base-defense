#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <memory>
#include <stack>

#include "State.h"

class StateManager {
   private:
    std::stack<std::unique_ptr<State>> states;

   public:
    StateManager() {}
    void changeState(std::unique_ptr<State> state);
    std::unique_ptr<State>& getState();
};

#endif