#ifndef ASSETS_MANAGER_H
#define ASSETS_MANAGER_H

#include <string.h>

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

class AssetsManager {
   private:
    std::map<int, std::unique_ptr<sf::Font>> fonts;
    std::map<int, std::unique_ptr<sf::Cursor>> cursors;
    std::map<int, std::unique_ptr<sf::Texture>> heroTextures;
    std::map<int, std::unique_ptr<sf::Texture>> projectilesTexture;

   public:
    AssetsManager() {}
    void addFont(int id, std::string fileName);
    void addCursor(int id, std::string fileName);
    void addHeroTexture(int id, std::string fileName);
    void addProjectileTexture(int id, std::string fileName);

    sf::Font& getFont(int id);
    sf::Cursor& getCursor(int id);
    sf::Texture& getHeroTexture(int id);
    sf::Texture& getProjectileTexture(int id);
};

#endif