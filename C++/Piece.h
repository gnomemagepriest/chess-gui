#pragma once
#include <SFML/Graphics.hpp>

class Piece
{
public:
    virtual ~Piece() {}
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual bool isValidMove(int startX, int startY, int endX, int endY) const = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual sf::Vector2f setPosition(sf::Vector2f newPosition) const = 0;
    sf::Sprite Sprite;
    int x, y;
};

