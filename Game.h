#pragma once

#include "Player.h"
#include "Button.h"
#include "Shop.h"
#include "Fight.h"
#include "TextureLoader.h"
#include "Utils.h"

class Game
{
public:
    Game();

    void InitFont();
    void InitButtons();
    void RenderMainScreen();
    void Poll();

private:
    sf::RenderWindow window;
    sf::Font font;
    GameState gameState;

    std::vector<Button> buttons;
    sf::Texture buttonTexture;

    sf::Sprite backgroundSprite;
    sf::Sprite foregroundSprite;

    Player player;
    Player enemy;
};
