#pragma once

#include "Dino.h"
#include "DinoType.h"
#include "TextureLoader.h"
#include "Utils.h"

class Dino
{
private:
    sf::Sprite cardSprite;
    sf::Font font;
    sf::Text nameText;
    sf::Text HPText;
    sf::Texture texture;
    sf::Texture attackTexture;
    sf::Texture cardTexture;
    sf::Color originalColor;
    sf::Clock damageClock;
    sf::Clock attackClock;
    bool isDamaged;
    bool isAttacking;

    void organizeText(sf::Text& text, std::string textString, sf::Vector2f position);

    std::string getDinoName(DinoType type);

    void update();

protected:
    int STR = 30;
    int DEX = 15;
    int INT = 10;

public:
    int HP = 100;
    int attackDamage = 10;
    int cost = 0;
    DinoType type;
    sf::Sprite sprite;
    sf::Sprite attackSprite;
    bool isSelected = false;
    bool isDead = false;

    bool ProcessDamage(int damage);

    Dino(DinoType type);

    void draw(sf::RenderWindow& window, sf::Vector2f position);

    void draw(sf::RenderWindow& window, sf::Vector2f position, bool drawCard, bool invert, float scaleMultiplier);

    void triggerAttack();

    void deathAnimation();

    virtual ~Dino() {}

    virtual int damage(Terrain terrain) = 0;
};


class DinoStr : public Dino {
public:
    DinoStr(DinoType type) : Dino(type) {}
    int damage(Terrain terrain) override;
};

class DinoDex : public Dino
{
public:
    DinoDex(DinoType type) : Dino(type) {}
    int damage(Terrain terrain) override;
};

class DinoInt : public Dino
{
public:
    DinoInt(DinoType type) : Dino(type) {}
    int damage(Terrain terrain) override;
};