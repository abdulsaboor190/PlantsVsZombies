#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>

using namespace sf;
using namespace std;

class Zombies
{
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual void setTexture(const sf::Texture& texture) = 0;
    virtual void moveZombie(float& x, float& y, int* lives) = 0;
};

class FootballZombie : public Zombies
{
    float position_X;
    float position_Y;
    sf::Sprite sprite;
    float movementSpeed;
    bool direction = true;
public:
    FootballZombie() : position_X(100), position_Y(100), movementSpeed(1) {}
    void setPosition(float x, float y)
    {
        position_X = x;
        position_Y = y;
    }

    void setTexture(const sf::Texture& texture)
    {
        sprite.setTexture(texture);
    }

    void draw(sf::RenderWindow& window) override
    {

        sprite.setPosition(position_X, position_Y);
        window.draw(sprite);
    }

    void moveZombie(float& x, float& y, int* lives) override
    {
        if (x > 500 || y >= 400)
        {
            x -= movementSpeed;
            if (x == 0)
                *lives -= 1;
        }

        else if (x <= 500 && y < 400)
        {
            y += movementSpeed;
            if (x == 0)
                *lives -= 1;
        }
    }
};

class BlackZombie : public Zombies
{
    float position_X;
    float position_Y;
    sf::Sprite sprite;
    float movementSpeed;
public:
    BlackZombie() : position_X(100), position_Y(100), movementSpeed(2) {}
    void setPosition(float x, float y)
    {
        position_X = x;
        position_Y = y;
    }

    void setTexture(const sf::Texture& texture)
    {
        sprite.setTexture(texture);
    }

    void draw(sf::RenderWindow& window) override
    {

        sprite.setPosition(position_X, position_Y);
        window.draw(sprite);
    }

    void moveZombie(float& x, float& y, int* lives) override
    {
        if (x > 700 || y >= 450)
        {
            x -= movementSpeed;
            if (x == 0)
                *lives -= 1;
        }

        else if (x <= 700 && y < 450)
        {
            y += movementSpeed;
            x -= movementSpeed;
            if (x == 0)
                *lives -= 1;
        }
    }
};

class SimpleZombie : public Zombies
{
    float position_X;
    float position_Y;
    sf::Sprite sprite;
    float movementSpeed;
public:
    SimpleZombie() : position_X(100), position_Y(100), movementSpeed(0.5) {}
    void setPosition(float x, float y)
    {
        position_X = x;
        position_Y = y;
    }

    void setTexture(const sf::Texture& texture)
    {
        sprite.setTexture(texture);
    }

    void draw(sf::RenderWindow& window) override
    {

        sprite.setPosition(position_X, position_Y);
        window.draw(sprite);
    }

    void moveZombie(float& x, float& y, int* lives) override
    {
        x -= movementSpeed;
        if (x == 0)
            *lives -= 1;
    }
};

class ZombieFactory
{
protected:
    Zombies* myZombies;
public:
    virtual void createSimpleZombies(RenderWindow& window, int* lives) = 0;
    virtual void createFootballZombies(RenderWindow& window, int* lives) = 0;
    virtual void createBlackZombies(RenderWindow& window, int* lives) = 0;
};


class zombieFactory : public ZombieFactory
{
private:
    Texture simpleZombieTexture;
    Texture footballZombieTexture;
    Texture blackZombieTexture;
    SimpleZombie Szombie1;
    SimpleZombie Szombie2;
    SimpleZombie Szombie3;
    SimpleZombie  Szombie4;
    SimpleZombie  Szombie5;
    FootballZombie Fzombie1;
    FootballZombie Fzombie2;
    FootballZombie Fzombie3;
    FootballZombie Fzombie4;
    FootballZombie Fzombie5;
    BlackZombie Bzombie1;
    BlackZombie Bzombie2;
    BlackZombie Bzombie3;
    BlackZombie Bzombie4;
    BlackZombie Bzombie5;
    float X1 = 1150;
    float X2 = 1150;
    float X3 = 1150;
    float X4 = 1150;
    float X5 = 1150;
    float Y1;
    float Y2;
    float Y3;
    float Y4;
    float Y5;

    Clock spawnTimer;

public:

    zombieFactory()
    {
        srand(time(0));
        Y1 = (rand() % 400) + 100;
        Y2 = (rand() % 400) + 100;
        Y3 = (rand() % 400) + 100;
        Y4 = (rand() % 400) + 100;
        Y5 = (rand() % 400) + 100;
        myZombies = NULL;
        if (!simpleZombieTexture.loadFromFile("Images/7.png"))
        {
            std::cerr << "Failed to load simple zombie image" << std::endl;
        }
        if (!footballZombieTexture.loadFromFile("Images/6.png"))
        {
            std::cerr << "Failed to load football zombie image" << std::endl;
        }
        if (!blackZombieTexture.loadFromFile("Images/Mr_Black.png"))
        {
            std::cerr << "Failed to load black zombie image" << std::endl;
        }

    }

