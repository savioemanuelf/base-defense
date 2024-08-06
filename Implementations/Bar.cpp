#include "../Headers/Bar.h"

#include <SFML/Graphics.hpp>

#include <iostream>

Bar::Bar() : maxContent(100), currentContent(100) {
    // Construtor padrão vazio
}

Bar::Bar(sf::Vector2f positions, sf::Vector2f size, sf::Color backgroundColor, sf::Color color, sf::Color outlineColor, int thickness, int currentContent, int maxContent) {

    this->bar.setSize(size);
    this->bar.setFillColor(color);
    this->bar.setPosition(positions.x, positions.y);  

    // outline da barra de status, implementada para o player ter noção de quantidade
    this->outlineBar.setSize(size);
    this->outlineBar.setFillColor(backgroundColor);
    this->outlineBar.setOutlineThickness(thickness);
    this->outlineBar.setOutlineColor(outlineColor);
    this->outlineBar.setPosition(positions);

    this->setMaxContent(maxContent);
    this->setCurrentContent(maxContent);

    if (!font.loadFromFile("Assets/Fonts/arial.ttf")) {
        std::cerr << "Erro ao carregar a fonte" << std::endl;
    } else {
        textContent.setFont(font);
        textContent.setCharacterSize(14);
        textContent.setFillColor(sf::Color::White);
        textContent.setOutlineThickness(1);
        textContent.setString(std::to_string(this->getCurrentContent()) + "/" + std::to_string(this->getMaxContent()));
        sf::FloatRect textRect = textContent.getLocalBounds();
        textContent.setOrigin(textRect.width / 2, textRect.height / 2);
        textContent.setPosition(
            (positions.x + size.x / 2), 
            (positions.y + size.y / 2 - textRect.height /4) + 1);  // centraliza o texto dentro da barra com +1 por causa da outline do texto
    }
}

Bar::~Bar() {
    // destrutor vazio
}

void Bar::showBar(sf::RenderWindow& window) {
    window.draw(this->outlineBar);
    window.draw(this->bar);
    window.draw(this->getTextContent());
}

void Bar::updateBar(int currentContent, sf::Color color) {
    // ajusta a barra com base no conteúdo atual
    this->currentContent = currentContent;
    float x = (currentContent / static_cast<float>(this->maxContent)) * this->outlineBar.getSize().x;
    float y = this->bar.getSize().y;
    this->bar.setSize(sf::Vector2f(x, y));

    this->bar.setFillColor(color); 

    if(currentContent == 0) {
        this->outlineBar.setOutlineColor(color);
        this->textContent.setFillColor(color);
    } 

    textContent.setString(std::to_string(currentContent) + "/" + std::to_string(this->getMaxContent()));
}
