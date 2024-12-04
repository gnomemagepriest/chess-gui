#pragma once
#include <SFML/Graphics.hpp>

class Piece
{
protected:
    sf::Sprite Sprite;
    sf::Texture texture;
    sf::Vector2f position;
    double prevCol, prevRow;
public:
    virtual ~Piece() {}
    virtual bool isValidMove(sf::Vector2f newPosition) const = 0;
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f newPosition);   
    int getCol();
    int getRow();
    int color;
};

