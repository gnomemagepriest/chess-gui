#include "GameScreen.h"
#include "Pawn.h"
#include "King.h"
#include "Knight.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include <iostream>

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
        throw 1;

    board.push_back(new Pawn(0, sf::Vector2f(0.0f,0.0f)));
    board.push_back(new Rook(0, sf::Vector2f(100.0f, 100.0f)));
    board.push_back(new Bishop(1, sf::Vector2f(200.0f, 200.0f)));
    board.push_back(new Queen(0, sf::Vector2f(300.0f, 0.300f)));
    board.push_back(new Knight(1, sf::Vector2f(500.0f, 0.500f)));
    board.push_back(new King(0, sf::Vector2f(400.0f, 0.400f)));

    sf::Image darkImage, lightImage;
    darkImage.create(100, 100, sf::Color(115, 86, 78));
    darkTexture.loadFromImage(darkImage);
    darkSquare.setTexture(darkTexture);

    lightImage.create(100, 100, sf::Color(189, 170, 137));
    lightTexture.loadFromImage(lightImage);
    lightSquare.setTexture(lightTexture);
    
    currentColor = 0;
}

GameScreen::~GameScreen() {
    for (auto piece : board) {
        delete piece;
    }
}

Piece* GameScreen::getPiece(int col, int row) {
    for (auto piece : board) {
        if (piece->getCol() == col && piece->getRow() == row)
            return piece;
    }

    return nullptr;
}

bool GameScreen::makeMove(int col, int row) {
    if (!selectedPiece)
        return false;

    if (!selectedPiece->isValidMove(col, row))
        return false;

    Piece* targetPiece = getPiece(col, row);
    if (targetPiece == nullptr)
        return true;

    if (targetPiece == selectedPiece || targetPiece->color == selectedPiece->color)
        return false;

    takePiece(targetPiece);
    return true;
}

void GameScreen::takePiece(Piece* targetPiece) {
    board.erase(std::remove_if(
        board.begin(),
        board.end(),
        [targetPiece](const Piece* p) { return p == targetPiece; }
    ));
}

void GameScreen::handleMousePressed(const sf::Vector2f& mousePos) {
    if (selectedPiece)
        return;

    for (auto piece : board) {
        if (piece->color == currentColor && 
            piece->getCol() == static_cast<int>(mousePos.x) / 100
            && piece->getRow() == static_cast<int>(mousePos.y) / 100) {
            
            selectedPiece = piece;
            break;
        }
    }
}

void GameScreen::handleMouseReleased(const sf::Vector2f& mousePos) {
    if (!selectedPiece)
        return;

    int newCol = static_cast<int>(mousePos.x / 100);
    int newRow = static_cast<int>(mousePos.y / 100);
    bool moveApproved = false;
    Piece* hittingPiece = getPiece(newCol, newRow);

    if (makeMove(newCol, newRow)) {
        selectedPiece->setPosition(sf::Vector2f(newCol*100, newRow*100));
    }
    isDragging = false;
    selectedPiece = nullptr;
}

void GameScreen::handleMouseMoved(const sf::Vector2f& mousePos) {
    if (!selectedPiece)
        return;

    isDragging = true;
}

void GameScreen::draw() {
    drawBoard();
    for (auto piece : board) {
        piece->draw(*window);
    }
}

void GameScreen::drawBoard() {
    int c = 1;

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (c) {
                lightSquare.setPosition(sf::Vector2f(100.0f*col, 100.0f * row));
                window->draw(lightSquare);
            }
            else {
                darkSquare.setPosition(sf::Vector2f(100.0f * col, 100.0f * row));
                window->draw(darkSquare);
            }
            c = !c;
        }
        c = !c;
    }
}