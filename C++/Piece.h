#pragma once
#include <SFML/Graphics.hpp>

class Piece
{
private:
    sf::Sprite Sprite;
    double prevCol, prevRow;
    sf::Vector2f position;
    int getCol();
    int getRow();
public:
    ~Piece() {}
    virtual bool isValidMove(sf::Vector2f newPosition) const = 0;
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f newPosition);   
    int col = getCol(), row = getRow();
    int color;
};

