#pragma once
#include "Piece.h"
class Bishop : public Piece
{
public:
	Bishop(int newColor, sf::Vector2f newPosition);
	bool isValidMove(int newCol, int newRow) const;
};

