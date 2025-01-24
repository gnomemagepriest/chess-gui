#include "Bishop.h"

Bishop::Bishop(int newColor, sf::Vector2f newPosition) {
	color = newColor;
	std::string path = "../Assets/bishop-";
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

	Sprite.setTexture(texture);
	Sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
	this->setPosition(newPosition);
}

bool Bishop::isValidMove(int newCol, int newRow) const {
	if ((newCol >= 0 && newCol <= 7 && newRow >= 0 && newRow <= 7)	
		&& std::abs(newCol - prevCol) == std::abs(newRow - prevRow)) {
		return true;
	}

	return false;
}