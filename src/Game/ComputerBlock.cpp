#include "Game/Block.h"

ComputerBlock::ComputerBlock(int x, int y, int size_x, int size_y)
                     : Block(x, y, size_x, size_y)
{
    speed = 0;
}

void ComputerBlock::logic(int x, int y, sf::Vector2i speed)
{
    if(this->y+size_y/2 < y)
        this->speed = +SPEED_PLAYER;
    else if(this->y+size_y/2 > y)
        this->speed = -SPEED_PLAYER;
    else
        this->speed = 0;
    logicPhysics();
}

ComputerBlock::~ComputerBlock()
{

}
