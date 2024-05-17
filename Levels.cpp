#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>

using namespace sf;
using namespace std;

class Levels
{
public:
    virtual void drawBackground(RenderWindow& window) = 0;
    virtual void drawplants(RenderWindow& window, Event& event) = 0;
    virtual void drawZombies(RenderWindow& window, Event& event, int* lives) = 0;
};

class BeginnersGarden : public Levels
{
private:
    ZombieFactory* myzombies;
    PlantFactory* myplants;
public:
    BeginnersGarden()
    {
        myplants = new plantFactory;
        myzombies = new zombieFactory;
    }

    void drawBackground(RenderWindow& window) override
    {
        Texture backgroundTexture;
        backgroundTexture.loadFromFile("Images/2.jpeg");
        Sprite backgroundSprite(backgroundTexture);
        window.draw(backgroundSprite);
    }

    void drawplants(RenderWindow& window, Event& event) override
    {
        myplants->createIcons(window);
    }

    void drawZombies(RenderWindow& window, Event& event, int* lives) override
    {
        myzombies->createSimpleZombies(window, lives);
    }

};



class ZombieOutskirts : public Levels
{
private:
    ZombieFactory* myzombies;
    PlantFactory* myplants;


public:
    ZombieOutskirts()
    {
        myplants = new plantFactory;
        myzombies = new zombieFactory;
    }

    void drawBackground(RenderWindow& window) override
    {
        Texture backgroundTexture;
        backgroundTexture.loadFromFile("Images/l1.jpg");
        Sprite backgroundSprite(backgroundTexture);
        window.draw(backgroundSprite);
    }

    void drawplants(RenderWindow& window, Event& event) override
    {
        myplants->createIcons(window);
    }

    void drawZombies(RenderWindow& window, Event& event, int* lives) override
    {
        myzombies->createFootballZombies(window, lives);
    }

};

class SunflowerFields : public Levels
{
private:

    ZombieFactory* myzombies;
    PlantFactory* myplants;
public:

    SunflowerFields() {

        myplants = new plantFactory;
        myzombies = new zombieFactory;

    }

    void drawBackground(RenderWindow& window) override
    {
        Texture backgroundTexture;
        backgroundTexture.loadFromFile("Images/l2.jpg");
        Sprite backgroundSprite(backgroundTexture);
        window.draw(backgroundSprite);
    }

    void drawplants(RenderWindow& window, Event& event) override
    {
        myplants->createIcons(window);
    }

    void drawZombies(RenderWindow& window, Event& event, int* lives) override
    {
        myzombies->createBlackZombies(window, lives);
    }

};