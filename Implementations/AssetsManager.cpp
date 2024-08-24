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
        texture->setSmooth(true);
        heroTextures[id] = std::move(texture);
    }
}

void AssetsManager::addProjectileTexture(int id, std::string fileName) {
    auto texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile("Assets/Texture/Projectiles/" + fileName)) {
        texture->setSmooth(true);
        projectilesTexture[id] = std::move(texture);
    }
}

void AssetsManager::addEnemyTexture(int id, std::string fileName) {
    auto texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile("Assets/Texture/Enemies/" + fileName)) {
        texture->setSmooth(true);
        enemyTextures[id] = std::move(texture);
    }
}

void AssetsManager::addBackgroundTexture(int id, std::string fileName) {
    auto texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile("Assets/Texture/Backgrounds/" + fileName)) {
        texture->setSmooth(true);
        backgroundTexture[id] = std::move(texture);
    }
}

void AssetsManager::addDropTexture(int id, std::string fileName) {
    auto texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile("Assets/Texture/Drops/" + fileName)) {
        texture->setSmooth(true);
        dropTexture[id] = std::move(texture);
    }
}

void AssetsManager::addBaseTexture(int id, std::string fileName) {
    auto texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile("Assets/Texture/Base/" + fileName)) {
        texture->setSmooth(true);
        baseTexture[id] = std::move(texture);
    }
}

void AssetsManager::addBarTexture(int id, std::string fileName) {
    auto texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile("Assets/Texture/Bar/" + fileName)) {
        texture->setSmooth(true);
        barTexture[id] = std::move(texture);
    }
}

sf::Font& AssetsManager::getFont(int id) { return *(fonts.at(id).get()); }

sf::Cursor& AssetsManager::getCursor(int id) { return *(cursors.at(id).get()); }

sf::Texture& AssetsManager::getHeroTexture(int id) { return *(heroTextures.at(id).get()); }

sf::Texture& AssetsManager::getProjectileTexture(int id) { return *(projectilesTexture.at(id).get()); }

sf::Texture& AssetsManager::getEnemyTexture(int id) { return *(enemyTextures.at(id).get()); }

sf::Texture& AssetsManager::getBackgroundTexture(int id) { return *(backgroundTexture.at(id).get()); }

sf::Texture& AssetsManager::getDropTexture(int id) { return *(dropTexture.at(id).get()); }

sf::Texture& AssetsManager::getBaseTexture(int id) { return *(baseTexture.at(id).get()); }

sf::Texture& AssetsManager::getBarTexture(int id) { return *(barTexture.at(id).get()); }
