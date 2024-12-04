#include "Piece.h"

sf::Vector2f Piece::getPosition() {
	return position;
}

void Piece::setPosition(sf::Vector2f newPosition) {
	position = newPosition;
}

int Piece::getCol() {
	return position.x / 100;
}

int Piece::getRow() {
	return position.y / 100;
}

void Piece::draw(sf::RenderWindow& window) {
	Sprite.setPosition(position);
	window.draw(Sprite);
}