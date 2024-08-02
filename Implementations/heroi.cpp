#include "../Headers/Heroi.h"
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

Heroi::Heroi() : HP(100), Municao(50) {
    if (!texture.loadFromFile("Assets/Texture/personagem.png")) {
        std::cerr << "Erro ao carregar a imagem" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(400, 300);   // Centro da janela
    sprite.setScale(0.3f, 0.3f);  // Escala dependendo do tomanaho da imagem

    sf::FloatRect bounds = sprite.getGlobalBounds();
    sprite.setOrigin(bounds.width / 2, bounds.height / 2);  // Origem no centro da imagem

    if (!font.loadFromFile("Assets/arial.ttf")) { // Local da fonte
        std::cerr << "Erro ao carregar a fonte" << std::endl;
    }
    
    hpText.setFont(font);
    hpText.setCharacterSize(12);
    hpText.setFillColor(sf::Color::Red);
    ammoText.setFont(font);
    ammoText.setCharacterSize(12);
    ammoText.setFillColor(sf::Color::White);
    hpText.setPosition(10, 10);
    ammoText.setPosition(10, 30);
}

void Heroi::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    hpText.setString("HP: " + std::to_string(HP)); //Atualizar sempre na tela
    ammoText.setString("Ammo: " + std::to_string(Municao)); //Atualizar sempre na tela
    window.draw(hpText);
    window.draw(ammoText);
}

void Heroi::andar(sf::Vector2f direction) {  // Direção x e y
    sprite.move(direction);
    rotate(direction);
}

void Heroi::atirar(std::vector<Projectile>& projectiles, sf::Texture& projectileTexture, sf::Vector2f target) {
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
    }
}

void Heroi::rotate(sf::Vector2f direction) {
    float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159265; //Calcula com base na tangente e gira o herói
    float currentAngle = sprite.getRotation(); //Pega a rotação atual
    float deltaAngle = angle - currentAngle;

    if(deltaAngle > 180.0f) {
        deltaAngle -= 360.0f;
    } else if(deltaAngle < -180.0f) {
        deltaAngle += 360.0f;
    }


    float rotationSpeed = 0.2f; //Velocidade da rotação
    if(std::abs(deltaAngle) > rotationSpeed) {
        if(deltaAngle > 0){
            sprite.setRotation(currentAngle + rotationSpeed);
        }
        else{
            sprite.setRotation(currentAngle - rotationSpeed);
        }
    }else{
        sprite.setRotation(angle); //Rotação final
    }
}

int Heroi::getHP() const { return HP; }

int Heroi::getMunicao() const { return Municao; }

sf::Vector2f Heroi::getPosition() const { return sprite.getPosition(); }
