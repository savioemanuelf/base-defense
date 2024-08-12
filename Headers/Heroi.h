#ifndef HEROI_H
#define HEROI_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include "../Headers/Bar.h"
#include "../Headers/Projectile.h"

class Heroi {
   private:
    // Attributes
    int HP;
    int Municao;
    float speed;
    Bar* healthBar;
    Bar* ammoBar;
    sf::Vector2f targetPosition;
    sf::Texture texture;
    sf::Sprite sprite;
    float currentAngle;
    void playFireballSound();
    sf::SoundBuffer fireBallBuffer;
    std::vector<sf::Sound> fireBallSounds;
    

   public:
    // Constructor
    Heroi(sf::Font font);

    // Destructor
    ~Heroi();
    // Functions
    void initializeHealthBar(sf::Window& window);
    void initializeAmmoBar(sf::Window& window);
    void andar(const sf::Vector2f& direction);
    void atirar(std::vector<Projectile>& projectiles, sf::Texture& projectileTexture, sf::Vector2f target);
    void dano_tomado(std::vector<Projectile>& projectiles);
    void draw(sf::RenderWindow& window);
    void rotate(const sf::Vector2f& targetPosition);
    // Getters
    int getHP() const;
    int getMunicao() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getTargetPosition();
    sf::Sprite getSprite();
    Bar getBarHealth(){return *this->healthBar;}
    Bar getBarAmmo(){return *this->ammoBar;}
    // Setters
    void setTargetPosition(sf::Vector2f target);
    void setMunicao(int municao);
    void setHP(int life);
    void setHealthBar(Bar barH){*this->healthBar = barH;}
    void setAmmoBar(Bar barM){*this->ammoBar = barM;}
};
#endif