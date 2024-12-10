#pragma once
#include "Piece.h"
class Queen : public Piece
{
public:
	Queen(int newColor, sf::Vector2f newPosition);
	bool isValidMove(int newCol, int newRow) const;
};

