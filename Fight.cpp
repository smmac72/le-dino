#include "Fight.h"

void Fight::ReceiveReward(int reward)
{
    player.balance += reward;
}

void Fight::BattleResults(bool playerWon, int prize)
{
    player.saveDinosToFile("savefile");
    gameState = BattleResult;
    ReceiveReward(prize);

    sf::Texture backgroundTexture;
    backgroundTexture = TextureLoader::getInstance().getTexture("Assets/plains.jpg");
    sf::Sprite backgroundSprite(backgroundTexture);

    sf::Font font;
    font.loadFromFile("Assets/ComicSans.ttf");

    sf::Text resultText;
    resultText.setFont(font);
    resultText.setFillColor(sf::Color::White);
    resultText.setOutlineColor(sf::Color::Black);
    resultText.setOutlineThickness(2.f);
    resultText.setCharacterSize(64);
    resultText.setString(playerWon ? "Victory!" : "Defeat!");
    resultText.setPosition(300, 300);

    sf::Text prizeText;
    prizeText.setFont(font);
    prizeText.setFillColor(sf::Color::White);
    prizeText.setOutlineColor(sf::Color::Black);
    prizeText.setOutlineThickness(2.f);
    prizeText.setCharacterSize(32);
    prizeText.setString("You won $" + std::to_string(prize));
    prizeText.setPosition(300, 200);

    sf::Texture buttonTexture;
    buttonTexture = TextureLoader::getInstance().getTexture("Assets/Button.png");
    Button backButton(500, 400, 300, 75, font, "Menu", buttonTexture);

    while (window.isOpen() && gameState == BattleResult)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos(sf::Mouse::getPosition(window));

                if (backButton.isMouseOver(window))
                {
                    gameState = InMenu;
                    return;
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(backgroundSprite);
        window.draw(resultText);
        window.draw(prizeText);
        backButton.draw(window);
        window.display();

        for (auto dino : player.dinos)
            dino->isSelected = false;
    }
}

Fight::Fight(Player& p1, Player& p2, sf::RenderWindow& window, GameState& gameState) : player(p1), enemy(p2), window(window), gameState(gameState)
{
    enemy.randomDinoPull();
    gridPosition = sf::Vector2f(50, 100);
    gridSize = sf::Vector2f(800, 600);
    cardSize = sf::Vector2f(200, 300);
    cardSpacing = sf::Vector2f(70, 10);
    cardsPerRow = 4;
}

void Fight::DrawDinos()
{
    sf::Vector2f currentPosition = gridPosition;
    int currentColumn = 0;

    for (Dino* dino : player.dinos)
    {
        if (dino->isSelected)
            continue;

        dino->draw(window, currentPosition);

        currentColumn++;
        if (currentColumn >= cardsPerRow)
        {
            currentColumn = 0;
            currentPosition.x = gridPosition.x;
            currentPosition.y += cardSize.y + cardSpacing.y;
        }
        else
            currentPosition.x += cardSize.x + cardSpacing.x;
    }
}


