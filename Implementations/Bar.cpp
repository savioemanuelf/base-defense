#include "../Headers/Bar.h"

#include <iostream>

void Bar::init(sf::Vector2f positions, sf::Vector2f size, sf::Color barColor, sf::Color outlineColor, int maxValue,
               int currentValue) {
    // bar settings
    bar.setSize(size);
    bar.setFillColor(barColor);
    bar.setOrigin(bar.getGlobalBounds().width / 2, bar.getGlobalBounds().height / 2);
    bar.setPosition(positions);

    // border settings
    border.setSize(size);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(2);
    border.setOutlineColor(outlineColor);
    border.setOrigin(bar.getGlobalBounds().width / 2, bar.getGlobalBounds().height / 2);
    border.setPosition(positions);

    // bar content settings
    content.setFont(resources.assets->getFont(Fonts::arial));
    content.setCharacterSize(border.getGlobalBounds().height / 2);
    content.setFillColor(outlineColor);
    content.setString(std::to_string(currentValue) + '/' + std::to_string(maxValue));
    content.setOrigin(content.getLocalBounds().width / 2, content.getLocalBounds().height / 2);
    content.setPosition(border.getPosition().x, border.getPosition().y - content.getGlobalBounds().height / 2);

    // assign values
    maxContentValue = maxValue;
    currentContentValue = currentValue;
}

void Bar::render() {
    resources.window->draw(bar);
    resources.window->draw(border);
    resources.window->draw(content);
}

void Bar::setContent(int value) {
    // resize bar to equal content value
    currentContentValue = value;

    float x = border.getSize().x * (currentContentValue / static_cast<float>(maxContentValue));
    float y = bar.getSize().y;

    bar.setSize(sf::Vector2f(x, y));
    content.setString(std::to_string(currentContentValue) + "/" + std::to_string(maxContentValue));
}