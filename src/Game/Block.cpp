#include "Game/Block.h"

Block::Block(int x, int y, int size_x, int size_y)
{
    this->x = x;
    this->y = y;
    this->size_x = size_x;
    this->size_y = size_y;

    speed = 0;

    shape.setPosition(sf::Vector2f(x,y));
    shape.setSize(sf::Vector2f(size_x, size_y));
    shape.setFillColor(COLOR_WHITE);
}

void Block::logicPhysics()
{
    //updateCords
    y += speed;
    //Collision with window
    if(y<0)
    {
        y = 0;
    }
    else if(y+size_y > WINDOW_HEIGHT)
    {
        y = WINDOW_HEIGHT-size_y;
    }

    speed = 0;
    shape.setPosition(sf::Vector2f(x,y));
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
     states.transform *= getTransform();
     target.draw(shape, states);
}

Block::~Block()
{

}