void Fight::SelectDinos()
{
    if (player.dinos.size() < 3)
    {
        gameState = InMenu;
        return;
    }

    sf::Texture backgroundTexture;
    backgroundTexture = TextureLoader::getInstance().getTexture("Assets/plains.jpg");
    sf::Sprite backgroundSprite(backgroundTexture);

    sf::Font font;
    font.loadFromFile("Assets/ComicSans.ttf");

    sf::Text headerText;
    headerText.setFont(font);
    headerText.setFillColor(sf::Color::White);
    headerText.setOutlineColor(sf::Color::Black);
    headerText.setOutlineThickness(2.f);
    headerText.setCharacterSize(64);
    headerText.setString("Choose 3 of your dinos");
    headerText.setPosition(50, 20);

    sf::Texture buttonTexture;
    buttonTexture = TextureLoader::getInstance().getTexture("Assets/Button.png");
    Button backButton(1050, 20, 200, 50, font, "Back", buttonTexture);

    while (window.isOpen() && player.selectedDinos.size() < 3)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos(sf::Mouse::getPosition(window));

                if (backButton.isMouseOver(window))
                {
                    gameState = InMenu;
                    return;
                }

                for (Dino* dino : player.dinos)
                {
                    if (dino->sprite.getGlobalBounds().contains(mousePos))
                    {
                        if (!dino->isSelected && player.selectedDinos.size() < 3)
                        {
                            dino->isSelected = true;
                            player.selectedDinos.push_back(dino);
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(backgroundSprite);
        window.draw(headerText);
        DrawDinos();
        backButton.draw(window);
        window.display();
    }

    if (player.selectedDinos.size() == 3)
        gameState = Battle;
}

void Fight::ShowOwnedDinos()
{
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("Assets/river.jpg");
    sf::Sprite backgroundSprite(backgroundTexture);

    sf::Font font;
    font.loadFromFile("Assets/ComicSans.ttf");

    sf::Text headerText;
    headerText.setFont(font);
    headerText.setFillColor(sf::Color::White);
    headerText.setOutlineColor(sf::Color::Black);
    headerText.setOutlineThickness(2.f);
    headerText.setCharacterSize(64);
    headerText.setString("Your Dinos:");
    headerText.setPosition(50, 20);

    sf::Texture buttonTexture;
    buttonTexture = TextureLoader::getInstance().getTexture("Assets/Button.png");
    Button backButton(1050, 20, 200, 50, font, "Back", buttonTexture);

    while (window.isOpen() && player.selectedDinos.size() < 3)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos(sf::Mouse::getPosition(window));

                if (backButton.isMouseOver(window))
                {
                    gameState = InMenu;
                    return;
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(backgroundSprite);
        window.draw(headerText);
        DrawDinos();
        backButton.draw(window);
        window.display();
    }
}


void Fight::FightLoop()
{
    Terrain terrain = static_cast<Terrain>(rand() % 3);

    sf::Texture backgroundTexture;
    switch (terrain)
    {
    case Terrain::Plain:
        backgroundTexture.loadFromFile("Assets/plains.jpg");
        break;
    case Terrain::River:
        backgroundTexture.loadFromFile("Assets/river.jpg");
        break;
    case Terrain::Mountain:
        backgroundTexture.loadFromFile("Assets/mountains.jpg");
        break;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    sf::Text headerText;
    sf::Font font;
    font.loadFromFile("Assets/ComicSans.ttf");
    headerText.setFont(font);
    headerText.setFillColor(sf::Color::White);
    headerText.setOutlineColor(sf::Color::Black);
    headerText.setOutlineThickness(2.f);
    headerText.setCharacterSize(64);

    headerText.setPosition(50, 5);

    sf::Clock attackClock;
    sf::Clock beatenAnimationClock;
    bool playerTurn = true;

    int enemyPullPrice = 0;
    for (Dino* dino : enemy.selectedDinos)
        enemyPullPrice += dino->cost;

    while (window.isOpen() && !player.selectedDinos.empty() && !enemy.selectedDinos.empty()) {
        headerText.setString(playerTurn ? "Your Turn" : "Enemy's Turn");
        window.clear(sf::Color::White);
        window.draw(backgroundSprite);
        window.draw(headerText);

        for (int i = 0; i < player.selectedDinos.size() - 1; i++) 
            player.selectedDinos[i]->draw(window, sf::Vector2f(100 + i * 150, 350), false, true, 0.7);
        for (int i = 0; i < enemy.selectedDinos.size() - 1; i++)
            enemy.selectedDinos[i]->draw(window, sf::Vector2f(900 + i * 150, 350), false, false, 0.7);

        player.selectedDinos.back()->draw(window, sf::Vector2f(450, 300), false, true, 1.35);
        enemy.selectedDinos.back()->draw(window, sf::Vector2f(750, 300), false, false, 1.35);

        if (beatenAnimationClock.getElapsedTime().asSeconds() > 1)
        {
            if (enemy.selectedDinos.back()->isDead)
                enemy.selectedDinos.pop_back();

            if (player.selectedDinos.back()->isDead)
            {
                player.deleteDino(player.selectedDinos.back());
                player.selectedDinos.pop_back();
            }
        }

        if (attackClock.getElapsedTime().asSeconds() > 2)
        {
            attackClock.restart();
            if (playerTurn)
            {
                player.attackEnemy(enemy, enemy.selectedDinos, terrain);
                if (enemy.selectedDinos.back()->isDead)
                    beatenAnimationClock.restart();
            }
            else 
            {
                enemy.attackEnemy(player, player.selectedDinos, terrain);
                if (player.selectedDinos.back()->isDead)
                    beatenAnimationClock.restart();
            }
            playerTurn = !playerTurn;
        }

        window.display();
    }
    if (player.selectedDinos.empty())
        BattleResults(false, 100);
    else if (enemy.selectedDinos.empty())
        BattleResults(true, enemyPullPrice);
}