    void createSimpleZombies(RenderWindow& window, int* lives) override
    {
        Szombie1.setPosition(X1, Y1);
        Szombie2.setPosition(X2, Y2);
        Szombie3.setPosition(X3, Y3);
        Szombie4.setPosition(X4, Y4);
        Szombie5.setPosition(X5, Y5);

        Szombie1.setTexture(simpleZombieTexture);
        Szombie2.setTexture(simpleZombieTexture);
        Szombie3.setTexture(simpleZombieTexture);
        Szombie4.setTexture(simpleZombieTexture);
        Szombie5.setTexture(simpleZombieTexture);

        if (spawnTimer.getElapsedTime().asSeconds() >= 0.0f)
        {
            Szombie1.draw(window);
            Szombie1.moveZombie(X1, Y1, lives);
            Szombie1.draw(window);
        }

        if (spawnTimer.getElapsedTime().asSeconds() >= 10.0f)
        {
            Szombie2.draw(window);
            Szombie2.moveZombie(X2, Y2, lives);
            Szombie2.draw(window);
        }

        if (spawnTimer.getElapsedTime().asSeconds() >= 20.0f)
        {
            Szombie3.draw(window);
            Szombie3.moveZombie(X3, Y3, lives);
            Szombie3.draw(window);
        }

        if (spawnTimer.getElapsedTime().asSeconds() >= 30.0f)
        {
            Szombie4.draw(window);
            Szombie4.moveZombie(X4, Y4, lives);
            Szombie4.draw(window);
        }

        if (spawnTimer.getElapsedTime().asSeconds() >= 40.0f)
        {
            Szombie5.draw(window);
            Szombie5.moveZombie(X5, Y5, lives);
            Szombie5.draw(window);
        }
    }

    void createFootballZombies(RenderWindow& window, int* lives) override
    {
        Fzombie1.setPosition(X1, Y1);
        Fzombie2.setPosition(X2, Y2);
        Fzombie3.setPosition(X3, Y3);
        Fzombie4.setPosition(X4, Y4);
        Fzombie5.setPosition(X5, Y5);

        Fzombie1.setTexture(footballZombieTexture);
        Fzombie2.setTexture(footballZombieTexture);
        Fzombie3.setTexture(footballZombieTexture);
        Fzombie4.setTexture(footballZombieTexture);
        Fzombie5.setTexture(footballZombieTexture);

        if (spawnTimer.getElapsedTime().asSeconds() >= 0.0f)
        {
            Fzombie1.draw(window);
            Fzombie1.moveZombie(X1, Y1, lives);
            Fzombie1.draw(window);
        }

        if (spawnTimer.getElapsedTime().asSeconds() >= 8.0f)
        {
            Fzombie2.draw(window);
            Fzombie2.moveZombie(X2, Y2, lives);
            Fzombie2.draw(window);
        }

        if (spawnTimer.getElapsedTime().asSeconds() >= 16.0f)
        {
            Fzombie3.draw(window);
            Fzombie3.moveZombie(X3, Y3, lives);
            Fzombie3.draw(window);
        }

        if (spawnTimer.getElapsedTime().asSeconds() >= 24.0f)
        {
            Fzombie4.draw(window);
            Fzombie4.moveZombie(X4, Y4, lives);
            Fzombie4.draw(window);
        }

        if (spawnTimer.getElapsedTime().asSeconds() >= 32.0f)
        {
            Fzombie5.draw(window);
            Fzombie5.moveZombie(X5, Y5, lives);
            Fzombie5.draw(window);
        }

    }

    void createBlackZombies(RenderWindow& window, int* lives) override
    {
        Bzombie1.setPosition(X1, Y1);
        Bzombie2.setPosition(X2, Y2);
        Bzombie3.setPosition(X3, Y3);
        Bzombie4.setPosition(X4, Y4);
        Bzombie5.setPosition(X5, Y5);

        Bzombie1.setTexture(blackZombieTexture);
        Bzombie2.setTexture(blackZombieTexture);
        Bzombie3.setTexture(blackZombieTexture);
        Bzombie4.setTexture(blackZombieTexture);
        Bzombie5.setTexture(blackZombieTexture);


        if (spawnTimer.getElapsedTime().asSeconds() >= 0.0f)
        {
            Bzombie1.draw(window);
            Bzombie1.moveZombie(X1, Y1, lives);
            Bzombie1.draw(window);
        }

        if (spawnTimer.getElapsedTime().asSeconds() >= 7.0f)
        {
            Bzombie2.draw(window);
            Bzombie2.moveZombie(X2, Y2, lives);
            Bzombie2.draw(window);
        }

        if (spawnTimer.getElapsedTime().asSeconds() >= 14.0f)
        {
            Bzombie3.draw(window);
            Bzombie3.moveZombie(X3, Y3, lives);
            Bzombie3.draw(window);
        }

        if (spawnTimer.getElapsedTime().asSeconds() >= 21.0f)
        {
            Bzombie4.draw(window);
            Bzombie4.moveZombie(X4, Y4, lives);
            Bzombie4.draw(window);
        }

        if (spawnTimer.getElapsedTime().asSeconds() >= 28.0f)
        {
            Bzombie5.draw(window);
            Bzombie5.moveZombie(X5, Y5, lives);
            Bzombie5.draw(window);
        }
    }
};