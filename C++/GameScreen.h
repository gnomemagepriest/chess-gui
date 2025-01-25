#pragma once
#include <SFML/Graphics.hpp>
#include "Piece.h"

class GameScreen
{
private:
	Piece* selectedPiece;
	Piece* targetPiece;
	std::vector<Piece*> board;
	bool isDragging;
	sf::RenderWindow* window;
	sf::Texture darkTexture, lightTexture;
	sf::Sprite darkSquare, lightSquare;
	sf::Font font;
	sf::Text currentPlayerText;
	int currentColor;
	void updateCurrentPlayerText();
	Piece* getPiece(int col, int row);
	bool canMakeMove(Piece* piece, int col, int row);
	bool movePawn(int newCol, int newRow);
	bool handleCastling(int newCol, int newRow);
	bool pieceOnAStraightLine(Piece* currentPiece, int newCol, int newRow);
	bool pieceOnADiagonalLine(Piece* currentPiece, int newCol, int newRow);
	bool isKingInCheck();
	bool isCheckmate();
	void takePiece(Piece* targetPiece);
	void handleMousePressed(const sf::Vector2f& mousePos);
	void handleMouseReleased(const sf::Vector2f& mousePos);
	void handleMouseMoved(const sf::Vector2f& mousePos);
	void drawBoard();
public:
	GameScreen(sf::RenderWindow* mainWindow);
	~GameScreen();
	void update(sf::Event event);
	void draw();
	bool isGameOver;
	std::string getEndGameMessage();
};

