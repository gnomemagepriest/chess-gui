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
	int currentColor;
	Piece* getPiece(int col, int row);
	bool canMakeMove(int col, int row);
	bool pieceOnAStraightLine(int newCol, int newRow);
	bool pieceOnADiagonalLine(int newCol, int newRow);
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
};

