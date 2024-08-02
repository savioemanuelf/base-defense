#ifndef BAR_H
#define BAR_H

#include <SFML/Graphics.hpp>

class Bar {
    private:
        sf::Font font;
        sf::Text textContent;

        int maxContent;
        int currentContent;

        sf::RectangleShape bar;
        sf::RectangleShape outlineBar; // outlinebar implementada para o player ter melhor noção de quantidade

    public:
        // CONSTRUCTOR AND DESTRUCTOR
        Bar();
        Bar(sf::Vector2f positions, sf::Vector2f size, sf::Color backgroundColor, sf::Color color, sf::Color outlineColor, int thickness, int currentContent, int maxContent);
        ~Bar();

        void showBar(sf::RenderWindow& window);
        void updateBar(int currentContent);
        
        // GETTERS AND SETTERS

        sf::Text getTextContent() { return this->textContent;}
        void setTextContent(sf::Text content) { this->textContent = content;}

        sf::RectangleShape getBar() { return this-> bar;}
        void setBar(sf::RectangleShape newbar) { this->bar = newbar;} 

        sf::RectangleShape getOutlineBar() { return this->outlineBar;}
        void setOutlineBar(sf::RectangleShape outline) { this->outlineBar = outline;} 

        int getMaxContent() { return this->maxContent;}
        void setMaxContent(int newContent) { this->maxContent = newContent;}

        int getCurrentContent() { return this->currentContent;}
        void setCurrentContent(int newContent) { this->currentContent = newContent;}

    
};
#endif // BAR_H