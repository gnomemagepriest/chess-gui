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
    selectedPiece = nullptr;
    targetPiece = nullptr;
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

bool GameScreen::canMakeMove(int col, int row) {
    if (!selectedPiece)
        return false;

    if (!selectedPiece->isValidMove(col, row))
        return false;

    if (pieceOnAStraightLine(col, row))
        return false;

    if (pieceOnADiagonalLine(col, row))
        return false;

    targetPiece = getPiece(col, row);
    if (targetPiece == nullptr)
        return true;

    if (targetPiece == selectedPiece || targetPiece->color == selectedPiece->color)
        return false;

    return true;
}

void GameScreen::takePiece(Piece* targetPiece) {
    if (targetPiece == nullptr)
        return;

    board.erase(std::remove_if(
        board.begin(),
        board.end(),
        [targetPiece](const Piece* p) { return p == targetPiece; }
    ));
}

bool GameScreen::pieceOnAStraightLine(int newCol, int newRow) {
    if (selectedPiece == nullptr)
        return false;

    // ��� �������� �����
    for (int col = selectedPiece->getCol()-1; col > newCol; col--)
        for (auto piece : board)
            if (piece->getCol() == col && piece->getRow() == newRow)
                return true;

    // ��� �������� ������
    for (int col = selectedPiece->getCol()+1; col < newCol; col++)
        for (auto piece : board)
            if (piece->getCol() == col && piece->getRow() == newRow)
                return true;

    // ��� �������� �����
    for (int row = selectedPiece->getRow()-1; row > newRow; row--)
        for (auto piece : board)
            if (piece->getRow() == row && piece->getCol() == newCol)
                return true;

    // ��� �������� ����
    for (int row = selectedPiece->getRow()+1; row < newRow; row++)
        for (auto piece : board)
            if (piece->getCol() == newCol && piece->getRow() == row)
                return true;

    return false;
}

bool GameScreen::pieceOnADiagonalLine(int newCol, int newRow) {
    if (selectedPiece == nullptr)
        return false;

    int prevCol = selectedPiece->getCol();
    int prevRow = selectedPiece->getRow();

    if (newRow < prevRow) {
        // ����� �����
        for (int col = prevCol - 1; col > newCol; col--) {
            int diff = std::abs(col - prevCol);
            for (auto piece : board)
                if (piece->getCol() == col && piece->getRow() == prevRow - diff)
                    return true;
        }

        // ������ �����
        for (int col = prevCol + 1; col < newCol; col++) {
            int diff = std::abs(col - prevCol);
            for (auto piece : board)
                if (piece->getCol() == col && piece->getRow() == prevRow - diff)
                    return true;
        }

    }
    else if (newRow > prevRow) {
        // ����� ����
        for (int col = prevCol - 1; col > newCol; col--) {
            int diff = std::abs(col - prevCol);
            for (auto piece : board)
                if (piece->getCol() == col && piece->getRow() == prevRow + diff)
                    return true;
        }

        // ������ ����
        for (int col = prevCol + 1; col < newCol; col++) {
            int diff = std::abs(col - prevCol);
            for (auto piece : board)
                if (piece->getCol() == col && piece->getRow() == prevRow + diff)
                    return true;
        }

    }

    return false;
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

    if (canMakeMove(newCol, newRow)) {
        takePiece(targetPiece);
        selectedPiece->setPosition(sf::Vector2f(newCol*100, newRow*100));
        currentColor = !currentColor;
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