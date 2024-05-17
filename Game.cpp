/*

Muhammad Aqib Qureshi
23i-0654
CS-B

Abdul Saboor
23i-3039
CS-B

*/


#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>

using namespace sf;
using namespace std; 

class Menu
{
private:
    Texture menuTexture;
    Sprite menuSprite;

public:
    Menu(const string& menuFilePath)
    {
        if (!menuTexture.loadFromFile(menuFilePath))
        {
            cerr << "Failed to load menu image" << endl;
        }
        menuSprite.setTexture(menuTexture);
    }

    void display(RenderWindow& window)
    {
        window.draw(menuSprite);
    }
};

class Game
{
    RenderWindow window;
    Levels* currentLevel;
    Peashooter* originalPeashooter;  // Original Peashooter shown for selection
    Sunflower* originalSunflower;    // Original Sunflower shown for selection
    SnowPeashooter* originalSnowPeashooter;  // Original SnowPeashooter shown for selection
    Potato* originalPotato;          // Original Potato shown for selection
    Peashooter* placedPeashooters[100];
    Sunflower* placedSunflowers[100];
    SnowPeashooter* placedSnowPeashooters[100];
    Potato* placedPotatoes[100];     // Array to store placed potatoes
    int placedPeashootersCount;
    int placedSunflowersCount;
    int placedSnowPeashootersCount;
    int placedPotatoesCount;         // Counter for placed potatoes
    bool isPeashooterSelected;
    bool isSunflowerSelected;
    bool isSnowPeashooterSelected;
    bool isPotatoSelected;           // Selection flag for Potato
    Menu* gameMenu;
    bool inMenu = true;;
    int score;
    bool isPaused; //used to check whether the game is paused or not
    Texture pauseScreenTexture;
    Texture backgroundPauseTexture;
    int lives = 3;
public:
    int currency; // Variable to hold the currency value
private:
    Font font; // Font for the currency text
    Text currencyText; // Text object to display the currency
    Font game_over;
    Text game_over_Text;



    Event event; // Declare event object outside of the functions

    void render(float deltaTime)
    {
        window.clear();

        if (inMenu) {
            gameMenu->display(window);
        }
        else {
            // Draw the background and zombies from the current level
            currentLevel->drawBackground(window);
            if (lives && !inMenu)
            {
                if (!isPaused && !inMenu)
                {
                    currentLevel->drawZombies(window, event, &lives);
                    currencyText.setString(std::to_string(currency) + " SUNS");
                    window.draw(currencyText);

                    // Draw and update original plant models that are used for selection
                    if (originalPeashooter) {
                        originalPeashooter->update(deltaTime);
                        originalPeashooter->draw(window);
                    }
                    if (originalSunflower) {
                        originalSunflower->draw(window);
                    }
                    if (originalSnowPeashooter) {
                        originalSnowPeashooter->draw(window);
                    }
                    if (originalPotato) {
                        originalPotato->draw(window);
                    }

                    // Update and draw placed peashooters (includes shooting peas)
                    for (int i = 0; i < placedPeashootersCount; i++) {
                        placedPeashooters[i]->update(deltaTime);
                        placedPeashooters[i]->draw(window);
                    }

                    // Draw placed sunflowers
                    for (int i = 0; i < placedSunflowersCount; i++) {
                        placedSunflowers[i]->update(deltaTime);
                        placedSunflowers[i]->draw(window);
                    }

                    for (int i = 0; i < placedSnowPeashootersCount; i++) {
                        placedSnowPeashooters[i]->update(deltaTime);
                        placedSnowPeashooters[i]->draw(window);
                    }

                    // Draw placed potatoes
                    for (int i = 0; i < placedPotatoesCount; i++) {
                        placedPotatoes[i]->draw(window);
                    }
                }
                else
                {
                    if (!pauseScreenTexture.loadFromFile("Images/play.png")) {
                        std::cerr << "Error loading pause screen texture!" << std::endl;
                    }


                    Sprite pauseScreenSprite;
                    pauseScreenSprite.setTexture(pauseScreenTexture);
                    pauseScreenSprite.setPosition(290, 160);
                    window.draw(pauseScreenSprite);
                }
            }
            else
            {
                if (!game_over.loadFromFile("Images/arial.ttf"))
                {
                    std::cerr << "Failed to load font" << std::endl;
                }
                game_over_Text.setFont(font);
                game_over_Text.setCharacterSize(150);
                game_over_Text.setFillColor(sf::Color(204, 255, 136));
                game_over_Text.setStyle(sf::Text::Bold); // Make the text bold
                game_over_Text.setPosition(160, 210);
                game_over_Text.setString("GAME OVER!");
                window.draw(game_over_Text);

            }

        }
        window.display();
    }




