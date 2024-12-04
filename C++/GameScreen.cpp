#include "GameScreen.h"

void GameScreen::update(sf::Event event) {
    switch (event.type) {
    case sf::Event::MouseButtonPressed:
        handleMousePressed(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
        break;
    case sf::Event::MouseButtonReleased:
        handleMouseReleased(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
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

GameScreen::GameScreen(sf::RenderWindow* mainWindow) {
    selectedPiece = nullptr;
    isDragging = false;
    window = mainWindow;
    if (!window)
        throw 505;
    //board.push_back(new Rook(0, 0));
}

GameScreen::~GameScreen() {
    for (auto piece : board) {
        delete piece;
    }
}

void GameScreen::handleMousePressed(const sf::Vector2f& mousePos) {
    if (selectedPiece)
        return;

    for (auto piece : board) {
        if (piece->color == currentColor
            && piece->col == mousePos.x / 100
            && piece->row == mousePos.y / 100) {
            selectedPiece = piece;
            break;
        }
    }
}

void GameScreen::handleMouseReleased(const sf::Vector2f& mousePos) {
    if (!selectedPiece)
        return;

    if (selectedPiece->isValidMove(selectedPiece->getPosition())) {
        selectedPiece->setPosition(sf::Vector2f(
            static_cast<int>(mousePos.x / 100) * 100, static_cast<int>(mousePos.y / 100) * 100
        ));
    }
    else {
        selectedPiece->setPosition(sf::Vector2f(
            selectedPiece->col * 100, selectedPiece->row * 100
        ));
    }
    isDragging = false;
    selectedPiece = nullptr;
}

void GameScreen::handleMouseMoved(const sf::Vector2f& mousePos) {
    if (!selectedPiece)
        return;

    isDragging = true;
    sf::Vector2f newPosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
    selectedPiece->setPosition(newPosition);
}

void GameScreen::draw() {
    for (auto piece : board) {
        piece->draw(*window);
    }
}