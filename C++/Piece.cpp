#include "Piece.h"
#include <iostream>

sf::Vector2f Piece::getPosition() {
	return position;
}

void Piece::setPosition(sf::Vector2f newPosition) {
	position = newPosition;
	prevCol = getCol();
	prevRow = getRow();
	Sprite.setPosition(newPosition);
}

int Piece::getCol() {
	return static_cast<int>(this->position.x) / 100;
}

int Piece::getRow() {
	return static_cast<int>(this->position.y) / 100;
}

std::string Piece::getType() {
	return Type;
}

void Piece::draw(sf::RenderWindow& window) {
	window.draw(Sprite);
}