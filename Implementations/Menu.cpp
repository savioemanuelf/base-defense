#include "../Headers/Menu.h"

#include <iostream>

void Menu::initMenu() {
    sf::Color primaryColor(166, 166, 166);
    sf::Color secondaryColor(sf::Color::White);

    int outlineSize = 2;
    int windowWidth = sf::VideoMode::getDesktopMode().width;

    this->visible = true;

    this->title.setFont(font);
    this->title.setString("Base Defense");
    this->title.setCharacterSize(100);
    this->title.setOutlineThickness(outlineSize);
    this->title.setFillColor(primaryColor);
    this->title.setOutlineColor(secondaryColor);
    this->title.setPosition((windowWidth - this->title.getGlobalBounds().width) / 2, 50);

    this->play.setFont(font);
    this->play.setString("Jogar");
    this->play.setCharacterSize(60);
    this->play.setOutlineThickness(outlineSize);
    this->play.setFillColor(primaryColor);
    this->play.setOutlineColor(secondaryColor);
    this->play.setPosition((windowWidth - this->play.getGlobalBounds().width) / 2, 300);

    this->exit.setFont(font);
    this->exit.setString("Sair");
    this->exit.setCharacterSize(60);
    this->exit.setOutlineThickness(outlineSize);
    this->exit.setFillColor(primaryColor);
    this->exit.setOutlineColor(secondaryColor);
    this->exit.setPosition((windowWidth - this->exit.getGlobalBounds().width) / 2, 450);
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(this->title);
    window.draw(this->play);
    window.draw(this->exit);
}

Menu::Menu(sf::Font font) {
    this->font = font;
    this->initMenu();
}

bool Menu::isVisible() { return visible; }

sf::FloatRect Menu::getPlayBounds() { return this->play.getGlobalBounds(); }

sf::FloatRect Menu::getExitBounds() { return this->exit.getGlobalBounds(); }

void Menu::setInvisible() { this->visible = false; }
