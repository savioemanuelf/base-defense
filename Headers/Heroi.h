#ifndef HEROI_H
#define HEROI_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "../Headers/Projectile.h"

class Heroi {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    int HP;
    int Municao;
    float speed;
    bool dead = false;

    // Barras de Vida e Mana
    sf::Texture Borda;
    sf::Sprite spriteBorda;
    sf::Texture vida;
    sf::Sprite spritevida;
    
    sf::Texture BordaMana;
    sf::Sprite spriteBordaMana;
    sf::Texture Mana;
    sf::Sprite spriteMana; //Sprite da barra de mana

    // Sons
    sf::SoundBuffer fireBallBuffer;
    std::vector<sf::Sound> fireBallSounds;

    sf::Vector2f targetPosition;

    

public:
    Heroi(sf::Font font);
    ~Heroi();
    void desenharBarras(sf::RenderWindow& window); 
    void atualizarSpriteBarras();
    void draw(sf::RenderWindow& window);    // Desenhar o herói e suas barras
    void andar(const sf::Vector2f& direction);
    void rotate(const sf::Vector2f& targetPosition);
    void atirar(std::vector<Projectile>& projectiles, sf::Texture& projectileTexture, sf::Vector2f target);
    void dano_tomado(std::vector<Projectile>& projectiles);
    void heroRegen(int regen);
    void restoreAmmo(int ammo);
    void playFireballSound();

    // Getters e Setters
    int getHP() const;
    int getMunicao() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getTargetPosition();
    sf::Sprite getSprite();
    void setTargetPosition(sf::Vector2f target);
    void setMunicao(int municao);
    void setHP(int life);
    bool isDead() const { return dead; }
    void setDead(bool status) { dead = status; }
};

#endif
