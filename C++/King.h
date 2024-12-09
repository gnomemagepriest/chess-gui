#pragma once
#include "Piece.h"
class King : public Piece
{
public:
	King(int newColor, sf::Vector2f newPosition);
	bool isValidMove(sf::Vector2f newPosition) const;
};

