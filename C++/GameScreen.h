#pragma once
#include <SFML/Graphics.hpp>
#include "Piece.h"

class GameScreen
{
private:
	Piece* selectedPiece;
	std::vector<Piece*> board;
	bool isDragging;
	sf::RenderWindow* window;
	sf::Texture darkTexture, lightTexture;
	sf::Sprite darkSquare, lightSquare;
	int currentColor;
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

