#include <SFML/Graphics.hpp>

class Menu {
   private:
    // Attributes
    sf::Text title, play, exit;
    sf::Font font;
    bool visible;
    // Functions
    void initMenu();

   public:
    // Constructor
    Menu(sf::Font font);
    // Functions
    void draw(sf::RenderWindow& window);
    bool isVisible();
    sf::FloatRect getPlayBounds();
    sf::FloatRect getExitBounds();
    void setInvisible();
};