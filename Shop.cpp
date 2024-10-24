#include "Shop.h"

void Shop::DrawDinoCards()
{
    sf::Vector2f currentPosition = gridPosition;
    int currentColumn = 0;

    int counterToFree = 3 - player.dinos.size();
    for (auto& dino : ShopDinos)
    {
        if (dino->isSelected)
            continue;
        if (counterToFree > 0)
        {
            dino->cost = 0;
            counterToFree--;
        }

        sf::Font font;
        font.loadFromFile("Assets/ComicSans.ttf");

        sf::Text priceText;
        priceText.setFont(font);
        priceText.setCharacterSize(40);
        priceText.setFillColor(sf::Color::White);
        priceText.setStyle(sf::Text::Bold);
        priceText.setString(std::to_string(dino->cost));
        priceText.setOutlineColor(sf::Color::Black);
        priceText.setOutlineThickness(2.f);
        priceText.setPosition(currentPosition.x + cardSize.x / 2 - priceText.getLocalBounds().width / 2, currentPosition.y + cardSize.y / 2 - priceText.getLocalBounds().height / 2 + 130);

        dino->draw(window, currentPosition);
        window.draw(priceText);

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

void Shop::RemoveDinoCards()
{
    ShopDinos.clear();
}

Shop::Shop(Player& p1, sf::RenderWindow& window, GameState& gameState) : player(p1), window(window), gameState(gameState)
{
    gridPosition = sf::Vector2f(50, 100);
    gridSize = sf::Vector2f(800, 600);
    cardSize = sf::Vector2f(200, 300);
    cardSpacing = sf::Vector2f(70, 10);
    cardsPerRow = 4;
}

void Shop::ShowShop()
{
    ShopDinos.clear();
    for (int i = 0; i < 8; i++)
    {
        DinoType dinoType;
        switch (rand() % 3 + 1) 
        {
        case 1:
            dinoType = Tyrannosaur;
            break;
        case 2:
            dinoType = Brachiosaurus;
            break;
        case 3:
            dinoType = Triceratops;
            break;
        }

        switch (rand() % 3 + 1)
        {
        case 1:
            ShopDinos.push_back(std::make_unique<DinoStr>(dinoType));
            break;
        case 2:
            ShopDinos.push_back(std::make_unique<DinoDex>(dinoType));
            break;
        case 3:
            ShopDinos.push_back(std::make_unique<DinoInt>(dinoType));
            break;
        }
    }

    sf::Texture backgroundTexture;
    backgroundTexture = TextureLoader::getInstance().getTexture("Assets/mountains.jpg");
    sf::Sprite backgroundSprite(backgroundTexture);

    sf::Font font;
    font.loadFromFile("Assets/ComicSans.ttf");

    sf::Text headerText;
    headerText.setFont(font);
    headerText.setFillColor(sf::Color::White);
    headerText.setOutlineColor(sf::Color::Black);
    headerText.setOutlineThickness(2.f);
    headerText.setCharacterSize(64);
    headerText.setString("Shop:");
    headerText.setPosition(50, 20);

    sf::Text balanceText;
    balanceText.setFont(font);
    balanceText.setFillColor(sf::Color::White);
    balanceText.setOutlineColor(sf::Color::Black);
    balanceText.setOutlineThickness(2.f);
    balanceText.setCharacterSize(64);
    balanceText.setPosition(500, 20);

    sf::Texture buttonTexture;
    buttonTexture = TextureLoader::getInstance().getTexture("Assets/Button.png");
    Button backButton(1050, 20, 200, 50, font, "Back", buttonTexture);

    while (window.isOpen())
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

                for (auto& dino : ShopDinos)
                {
                    if (dino->sprite.getGlobalBounds().contains(mousePos))
                    {
                        if (!dino->isSelected && dino->cost <= player.balance)
                        {
                            dino->isSelected = true;
                            player.dinos.push_back(dino.get());
                            player.balance -= dino->cost;
                            player.saveDinosToFile("savefile");
                        }
                    }
                }
            }
        }

        balanceText.setString("Balance: $" + std::to_string(player.balance));

        window.clear(sf::Color::White);
        window.draw(backgroundSprite);
        window.draw(headerText);
        window.draw(balanceText);
        DrawDinoCards();
        backButton.draw(window);
        window.display();
    }
}