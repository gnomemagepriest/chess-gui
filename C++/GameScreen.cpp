#include "GameScreen.h"

void GameScreen::update(sf::Event event) {
    switch (event.type) {
    case sf::Event::MouseButtonPressed:
        handleMousePressed(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
        break;
    case sf::Event::MouseButtonReleased:
        handleMouseReleased();
        break;
    case sf::Event::MouseMoved:
        if (isDragging && selectedPiece) {
            handleMouseMoved(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
        }
        break;
    default:
        break;
    }
}

GameScreen::GameScreen() {
    selectedPiece = nullptr;
    isDragging = false;
    //board.push_back(new Rook(0, 0));
}

GameScreen::~GameScreen() {
    for (auto piece : board) {
        delete piece;
    }
}

void GameScreen::handleMousePressed(const sf::Vector2f& mousePos) {

}

void GameScreen::handleMouseReleased() {

}

void GameScreen::handleMouseMoved(const sf::Vector2f& mousePos) {

}

void GameScreen::draw(sf::RenderWindow& window) {
    for (auto piece : board) {
        piece->draw(window);
    }

    if (selectedPiece) {
        sf::Vector2f newPosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) - offset;
        selectedPiece->setPosition(newPosition);
        selectedPiece->draw(window);
    }
}