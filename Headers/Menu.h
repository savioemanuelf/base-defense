#ifndef MENU_H
#define MENU_H

#include "State.h"

class Menu : public State {
   private:
    // components
    sf::Text title, play, settings, exit;
    sf::Color primary, secondary;
    sf::Sprite background;
    // attributes
    StateType next;
    int outlineSize;

   public:
    // constructor
    Menu(GameContext& resources) : State(resources), next(StateType::Menu) { init(); }
    ~Menu() override {}
    // functions
    void init() override;
    void handleEvents(sf::Event& event) override;
    void update(float dt) override;
    void render() override;
    void resize();
    // getters
    virtual StateType getType() { return StateType::Menu; }
    virtual StateType nextState() { return next; }
};

#endif