#include "King.h"
#include <cmath>

King::King(int newColor, sf::Vector2f newPosition) {
	color = newColor;
	std::string path = "../Assets/king-";
	if (!color)
		path += "black.png";
	else
		path += "white.png";

	try {
		sf::Image image;
		image.loadFromFile(path);
		//image.create(100, 100, sf::Color(color*255, color * 255, color * 255));
		texture.loadFromImage(image);
	}
	catch (...) {
		throw 1;
	}

	Type = "King";

	Sprite.setTexture(texture);
	Sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
	this->setPosition(newPosition);
}

bool King::isValidMove(int newCol, int newRow) const {
	if ((newCol >= 0 && newCol <= 7 && newRow >= 0 && newRow <= 7)			// проверка на достижимую позицию на доске
		&& (std::abs(newCol - prevCol) + std::abs(newRow - prevRow) == 1	// движение по горизонтали и вертикали
		|| std::abs(newCol - prevCol)*std::abs(newRow - prevRow) == 1))		// движение по диагонали
		return true;

	return false;
}
