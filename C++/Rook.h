#pragma once
#include "Piece.h"
class Rook : public Piece
{
public:
	Rook(int newColor, sf::Vector2f newPosition);
	bool isValidMove(int newCol, int newRow) const;
};

