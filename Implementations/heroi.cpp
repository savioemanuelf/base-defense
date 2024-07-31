#include "../Headers/Heroi.h"

#include <iostream>

Heroi::Heroi() : HP(100), Municao(50) {
    if (!texture.loadFromFile("Assets/Texture/personagem.png")) {
        std::cerr << "Erro ao carregar a imagem" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(400, 300);   // Centro da janela
    sprite.setScale(0.08f, 0.08f);  // Escala dependendo do tomanaho da imagem
}

void Heroi::andar(sf::Vector2f direction) {  // Direção x e y
    sprite.move(direction);
}

void Heroi::atirar(std::vector<Projectile>& projectiles,sf::Texture& projectileTexture, sf::Vector2f target) {
    if (Municao > 0) {
        Municao--;
        sf::Vector2f position = sprite.getPosition();
        sf::Vector2f direction = target - position;
        projectiles.emplace_back(projectileTexture, position, direction);
    }
}

void Heroi::dano_tomado(int dano) {
    HP -= dano;
    if (HP < 0) {
        HP = 0;
        // Morte do Herói:
    }
}

void Heroi::draw(sf::RenderWindow& window) { window.draw(sprite); }

int Heroi::getHP() const { return HP; }

int Heroi::getMunicao() const { return Municao; }

sf::Vector2f Heroi::getPosition() const { return sprite.getPosition(); }
