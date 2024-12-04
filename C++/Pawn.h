#pragma once
#include "Piece.h"
class Pawn : public Piece
{
public:
	Pawn(int newColor, sf::Vector2f newPosition);
	bool isValidMove(sf::Vector2f newPosition) const;
};

