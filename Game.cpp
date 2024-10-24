#include "Game.h"

Game::Game()
{
    gameState = InMenu;
    player.loadDinosFromFile("savefile");
    window.create(sf::VideoMode(1280, 720), "le dino");

    InitFont();
    InitButtons();
    RenderMainScreen();

    Poll();
}
void Game::Poll()
{
    Shop shop(player, window, gameState);
    Fight fight(player, enemy, window, gameState);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    for (Button& button : buttons)
                    {
                        if (button.isMouseOver(window))
                        {
                            if (button.text.getString() == "Your Party")
                                gameState = Showcase;
                            else if (button.text.getString() == "Shop")
                                gameState = InShop;
                            else if (button.text.getString() == "Next Battle")
                                gameState = SelectingDinos;
                            else if (button.text.getString() == "Quit")
                                window.close();
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(backgroundSprite);
        switch (gameState)
        {
        case GameState::InMenu:
            RenderMainScreen();
            break;
        case GameState::SelectingDinos:
            fight.SelectDinos();
            break;
        case GameState::Showcase:
            fight.ShowOwnedDinos();
            break;
        case GameState::InShop:
            shop.ShowShop();
            break;
        case GameState::Battle:
            fight.FightLoop();
            player.selectedDinos.clear();
            enemy.selectedDinos.clear();
            enemy.randomDinoPull();
        }

        window.display();
    }
}
void Game::InitFont()
{
    font.loadFromFile("Assets/ComicSans.ttf");
}
void Game::InitButtons()
{
    buttonTexture = TextureLoader::getInstance().getTexture("Assets/Button.png");
    buttons.emplace_back(50, 550, 300, 75, font, "Next Battle", buttonTexture);
    buttons.emplace_back(350, 550, 300, 75, font, "Your Party", buttonTexture);
    buttons.emplace_back(650, 550, 300, 75, font, "Shop", buttonTexture);
    buttons.emplace_back(950, 550, 300, 75, font, "Quit", buttonTexture);
}
void Game::RenderMainScreen()
{
    backgroundSprite.setTexture(TextureLoader::getInstance().getTexture("Assets/plains.jpg"));

    window.draw(backgroundSprite);
    for (Button& button : buttons)
        button.draw(window);

    sf::Text titleText;
    titleText.setFont(font);
    titleText.setFillColor(sf::Color::White);
    titleText.setOutlineColor(sf::Color::Black);
    titleText.setOutlineThickness(2.f);
    titleText.setCharacterSize(64);
    titleText.setString("LE DINO GAME");
    titleText.setPosition(250, 400);
    window.draw(titleText);
}