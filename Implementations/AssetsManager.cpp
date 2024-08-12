#include "../Headers/AssetsManager.h"

#include <iostream>

void AssetsManager::addFont(int id, std::string fileName) {
    auto font = std::make_unique<sf::Font>();

    if (font->loadFromFile("Assets/Fonts/" + fileName)) {
        fonts[id] = std::move(font);
    }
}

void AssetsManager::addCursor(int id, std::string fileName) {
    auto cursor = std::make_unique<sf::Cursor>();

    if (fileName == "hand") {
        if (cursor->loadFromSystem(sf::Cursor::Hand)) {
            cursors[id] = std::move(cursor);
        }
    }
}

void AssetsManager::addHeroTexture(int id, std::string fileName) {
    auto texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile("Assets/Texture/Heroes/" + fileName)) {
        heroTextures[id] = std::move(texture);
    }
}

sf::Font& AssetsManager::getFont(int id) { return *(fonts.at(id).get()); }

sf::Cursor& AssetsManager::getCursor(int id) { return *(cursors.at(id).get()); }

sf::Texture& AssetsManager::getHeroTexture(int id) { return *(heroTextures.at(id).get()); }
