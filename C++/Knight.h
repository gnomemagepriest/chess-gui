#pragma once
#include "Piece.h"
class Knight : public Piece
{
public:
	Knight(int newColor, sf::Vector2f newPosition);
	bool isValidMove(sf::Vector2f newPosition) const;
};

