#ifndef STATE_H
#define STATE_H

#include "GameContext.h"

enum class StateType { Menu, Settings, Game, Restart };

class State {
   protected:
    GameContext& resources;

   public:
    State(GameContext& r) : resources(r) {}
    virtual ~State() = default;
    virtual void init() = 0;
    virtual void handleEvents(sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;
    virtual StateType getType() = 0;
    virtual StateType nextState() = 0;
};

#endif