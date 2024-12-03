#pragma once
#include <SFML/Graphics.hpp>
#include "Piece.h"

class GameScreen
{
private:
	Piece* selectedPiece;
	std::vector<Piece*> board;
	bool isDragging;
	sf::Vector2f offset;
	void handleMousePressed(const sf::Vector2f& mousePos);
	void handleMouseReleased();
	void handleMouseMoved(const sf::Vector2f& mousePos);
public:
	GameScreen();
	~GameScreen();
	void update(sf::Event event);
	void draw(sf::RenderWindow& window);
};

