#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>

using namespace sf;
using namespace std;

class Plants
{
protected:
    int health;
    int cost;

public:
    Plants(int h, int c) : health(h), cost(c) {}

    virtual void setPosition(float x, float y) = 0;
    virtual void setTexture(const sf::Texture& texture) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};


class Pea {
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    bool active;  // To track if the pea is active and should be moved or drawn

public:
    Pea() : speed(150.0f), active(false) {}

    void activate(float x, float y) {
        if (!texture.loadFromFile("Images/pea.png")) {
            std::cerr << "Failed to load pea image" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
        active = true;
    }

    void update(float deltaTime) {
        if (active) {
            sprite.move(speed * deltaTime, 0); // Move right
            if (sprite.getPosition().x > 1200) { // Assuming screen width is 1200
                active = false;  // Deactivate if off screen
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        if (active) {
            window.draw(sprite);
        }
    }

    bool isActive() const {
        return active;
    }
};




class Peashooter : public Plants
{
    sf::Sprite sprite;
    sf::Texture texture;

    Pea peas[40];  // Array of peas, assuming a max of 10 active peas at a time
    float shootTimer;
    const float shootInterval = 5.0f; // 8 seconds interval

public:
    // Default constructor
    Peashooter() : Plants(0, 0) {}

    // Constructor with parameters for texture and position
    Peashooter(const std::string& textureFile, float x, float y, int h = 0, int c = 0) : Plants(h, c)
    {
        if (!texture.loadFromFile(textureFile)) {
            cerr << "Failed to load peashooter image" << endl;
        }
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
        shootTimer = shootInterval;
    }

    void setPosition(float x, float y) override {
        sprite.setPosition(x, y);
    }

    void setTexture(const sf::Texture& texture) override {
        sprite.setTexture(texture);
    }

    void update(float deltaTime) {
        // Shooting logic
        if ((shootTimer -= deltaTime) <= 0) {
            for (int i = 0; i < 40; i++) {
                if (!peas[i].isActive()) {
                    peas[i].activate(sprite.getPosition().x + sprite.getGlobalBounds().width,
                        sprite.getPosition().y + sprite.getGlobalBounds().height / 2);
                    break;
                }
            }
            shootTimer = shootInterval;
        }

        // Update each active pea
        for (int i = 0; i < 40; i++) {
            peas[i].update(deltaTime);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
        for (int i = 0; i < 40; i++) {
            peas[i].draw(window);
        }
    }

    Vector2f getPosition() const {
        return sprite.getPosition();
    }
};



class Sun {
    sf::Sprite sprite;
    sf::Texture texture;
    bool active;
    float timer;

public:
    Sun() : active(false), timer(0) {}

    void activate(float x, float y) {
        if (!texture.loadFromFile("Images/sun.png")) {
            std::cerr << "Failed to load sun image" << std::endl;
        }
        active = true;
        sprite.setTexture(texture);
        sprite.setPosition(x, y + 20); // Position the sun slightly above the sunflower
        timer = 10.0f; // Resets the timer for the next sun generation
    }

    void update(float deltaTime) {
        if (active) {
            timer -= deltaTime;
            if (timer <= 8) {
                active = false; // Automatically deactivate after 10 seconds if not clicked
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        if (active) {
            window.draw(sprite);
        }
    }

    bool contains(float x, float y) {
        return sprite.getGlobalBounds().contains(x, y);
    }

    bool isActive() const {
        return active;
    }

    void deactivate() {
        active = false;
    }
};




class Sunflower : public Plants {
    sf::Sprite sprite;
    sf::Texture texture;
    Sun sun; // Each sunflower has one sun at a time
    int* currencyPtr;  // Pointer to the currency in the Game class
    float generateSunTimer;  // Timer for generating suns

public:
    // Default constructor

    Sunflower() : Plants(0, 0), generateSunTimer(10.0f), currencyPtr(NULL) {}

    Sunflower(const std::string& textureFile, float x, float y, int h, int c, int* Currency) : Plants(h, c), generateSunTimer(10.0f), currencyPtr(Currency) {
        if (!texture.loadFromFile(textureFile)) {
            std::cerr << "Failed to load sunflower image" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
    }

    void update(float deltaTime) {
        if (!sun.isActive())
        {
            if ((generateSunTimer -= deltaTime) <= 0) {

                generateSunTimer = 10.0f; // Reset timer for next sun generation
                sun.activate(sprite.getPosition().x, sprite.getPosition().y);
                // Increment the currency value by 10 when a sun is generated
                *currencyPtr += 10;

            }
        }
        else
        {
            sun.update(deltaTime);
        }
    }



    void setPosition(float x, float y) override {
        sprite.setPosition(x, y);
    }

    void setTexture(const sf::Texture& texture) override {
        sprite.setTexture(texture);
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(sprite);
        sun.draw(window);
    }

    Vector2f getPosition() const {
        return sprite.getPosition();
    }

    bool checkSunClicked(float x, float y) {
        if (sun.contains(x, y) && sun.isActive()) {
            sun.deactivate();
            return true;
        }
        return false;
    }
};


class Cherry : public Plants
{
private:
    float position_X;
    float position_Y;
    sf::Sprite sprite;

public:
    Cherry(int h = 0, int c = 0)
        : Plants(h, c), position_X(0.0f), position_Y(0.0f)
    {
        // Additional initialization if needed
    }

    void setPosition(float x, float y) override
    {
        position_X = x;
        position_Y = y;
    }

    void setTexture(const sf::Texture& texture) override
    {
        sprite.setTexture(texture);
    }

    void draw(sf::RenderWindow& window) override
    {
        sprite.setPosition(position_X, position_Y);  // Set sprite position
        window.draw(sprite);  // Draw the sprite on the window
    }
};

class Potato : public Plants {
    sf::Sprite sprite;
    sf::Texture texture;

public:
    // Default constructor initializes with default health and cost (optional if not needed)
    Potato() : Plants(0, 0) {}


    // Constructor for setting texture and position
    Potato(const std::string& textureFile, float x, float y, int h = 0, int c = 0) : Plants(h, c) {
        if (!texture.loadFromFile(textureFile)) {
            cerr << "Failed to load potato mine image from " << textureFile << endl;
        }
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
    }

    void setPosition(float x, float y) override
    {
        sprite.setPosition(x, y);
    }

    void setTexture(const sf::Texture& newTexture) override
    {
        texture = newTexture;
        sprite.setTexture(texture);
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(sprite);
    }

    Vector2f getPosition() const {
        return sprite.getPosition();
    }
};

class SnowPea {
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    bool active;

public:
    SnowPea() : speed(150.0f), active(false) {}

    void activate(float x, float y) {
        if (!texture.loadFromFile("Images/snowpea.png")) {
            std::cerr << "Failed to load snow pea image" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
        active = true;
    }

    void update(float deltaTime) {
        if (active) {
            sprite.move(speed * deltaTime, 0); // Move right
            if (sprite.getPosition().x > 1200) { // Assuming screen width is 1200
                active = false;  // Deactivate if off screen
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        if (active) {
            window.draw(sprite);
        }
    }

    bool isActive() const {
        return active;
    }
};



class SnowPeashooter : public Plants {
    sf::Sprite sprite;
    sf::Texture texture;
    SnowPea snowPeas[10]; // Array of snow peas
    float shootTimer;
    const float shootInterval = 8.0f; // 8 seconds interval

public:
    // Default constructor initializes with default health and cost (optional if not needed)
    SnowPeashooter(int h = 0, int c = 0) : Plants(h, c) {}

    SnowPeashooter(const std::string& textureFile, float x, float y, int h = 0, int c = 0) : Plants(h, c)
    {
        if (!texture.loadFromFile(textureFile)) {
            std::cerr << "Failed to load SnowPeashooter image" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
        shootTimer = shootInterval;
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    void setTexture(const sf::Texture& newTexture) {
        texture = newTexture;
        sprite.setTexture(texture);
    }

    void update(float deltaTime) {
        if ((shootTimer -= deltaTime) <= 0) {
            for (int i = 0; i < 10; i++) {
                if (!snowPeas[i].isActive()) {
                    snowPeas[i].activate(sprite.getPosition().x + sprite.getGlobalBounds().width,
                        sprite.getPosition().y + sprite.getGlobalBounds().height / 2);
                    break;
                }
            }
            shootTimer = shootInterval;
        }

        for (int i = 0; i < 10; i++) {
            snowPeas[i].update(deltaTime);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
        for (int i = 0; i < 10; i++) {
            snowPeas[i].draw(window);
        }
    }

    Vector2f getPosition() const {
        return sprite.getPosition();
    }
};

class PlantFactory
{
protected:
    Plants* myPlants;
    Texture peashooterTexture;
    Texture sunflowerTexture;
    Texture cherryTexture;
    Texture potatoTexture;
    Texture snowPeashooterTexture;
public:
    virtual void createIcons(sf::RenderWindow& window) = 0;
};

class plantFactory : public PlantFactory
{
public:
    void createIcons(sf::RenderWindow& window)
    {
        /*Load peashooter texture*/
        if (!peashooterTexture.loadFromFile("Images/a1.png")) {
            cerr << "Failed to load peashooter image" << endl;
        }
        // Load sunflower texture
        if (!sunflowerTexture.loadFromFile("Images/a4.png")) {
            cerr << "Failed to load sunflower image" << endl;
        }
        // Load cherry texture
        if (!cherryTexture.loadFromFile("Images/a2.png")) {
            cerr << "Failed to load cherry image" << endl;
        }
        // Load potato texture
        if (!potatoTexture.loadFromFile("Images/a5.png")) {
            cerr << "Failed to load potato image" << endl;
        }
        // Load snowPeashooter texture
        if (!snowPeashooterTexture.loadFromFile("Images/a3.png")) {
            cerr << "Failed to load snow_peashooter image" << endl;
        }


        myPlants = new Peashooter;
        myPlants->setPosition(50, 100);
        myPlants->setTexture(peashooterTexture);
        myPlants->draw(window);

        myPlants = new Sunflower;
        myPlants->setPosition(50, 170);
        myPlants->setTexture(sunflowerTexture);
        myPlants->draw(window);

        myPlants = new Potato;
        myPlants->setPosition(50, 310);
        myPlants->setTexture(potatoTexture);
        myPlants->draw(window);

        myPlants = new SnowPeashooter;
        myPlants->setPosition(50, 380);
        myPlants->setTexture(snowPeashooterTexture);
        myPlants->draw(window);

    }
};