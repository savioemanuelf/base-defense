#include "../Headers/Bar.h"

void Bar::init(sf::Vector2f positions, sf::Vector2f size, sf::Color barColor, sf::Color outlineColor, int maxValue,
               int currentValue) {
    bar.setSize(size);
    bar.setFillColor(barColor);
    bar.setOrigin(bar.getGlobalBounds().width / 2, bar.getGlobalBounds().height / 2);
    bar.setPosition(positions);

    border.setSize(size);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(2);
    border.setOutlineColor(outlineColor);
    border.setOrigin(bar.getGlobalBounds().width / 2, bar.getGlobalBounds().height / 2);
    border.setPosition(positions);

    content.setFont(resources.assets->getFont(Fonts::arial));
    content.setCharacterSize(border.getGlobalBounds().height / 2);
    content.setFillColor(outlineColor);
    content.setString(std::to_string(currentValue) + '/' + std::to_string(maxValue));
    content.setOrigin(content.getLocalBounds().width / 2, content.getLocalBounds().height / 2);
    content.setPosition(border.getPosition().x, border.getPosition().y - content.getGlobalBounds().height / 2);
}

void Bar::render() {
    resources.window->draw(bar);
    resources.window->draw(border);
    resources.window->draw(content);
}