#ifndef HEROI_H
#define HEROI_H
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include <vector>

class Heroi
{

private:
    int HP;
    int Municao;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    Heroi();
    void andar(sf::Vector2f direction);
    void atirar(std::vector<Projectile>& projectiles, sf::Texture& projectileTexture);
    void dano_tomado(int dano);
    void draw(sf::RenderWindow& window);

    int getHP() const;
    int getMunicao() const;
    sf::Vector2f getPosition() const;
};
#endif