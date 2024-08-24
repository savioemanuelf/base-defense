#ifndef SETTINGS_H
#define SETTINGS_H

#include "State.h"

class Settings : public State {
   private:
    // components
    sf::Text fullscreen, heroType, difficulty, back;
    sf::Color primary, secondary;
    // attributes
    int outlineSize;
    StateType next;

   public:
    // constructor
    Settings(GameContext& resources) : State(resources), next(StateType::Settings) { init(); }
    // destructor
    ~Settings() override {}
    // functions
    void init() override;
    void handleEvents(sf::Event& event) override;
    void update(float dt) override;
    void render() override;
    void resize();
    // getters
    virtual StateType getType() { return StateType::Settings; }
    virtual StateType nextState() { return next; }
};

#endif