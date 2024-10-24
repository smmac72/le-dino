#pragma once
#include "Dino.h"
#include "Player.h"
#include "DinoType.h"
#include "Button.h"
#include "Shop.h"
#include "Utils.h"

class Fight
{
private:
    Player& player;
    Player& enemy;

    sf::RenderWindow& window;
    GameState& gameState;

    sf::Vector2f gridPosition;
    sf::Vector2f gridSize;
    sf::Vector2f cardSize;
    sf::Vector2f cardSpacing;
    int cardsPerRow;

    void ReceiveReward(int reward);
    void BattleResults(bool playerWon, int prize);

public:
    Fight(Player& p1, Player& p2, sf::RenderWindow& window, GameState& gameState);

    void ShowOwnedDinos();
    void SelectDinos();
    void DrawDinos();

    void FightLoop();
};
