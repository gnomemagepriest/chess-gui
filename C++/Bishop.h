#pragma once
#include "Piece.h"
class Bishop : public Piece
{
public:
	Bishop(int newColor, sf::Vector2f newPosition);
	bool isValidMove(sf::Vector2f newPosition) const;
};

