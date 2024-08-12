#ifndef GAME_H
#define GAME_H

#include "Hero.h"
#include "State.h"

class Game : public State {
   private:
    StateType next;
    Hero player;

   public:
    Game(GameContext& resources) : State(resources), next(StateType::Game), player(resources) { init(); }
    void init() override;
    void handleEvents(sf::Event& event) override;
    void update(float dt) override;
    void render() override;
    virtual StateType getType() { return StateType::Game; }
    virtual StateType nextState() { return next; }
};

#endif