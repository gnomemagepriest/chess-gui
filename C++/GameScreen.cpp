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
    
    // Пешки
    board.push_back(new Pawn(0, sf::Vector2f(0.0f,100.0f)));
    board.push_back(new Pawn(0, sf::Vector2f(100.0f, 100.0f)));
    board.push_back(new Pawn(0, sf::Vector2f(200.0f, 100.0f)));
    board.push_back(new Pawn(0, sf::Vector2f(300.0f, 100.0f)));
    board.push_back(new Pawn(0, sf::Vector2f(400.0f, 100.0f)));
    board.push_back(new Pawn(0, sf::Vector2f(500.0f, 100.0f)));
    board.push_back(new Pawn(0, sf::Vector2f(600.0f, 100.0f)));
    board.push_back(new Pawn(0, sf::Vector2f(700.0f, 100.0f)));
    board.push_back(new Pawn(1, sf::Vector2f(00.0f, 600.0f)));
    board.push_back(new Pawn(1, sf::Vector2f(100.0f, 600.0f)));
    board.push_back(new Pawn(1, sf::Vector2f(200.0f, 600.0f)));
    board.push_back(new Pawn(1, sf::Vector2f(300.0f, 600.0f)));
    board.push_back(new Pawn(1, sf::Vector2f(400.0f, 600.0f)));
    board.push_back(new Pawn(1, sf::Vector2f(500.0f, 600.0f)));
    board.push_back(new Pawn(1, sf::Vector2f(600.0f, 600.0f)));
    board.push_back(new Pawn(1, sf::Vector2f(700.0f, 600.0f)));

    // Ладьи
    board.push_back(new Rook(0, sf::Vector2f(0.0f, 0.0f)));
    board.push_back(new Rook(0, sf::Vector2f(700.0f, 0.0f)));
    board.push_back(new Rook(1, sf::Vector2f(0.0f, 700.0f)));
    board.push_back(new Rook(1, sf::Vector2f(700.0f, 700.0f)));

    // Ферзи и короли
    board.push_back(new Queen(0, sf::Vector2f(300.0f, 0.00f)));
    board.push_back(new King(0, sf::Vector2f(400.0f, 0.00f)));
    board.push_back(new Queen(1, sf::Vector2f(300.0f, 700.00f)));
    board.push_back(new King(1, sf::Vector2f(400.0f, 700.00f)));

    // Кони
    board.push_back(new Knight(0, sf::Vector2f(100.0f, 0.0f)));
    board.push_back(new Knight(0, sf::Vector2f(600.0f, 0.0f)));
    board.push_back(new Knight(1, sf::Vector2f(100.0f, 700.0f)));
    board.push_back(new Knight(1, sf::Vector2f(600.0f, 700.0f)));

    // Слоны
    board.push_back(new Bishop(0, sf::Vector2f(200.0f, 0.0f)));
    board.push_back(new Bishop(0, sf::Vector2f(500.0f, 0.0f)));
    board.push_back(new Bishop(1, sf::Vector2f(200.0f, 700.0f)));
    board.push_back(new Bishop(1, sf::Vector2f(500.0f, 700.0f)));

    sf::Image darkImage, lightImage;
    darkImage.create(100, 100, sf::Color(115, 86, 78));
    darkTexture.loadFromImage(darkImage);
    darkSquare.setTexture(darkTexture);

    lightImage.create(100, 100, sf::Color(189, 170, 137));
    lightTexture.loadFromImage(lightImage);
    lightSquare.setTexture(lightTexture);
    
    currentColor = 1;
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

void GameScreen::movePawn(int newCol, int newRow) {
    if (newCol < 0 || newCol > 7 || newRow < 0 || newRow > 7)
        return;

    int colorAdjust = currentColor ? -1 : 1;
    int prevCol = selectedPiece->getCol();
    int prevRow = selectedPiece->getRow();
    bool firstMove = currentColor ? prevRow == 6: prevRow == 1 ;

    if (std::abs(newCol - prevCol) > 1
        || (currentColor ? prevRow <= newRow : prevRow >= newRow))
        return;

    Piece* hittingPiece = getPiece(newCol, newRow);

    if (newCol == prevCol && newRow == prevRow + colorAdjust) {
        if (hittingPiece != nullptr) {
            return; // нету хода, если клетка занята
        }
    }

    if (newCol == prevCol && newRow == prevRow + colorAdjust*2) {
        if (!firstMove)
            return;

        if (hittingPiece != nullptr)
            return;

        if (getPiece(newCol, prevRow + colorAdjust) != nullptr)
            return;
    }

    if ((newCol == prevCol - 1 || newCol == prevCol + 1) && newRow == prevRow + colorAdjust) {
        if (hittingPiece == nullptr)
            return;

        if (hittingPiece->color == selectedPiece->color)
            return;
        takePiece(hittingPiece);
    }

    selectedPiece->setPosition(sf::Vector2f(newCol * 100, newRow * 100));
    currentColor = !currentColor;
}

