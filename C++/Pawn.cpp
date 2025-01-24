#include "Pawn.h"
#include <string>
#include <iostream>
#include <filesystem>;

Pawn::Pawn(int newColor, sf::Vector2f newPosition) {
	color = newColor;
	std::string path = "../Assets/pawn-";
	if (!color)
		path += "black.png";
	else
		path += "white.png";

	try {
		sf::Image image;
		image.loadFromFile(path);
		//image.create(100, 100, sf::Color(color * 255, color * 255, color * 255));
		texture.loadFromImage(image);
	}
	catch (...) {
		throw 1;
	}
	
	Type = "Pawn";

	Sprite.setTexture(texture);
	Sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
	this->setPosition(newPosition);
}

bool Pawn::isValidMove(int newCol, int newRow) const {
	return false;
}