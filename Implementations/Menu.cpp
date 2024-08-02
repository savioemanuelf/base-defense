#include "../Headers/Menu.h"

#include <iostream>

void Menu::initMenu() {
    this->visible = true;

    // Colors
    sf::Color primaryColor(166, 166, 166);
    sf::Color secondaryColor(sf::Color::White);

    // Sizes
    int outlineSize = 2;
    int windowWidth = sf::VideoMode::getDesktopMode().width;

    // Texts
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

void Menu::resize(sf::RenderWindow& window) {
    // Title Resize
    this->title.setCharacterSize(window.getSize().y / 10);
    this->title.setPosition((window.getSize().x - this->title.getGlobalBounds().width) / 2,
                            (window.getSize().y - this->title.getGlobalBounds().height) / 50);

    // Play Resize
    this->play.setCharacterSize(window.getSize().y / 16);
    this->play.setPosition((window.getSize().x - this->play.getGlobalBounds().width) / 2,
                           (window.getSize().y - this->play.getGlobalBounds().height) / 3.5f);
    // Exit Resize
    this->exit.setCharacterSize(window.getSize().y / 16);
    this->exit.setPosition((window.getSize().x - this->exit.getGlobalBounds().width) / 2,
                           (window.getSize().y - this->exit.getGlobalBounds().height) / 2.3f);
}

Menu::Menu(sf::Font font) {
    this->font = font;
    this->initMenu();
}

bool Menu::isVisible() { return visible; }

sf::FloatRect Menu::getPlayBounds() { return this->play.getGlobalBounds(); }

sf::FloatRect Menu::getExitBounds() { return this->exit.getGlobalBounds(); }

void Menu::setInvisible() { this->visible = false; }
