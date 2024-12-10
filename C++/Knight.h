#pragma once
#include "Piece.h"
class Knight : public Piece
{
public:
	Knight(int newColor, sf::Vector2f newPosition);
	bool isValidMove(int newCol, int newRow) const;
};

