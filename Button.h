#pragma once
#include "SFML/Graphics.hpp"

class Button
{
private:
    sf::Sprite sprite;

public:
    sf::Text text;

    Button(int x, int y, int width, int height, sf::Font& font, std::string buttonText, const sf::Texture& texture);

    void draw(sf::RenderWindow& window);
    bool isMouseOver(sf::RenderWindow& window);
};