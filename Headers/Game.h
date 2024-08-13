#ifndef GAME_H
#define GAME_H

#include "Enemy.h"
#include "Hero.h"
#include "Projectile.h"
#include "State.h"

class Game : public State {
   private:
    StateType next;
    Hero player;
    std::vector<std::unique_ptr<Projectile>> heroProjectiles;
    std::vector<std::unique_ptr<Enemy>> enemies;
    sf::Clock enemySpawnClock;

   public:
    Game(GameContext& resources) : State(resources), next(StateType::Game), player(resources) { init(); }
    ~Game() override {}
    void init() override;
    void handleEvents(sf::Event& event) override;
    void update(float dt) override;
    void render() override;
    virtual StateType getType() { return StateType::Game; }
    virtual StateType nextState() { return next; }
};

#endif