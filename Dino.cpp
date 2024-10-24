#pragma once

#include "Dino.h"
#include <random>

void Dino::organizeText(sf::Text& text, std::string textString, sf::Vector2f position)
{
    text.setFont(font);
    text.setString(textString);
    text.setCharacterSize(24);
    text.setPosition(position);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2.f);
}

std::string Dino::getDinoName(DinoType type)
{
    switch (type)
    {
    case Tyrannosaur:
        return "Tyrannosaur";
    case Brachiosaurus:
        return "Brachiosaurus";
    case Triceratops:
        return "Triceratops";
    }
}

void Dino::update()
{
    if (isDamaged && damageClock.getElapsedTime().asSeconds() > 1)
    {
        sprite.setColor(originalColor);
        isDamaged = false;
    }
    if (isAttacking && attackClock.getElapsedTime().asSeconds() <= 1)
    {
        sprite.setTexture(attackTexture);
    }
    else
    {
        sprite.setTexture(texture);
        isAttacking = false;
    }
    if (isDead)
        deathAnimation();
}
bool Dino::ProcessDamage(int damage)
{
    HP -= damage;
    isDamaged = true;
    damageClock.restart();
    sprite.setColor(sf::Color::Red);

    if (HP <= 0)
    {
        HP = 0;
        return true;
    }
    return false;
}

Dino::Dino(DinoType type) : type(type)
{
    STR = rand() % 20 + 10;
    DEX = rand() % 20 + 10;
    INT = rand() % 20 + 10;

    font.loadFromFile("Assets/ComicSans.ttf");

    switch (type)
    {
    case DinoType::Triceratops:
        texture = TextureLoader::getInstance().getTexture("Assets/DinoImg/TRIC.png");
        attackTexture.loadFromFile("Assets/DinoImg/TRIC_A.png");
        cost = 200;
        HP = 135;
        break;
    case DinoType::Tyrannosaur:
        texture = TextureLoader::getInstance().getTexture("Assets/DinoImg/TREX.png");
        attackTexture.loadFromFile("Assets/DinoImg/TREX_A.png");
        cost = 150;
        HP = 110;
        break;
    case DinoType::Brachiosaurus:
        texture = TextureLoader::getInstance().getTexture("Assets/DinoImg/BRA.png");
        attackTexture.loadFromFile("Assets/DinoImg/BRA_A.png");
        cost = 100;
        HP = 100;
        break;
    }

    cardTexture = TextureLoader::getInstance().getTexture("Assets/Card.png");
    cardSprite.setTexture(cardTexture);
    cardSprite.setScale(1.0f, 1.1f);
    cardSprite.setPosition(0, 30);

    sprite.setTexture(texture);
    sprite.setScale(0.5f, 0.5f);
    sprite.setPosition(0, 40);

    attackSprite.setTexture(attackTexture);
    attackSprite.setScale(0.5f, 0.5f);
    attackSprite.setPosition(0, 40);

    isDamaged = false;
    isAttacking = false;
    originalColor = sprite.getColor();
}

void Dino::draw(sf::RenderWindow& window, sf::Vector2f position)
{
    organizeText(nameText, getDinoName(type), sf::Vector2f(0, 40));
    organizeText(HPText, std::to_string(HP) + " HP", sf::Vector2f(0, 25));

    cardSprite.setPosition(position);
    sprite.setPosition(position.x + 20, position.y + 65);
    sprite.setScale(0.5f, 0.5f);
    nameText.setPosition(sf::Vector2f(position.x + 40, position.y + 25));
    HPText.setPosition(sf::Vector2f(position.x + 40, position.y + 45));

    update();

    window.draw(cardSprite);
    window.draw(sprite);
    window.draw(nameText);
    window.draw(HPText);
}

void Dino::draw(sf::RenderWindow& window, sf::Vector2f position, bool drawCard, bool invert, float scaleMultiplier)
{
    organizeText(nameText, getDinoName(type), sf::Vector2f(0, 0));
    organizeText(HPText, std::to_string(HP) + " HP", sf::Vector2f(0, 25));

    cardSprite.setPosition(position);
    sprite.setPosition(invert ? position.x + 90 : position.x, position.y + 45);
    sprite.setScale(invert ? -0.5f : 0.5f, 0.5f);
    sprite.setScale(sprite.getScale() * scaleMultiplier);

    nameText.setPosition(position);
    HPText.setPosition(sf::Vector2f(position.x, position.y + 25));

    update();

    if (drawCard)
        window.draw(cardSprite);
    window.draw(sprite);
    if (scaleMultiplier > 1.0f)
    {
        window.draw(nameText);
        window.draw(HPText);
    }
}

void Dino::triggerAttack()
{
    isAttacking = true;
    attackClock.restart();
}

void Dino::deathAnimation()
{
    sprite.setColor(sf::Color::Color(0, 0, 0, 220));
}

int DinoStr::damage(Terrain terrain)
{
    attackDamage = STR;
    if (terrain == Plain)
        attackDamage *= 2;
    return attackDamage;
}

int DinoDex::damage(Terrain terrain)
{
    attackDamage = DEX;
    if (terrain == River)
        attackDamage *= 2;
    return attackDamage;
}
int DinoInt::damage(Terrain terrain)
{
    attackDamage = INT;
    if (terrain == Mountain)
        attackDamage *= 2;
    return attackDamage;
}