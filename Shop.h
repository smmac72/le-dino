#pragma once

#include "Dino.h"
#include "Player.h"
#include "DinoType.h"
#include "Button.h"
#include "Utils.h"

class Shop
{
private:
    std::vector<std::unique_ptr<Dino>> ShopDinos;
    Player& player;

    sf::RenderWindow& window;

    GameState& gameState;

    sf::Vector2f gridPosition;
    sf::Vector2f gridSize;
    sf::Vector2f cardSize;
    sf::Vector2f cardSpacing;
    int cardsPerRow;

    void DrawDinoCards();

    void RemoveDinoCards();

public:
    Shop(Player& p1, sf::RenderWindow& window, GameState& gameState);

    void ShowShop();
};