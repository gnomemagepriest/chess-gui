#pragma once
#include "Piece.h"
class King : public Piece
{
public:
	King(int newColor, sf::Vector2f newPosition);
	bool isValidMove(int newCol, int newRow) const;
	bool isFirstMove();
};

