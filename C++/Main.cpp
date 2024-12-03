#include <SFML/Graphics.hpp>
#include "GameScreen.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess");

    GameScreen gameScreen;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            gameScreen.update(event);
        }

        window.clear();
        gameScreen.draw(window);
        window.display();
    }

    return 0;
}