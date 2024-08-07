#ifndef HEROI_H
#define HEROI_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include "Projectile.h"

class Heroi {
   private:
    // Attributes
    int HP;
    int Municao;
    float speed;
    sf::Vector2f targetPosition;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text hpText;
    sf::Text ammoText;
    float currentAngle;
    void playFireballSound();
    sf::SoundBuffer fireBallBuffer;
    std::vector<sf::Sound> fireBallSounds;
    

   public:
    // Constructor
    Heroi(sf::Font font);
    // Functions
    void andar(const sf::Vector2f& direction);
    void atirar(std::vector<Projectile>& projectiles, sf::Texture& projectileTexture, sf::Vector2f target);
    void dano_tomado(int dano);
    void draw(sf::RenderWindow& window);
    void rotate(const sf::Vector2f& targetPosition);
    // Getters
    int getHP() const;
    int getMunicao() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getTargetPosition();
    // Setters
    void setTargetPosition(sf::Vector2f target);
};
#endif