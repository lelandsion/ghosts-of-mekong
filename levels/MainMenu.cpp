//
// Created by Leland Sion on 2024-10-15.
//

#include "MainMenu.h"
// Constructor

MainMenu::MainMenu() {
    // Load the background texture
    if (!backgroundTexture.loadFromFile("assets/levels/menu_texture.png")) {
        // Handle error
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Load the font (make sure the font file exists in the project)
    if (!font.loadFromFile("assets/fonts/game_font.ttf")) {
        // Handle error
    }

    // Initialize the menu options (Start, Options, Exit)
    menuOptions[0].setFont(font);
    menuOptions[0].setString("Start Game");
    menuOptions[0].setFillColor(sf::Color::Red);  // Highlight the default selection
    menuOptions[0].setPosition(sf::Vector2f(400, 300));  // Example position for "Start Game"

    menuOptions[1].setFont(font);
    menuOptions[1].setString("Options");
    menuOptions[1].setFillColor(sf::Color::White);  // Non-highlighted color
    menuOptions[1].setPosition(sf::Vector2f(400, 400));  // Example position for "Options"

    menuOptions[2].setFont(font);
    menuOptions[2].setString("Exit");
    menuOptions[2].setFillColor(sf::Color::White);  // Non-highlighted color
    menuOptions[2].setPosition(sf::Vector2f(400, 500));  // Example position for "Exit"

    selectedOptionIndex = 0;  // Default selection is "Start Game"
}

// Destructor
MainMenu::~MainMenu() {
    // Any cleanup logic if necessary
}

// Render the main menu
void MainMenu::render(sf::RenderWindow& window) {
    // Draw the background
    window.draw(backgroundSprite);

    // Draw the menu options
    for (int i = 0; i < totalOptions; i++) {
        window.draw(menuOptions[i]);
    }
}

// Handle user input (keyboard navigation)
void MainMenu::handleInput(sf::RenderWindow& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        moveUp();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        moveDown();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        // Perform action based on selected option
        switch (getSelectedOption()) {
            case 0:
                // Start Game logic
                break;
            case 1:
                // Options logic (e.g., settings menu)
                break;
            case 2:
                window.close();  // Exit the game
                break;
        }
    }
}

// Move up the menu (decrease selected index)
void MainMenu::moveUp() {
    if (selectedOptionIndex - 1 >= 0) {
        menuOptions[selectedOptionIndex].setFillColor(sf::Color::White);  // Deselect current option
        selectedOptionIndex--;
        menuOptions[selectedOptionIndex].setFillColor(sf::Color::Red);    // Highlight new option
    }
}

// Move down the menu (increase selected index)
void MainMenu::moveDown() {
    if (selectedOptionIndex + 1 < totalOptions) {
        menuOptions[selectedOptionIndex].setFillColor(sf::Color::White);  // Deselect current option
        selectedOptionIndex++;
        menuOptions[selectedOptionIndex].setFillColor(sf::Color::Red);    // Highlight new option
    }
}

// Get the currently selected option
int MainMenu::getSelectedOption() const {
    return selectedOptionIndex;
}



