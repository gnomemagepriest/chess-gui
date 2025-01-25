#include <SFML/Graphics.hpp>
#include "GameScreen.h"

enum class MenuChoice {
    Restart,
    Exit
};

MenuChoice displayMenu(sf::RenderWindow& window, std::string endGameMsg);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess");

    MenuChoice choice = MenuChoice::Restart;

    while (choice != MenuChoice::Exit){
        GameScreen gameScreen(&window);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                gameScreen.update(event);
            }

            window.clear();
            gameScreen.draw();
            window.display();

            if (gameScreen.isGameOver) {
                choice = displayMenu(window, gameScreen.getEndGameMessage());
                if (choice == MenuChoice::Exit) {
                    window.close();
                }
                break;
            }
        }
    }

    return 0;
}

MenuChoice displayMenu(sf::RenderWindow& window, std::string endGameMsg) {
    sf::Font font;
    if (!font.loadFromFile("../Assets/arialmt.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    sf::Text menuText;
    menuText.setFont(font);
    menuText.setString(endGameMsg + "\nPress R to Restart or any other key to Exit");
    menuText.setCharacterSize(30);
    menuText.setFillColor(sf::Color::White);
    menuText.setPosition(200, 350);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return MenuChoice::Exit;
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R)
                    return MenuChoice::Restart;
                else
                    return MenuChoice::Exit;
            }
        }

        window.clear();
        window.draw(menuText);
        window.display();
    }

    return MenuChoice::Exit;
}