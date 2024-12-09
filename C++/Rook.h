#pragma once
#include "Piece.h"
class Rook : public Piece
{
public:
	Rook(int newColor, sf::Vector2f newPosition);
	bool isValidMove(sf::Vector2f newPosition) const;
};