bool GameScreen::handleCastling(int newCol, int newRow) {
    int prevCol = selectedPiece->getCol();
    int prevRow = selectedPiece->getRow();
    Piece* castlingPiece = nullptr;

    // Вправо
    if (newCol == (prevCol + 2) && newRow == prevRow && !pieceOnAStraightLine(newCol, newRow)) {
        for (auto piece : board) {
            if (piece->getCol() == (newCol + 1) && piece->getRow() == (newRow) && piece->isFirstMove()) {
                castlingPiece = piece;
                break;
            }
        }
    }

    // Влево
    if (newCol == (prevCol - 2) && newRow == prevRow && !pieceOnAStraightLine(newCol-1, newRow)) {
        for (auto piece : board) {
            if (piece->getCol() == (newCol - 2) && piece->getRow() == (newRow) && piece->isFirstMove()) {
                castlingPiece = piece;
                break;
            }
        }
    }

    // Собственно ход
    if (castlingPiece == nullptr) {
        return false;
    }

    if (castlingPiece->getCol() == 0) {
        castlingPiece->setPosition(sf::Vector2f(
            (castlingPiece->getCol()+3)*100, 
            castlingPiece->getRow()*100));
    } else if (castlingPiece->getCol() == 7) {
        castlingPiece->setPosition(sf::Vector2f(
            (castlingPiece->getCol() - 2) * 100,
            castlingPiece->getRow()*100));
    }

    selectedPiece->setPosition(sf::Vector2f(newCol*100, newRow*100));
    currentColor = !currentColor;
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

    if (selectedPiece->getRow() == newRow) {
        // при движении влево
        for (int col = selectedPiece->getCol() - 1; col > newCol; col--)
            for (auto piece : board)
                if (piece->getCol() == col && piece->getRow() == newRow)
                    return true;

        // при движении вправо
        for (int col = selectedPiece->getCol() + 1; col < newCol; col++)
            for (auto piece : board)
                if (piece->getCol() == col && piece->getRow() == newRow)
                    return true;
    }
    else if (selectedPiece->getCol() == newCol) {
        // при движении вверх
        for (int row = selectedPiece->getRow() - 1; row > newRow; row--)
            for (auto piece : board)
                if (piece->getRow() == row && piece->getCol() == newCol)
                    return true;

        // при движении вниз
        for (int row = selectedPiece->getRow() + 1; row < newRow; row++)
            for (auto piece : board)
                if (piece->getCol() == newCol && piece->getRow() == row)
                    return true;
    }

    return false;
}

bool GameScreen::pieceOnADiagonalLine(int newCol, int newRow) {
    if (selectedPiece == nullptr)
        return false;

    int prevCol = selectedPiece->getCol();
    int prevRow = selectedPiece->getRow();

    if (prevCol == newCol || prevRow == newRow) {

        if (newRow < prevRow) {
            // Влево вверх
            for (int col = prevCol - 1; col > newCol; col--) {
                int diff = std::abs(col - prevCol);
                for (auto piece : board)
                    if (piece->getCol() == col && piece->getRow() == prevRow - diff)
                        return true;
            }

            // Вправо вверх
            for (int col = prevCol + 1; col < newCol; col++) {
                int diff = std::abs(col - prevCol);
                for (auto piece : board)
                    if (piece->getCol() == col && piece->getRow() == prevRow - diff)
                        return true;
            }

        }
        else if (newRow > prevRow) {
            // Влево вниз
            for (int col = prevCol - 1; col > newCol; col--) {
                int diff = std::abs(col - prevCol);
                for (auto piece : board)
                    if (piece->getCol() == col && piece->getRow() == prevRow + diff)
                        return true;
            }

            // Вправо вниз
            for (int col = prevCol + 1; col < newCol; col++) {
                int diff = std::abs(col - prevCol);
                for (auto piece : board)
                    if (piece->getCol() == col && piece->getRow() == prevRow + diff)
                        return true;
            }

        }
    }

    return false;
}

bool GameScreen::kingIllegalMoveDetected(int newCol, int newRow) {
    King* originalSelectedPiece = (King*)selectedPiece;

    for (auto piece : board) {
        selectedPiece = piece;
        if (piece->color != currentColor && canMakeMove(newCol, newRow)) {
            selectedPiece = originalSelectedPiece;
            return true;
        }
    }

    selectedPiece = originalSelectedPiece;
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

    if (selectedPiece->getType() == "King" && kingIllegalMoveDetected(newCol, newRow)) {
        return;
    }

    if (selectedPiece->getType() == "Pawn") {
        movePawn(newCol, newRow);
    }
    else if (selectedPiece->getType() == "King" && selectedPiece->isFirstMove()) {
        if (!handleCastling(newCol, newRow)) {
            if (canMakeMove(newCol, newRow)) {
                takePiece(targetPiece);
                selectedPiece->setPosition(sf::Vector2f(newCol * 100, newRow * 100));
                currentColor = !currentColor;
            }
        }
    }
    else if (canMakeMove(newCol, newRow)) {
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