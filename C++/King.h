#pragma once
#include "Piece.h"
class King : public Piece
{
public:
	King(int newColor, sf::Vector2f newPosition);
    King& operator=(const King& other) {
        if (this != &other) { 
            Sprite = other.Sprite;
            texture = other.texture;
            position = other.position;
            prevCol = other.prevCol;
            prevRow = other.prevRow;
            Type = other.Type;
            timesPositionSet = other.timesPositionSet;
        }
        return *this;
    }
	bool isValidMove(int newCol, int newRow) const;
};

