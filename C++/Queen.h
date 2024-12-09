#pragma once
#include "Piece.h"
class Queen : public Piece
{
public:
	Queen(int newColor, sf::Vector2f newPosition);
	bool isValidMove(sf::Vector2f newPosition) const;
};

