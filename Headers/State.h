#ifndef STATE_H
#define STATE_H

#include "GameContext.h"

enum class StateType { Menu, Settings, Game, Restart };

class State {
   protected:
    // global resources
    GameContext& resources;

   public:
    // constructor
    State(GameContext& r) : resources(r) {}
    // functions
    virtual ~State() = default;
    virtual void init() = 0;
    virtual void handleEvents(sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;
    // getters
    virtual StateType getType() = 0;
    virtual StateType nextState() = 0;
};

#endif