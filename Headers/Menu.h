#ifndef MENU_H
#define MENU_H

#include "State.h"

class Menu : public State {
   private:
    // Text Attributes
    sf::Text title, play, settings, exit;
    sf::Color primary, secondary;
    int outlineSize;
    // Next State Selected
    StateType next;

   public:
    // Constructor
    Menu(GameContext& resources) : State(resources), next(StateType::Menu) { init(); }
    ~Menu() override {}
    // Virtual Methods
    void init() override;
    void handleEvents(sf::Event& event) override;
    void update(float dt) override;
    void render() override;
    virtual StateType getType() { return StateType::Menu; }
    virtual StateType nextState() { return next; }
    // Funcions
    void resize();
};

#endif