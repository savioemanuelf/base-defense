#ifndef BAR_H
#define BAR_H

#include <SFML/Graphics.hpp>

class Bar {
   private:
    // Attributes
    sf::Font font;
    sf::Text textContent;

    int maxContent;
    int currentContent;

    sf::RectangleShape bar;
    sf::RectangleShape outlineBar;

   public:
    // Constructor
    Bar();
    Bar(sf::Vector2f positions, sf::Vector2f size, sf::Color backgroundColor, sf::Color color, sf::Color outlineColor,
        int thickness, int currentContent, int maxContent);
    // Destructor
    ~Bar();
    // Functions
    void showBar(sf::RenderWindow& window);
    void updateBar(int currentContent);
    // Getters
    sf::Text getTextContent() { return this->textContent; }
    sf::RectangleShape getBar() { return this->bar; }
    sf::RectangleShape getOutlineBar() { return this->outlineBar; }
    int getMaxContent() { return this->maxContent; }
    int getCurrentContent() { return this->currentContent; }
    // Setters
    void setTextContent(sf::Text content) { this->textContent = content; }
    void setBar(sf::RectangleShape newbar) { this->bar = newbar; }
    void setOutlineBar(sf::RectangleShape outline) { this->outlineBar = outline; }
    void setMaxContent(int newContent) { this->maxContent = newContent; }
    void setCurrentContent(int newContent) { this->currentContent = newContent; }
};
#endif  // BAR_H