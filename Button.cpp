#include "Button.h"


Button::Button(int x, int y, int width, int height, sf::Font& font, std::string buttonText, const sf::Texture& texture) 
{
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(x, y));
    sprite.setScale(
        static_cast<float>(width) / texture.getSize().x,
        static_cast<float>(height) / texture.getSize().y
    );

    text.setFont(font);
    text.setString(buttonText);
    text.setCharacterSize(36);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1.0f);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(x + width / 2.0f, y + height / 2.0f);
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(text);
}

bool Button::isMouseOver(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f buttonPos = sprite.getPosition();
    sf::Vector2f buttonSize = sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

    return (mousePos.x >= buttonPos.x && mousePos.x <= buttonPos.x + buttonSize.x &&
        mousePos.y >= buttonPos.y && mousePos.y <= buttonPos.y + buttonSize.y);
}