#include "Knight.h"

Knight::Knight(int newColor, sf::Vector2f newPosition) {
	color = newColor;
	std::string path = "../Assets/knight-";
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

bool Knight::isValidMove(int newCol, int newRow) const {
	if ((newCol >= 0 && newCol <= 7 && newRow >= 0 && newRow <= 7)			// проверка на достижимую позицию на доске
		&& std::abs(newCol - prevCol) * std::abs(newRow - prevRow) == 2)	// может двигаться только в отношении 1:2 или 2:1
		return true;														// горизонтально и вертикально соответственно

	return false;
}