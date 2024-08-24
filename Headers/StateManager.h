#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <memory>
#include <stack>

#include "State.h"

class StateManager {
   private:
    // attributes
    std::stack<std::unique_ptr<State>> states;

   public:
    // constructor
    StateManager() {}
    // getters
    std::unique_ptr<State>& getState();
    // setters
    void changeState(std::unique_ptr<State> state);
};

#endif