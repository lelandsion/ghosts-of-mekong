//
// Created by Leland Sion on 2024-10-15.
//

#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class MainMenu {
public:
    MainMenu();
    ~MainMenu();

    // Core methods
    void render(sf::RenderWindow& window);   // Render the main menu to the window
    void handleInput(sf::RenderWindow& window);  // Handle input from the user

    // Menu logic
    void moveUp();      // Navigate up the menu
    void moveDown();    // Navigate down the menu
    int getSelectedOption() const;  // Get the currently selected menu option

private:
    // Menu options
    int selectedOptionIndex;  // Tracks the current selected menu option
    sf::Font font;            // Font used for menu text
    sf::Text menuOptions[3];  // Array of text for the menu options (e.g., "Start", "Exit")

    // Background
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    // Constants for menu options
    const int totalOptions = 3;  // Example: 3 options (Start, Options, Exit)
};

#endif // MAINMENU_H
