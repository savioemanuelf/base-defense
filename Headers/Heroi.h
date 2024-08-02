#ifndef HEROI_H
#define HEROI_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Projectile.h"

class Heroi {
   private:
    int HP;
    int Municao;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text hpText;
    sf::Text ammoText;
    float currentAngle;
    void rotate(sf::Vector2f direction);
    
   public:
    Heroi();
    void andar(sf::Vector2f direction);
    void atirar(std::vector<Projectile>& projectiles, sf::Texture& projectileTexture, sf::Vector2f target);
    void dano_tomado(int dano);
    void draw(sf::RenderWindow& window);
    

    int getHP() const;
    int getMunicao() const;
    sf::Vector2f getPosition() const;
};
#endif