    void handleEvents() {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed) {
                if (inMenu) {
                    // Handle menu-specific mouse clicks
                    handleMenuMousePress(event.mouseButton.x, event.mouseButton.y);
                }
                else {
                    // Handle game-specific mouse clicks
                    handleGameMousePress(event.mouseButton.x, event.mouseButton.y);
                }
            }
            else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) && inMenu == false)
            {
                isPaused = !isPaused; // Toggle pause state
            }

        }
    }



    void handleMenuMousePress(int x, int y) {
        // Check if the user clicked in the area to start BeginnersGarden
        if (x >= 100 && x <= 300 && y >= 20 && y <= 300) {
            inMenu = false;
        }
        // Check if the user clicked in the area to start ZombieOutskirts
        else if (x >= 350 && x <= 490 && y >= 20 && y <= 300) {
            // Transition to the second level
            currentLevel = new ZombieOutskirts();
            inMenu = false;
        }
        else if (x >= 500 && x <= 700 && y >= 20 && y <= 300) {
            // Transition to the third level
            currentLevel = new SunflowerFields();
            inMenu = false;
        }
    }

    void handleGameMousePress(int x, int y) {
        // Handle game-specific mouse clicks
        handleMousePress(x, y);
    }


    void handleMousePress(int x, int y) {
        // Coordinates for selection areas of Peashooter, Sunflower, and SnowPeashooter
        bool clickOnPeashooter = (x >= 50 && x <= 150 && y >= 100 && y <= 180);
        bool clickOnSunflower = (x >= 50 && x <= 150 && y >= 190 && y <= 270);
        bool clickOnSnowPeashooter = (x >= 50 && x <= 150 && y >= 280 && y <= 360);
        bool clickOnPotato = (x >= 50 && x <= 150 && y >= 370 && y <= 450);


        if (clickOnPeashooter) {
            isPeashooterSelected = true;
            isSunflowerSelected = isSnowPeashooterSelected = isPotatoSelected = false;  // Deselect others
        }
        else if (clickOnSunflower) {
            isSunflowerSelected = true;
            isPeashooterSelected = isSnowPeashooterSelected = isPotatoSelected = false;  // Deselect others
        }
        else if (clickOnSnowPeashooter) {
            isSnowPeashooterSelected = true;
            isPeashooterSelected = isSunflowerSelected = isPotatoSelected = false;  // Deselect others
        }
        else if (clickOnPotato) {
            isPotatoSelected = true;
            isPeashooterSelected = isSnowPeashooterSelected = isSunflowerSelected = false;


        }

        else if (isPeashooterSelected || isSunflowerSelected || isSnowPeashooterSelected || isPotatoSelected) {
            // Place the selected plant at the click location

            if (isPeashooterSelected && placedPeashootersCount < 100 && currency >= 100)
            {

                placedPeashooters[placedPeashootersCount++] = new Peashooter("Images/c1.png", x, y);
                isPeashooterSelected = false; // Deselect after placing
                currency -= 100;
            }
            else if (isSunflowerSelected && placedSunflowersCount < 100 && currency >= 50) {

                placedSunflowers[placedSunflowersCount++] = new Sunflower("Images/c2.png", x, y, 0, 0, &currency);
                isSunflowerSelected = false; // Deselect after placing
                currency -= 50;
            }
            else if (isSnowPeashooterSelected && placedSnowPeashootersCount < 100 && currency >= 175) {

                placedSnowPeashooters[placedSnowPeashootersCount++] = new SnowPeashooter("Images/c3.png", x, y);  // Use an appropriate texture
                isSnowPeashooterSelected = false;  // Deselect after placing
                currency -= 175;
            }
            else if (isPotatoSelected && placedPotatoesCount < 100 && currency >= 50) {

                placedPotatoes[placedPotatoesCount++] = new Potato("Images/c4.png", x, y);
                isPotatoSelected = false;
                currency -= 50;

            }
        }
    }



public:
    Game() : isPaused(false), window(VideoMode(1200, 700), "Plant Placement Game"),
        placedPeashootersCount(0), placedSunflowersCount(0),
        placedSnowPeashootersCount(0), placedPotatoesCount(0),
        isPeashooterSelected(false), isSunflowerSelected(false),
        isSnowPeashooterSelected(false), isPotatoSelected(false), currency(150) {
        originalPeashooter = new Peashooter("Images/a1.png", 50, 100);
        originalSunflower = new Sunflower("Images/a4.png", 50, 170, 0, 0, &currency);
        originalSnowPeashooter = new SnowPeashooter("Images/a3.png", 50, 260);
        originalPotato = new Potato("Images/a5.png", 50, 340); // Path adjusted for potato
        currentLevel = new BeginnersGarden(); // Initialize with a default level
        gameMenu = new Menu("Images/menu.png");
        score = 0;
        if (!font.loadFromFile("Images/arial.ttf"))
        {
            std::cerr << "Failed to load font" << std::endl;
        }
        currencyText.setFont(font);
        currencyText.setCharacterSize(24);
        currencyText.setFillColor(sf::Color::White);
        currencyText.setStyle(sf::Text::Bold); // Make the text bold
        currencyText.setPosition(1050, 10);
    }

    ~Game() {
        delete originalPeashooter;
        delete originalSunflower;
        delete originalSnowPeashooter;
        delete originalPotato;
        delete currentLevel;
        delete gameMenu;
        for (int i = 0; i < placedPeashootersCount; i++) {
            delete placedPeashooters[i];
        }
        for (int i = 0; i < placedSunflowersCount; i++) {
            delete placedSunflowers[i];
        }
        for (int i = 0; i < placedSnowPeashootersCount; i++) {
            delete placedSnowPeashooters[i];
        }
        for (int i = 0; i < placedPotatoesCount; i++) {
            delete placedPotatoes[i];
        }
    }
    void run() {
        sf::Clock clock;
        while (window.isOpen()) {
            float deltaTime = clock.restart().asSeconds();
            handleEvents();
            render(deltaTime);
        }
    }
};