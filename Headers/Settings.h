#ifndef SETTINGS_H
#define SETTINGS_H

#include "State.h"

class Settings : public State {
   private:
    sf::Text fullscreen, heroType, back;
    sf::Color primary, secondary;
    int outlineSize;

    StateType next;

   public:
    Settings(GameContext& resources) : State(resources), next(StateType::Settings) { init(); }
    void init() override;
    void handleEvents(sf::Event& event) override;
    void update(float dt) override;
    void render() override;
    virtual StateType getType() { return StateType::Settings; }
    virtual StateType nextState() { return next; }
    void resize();
};

#endif