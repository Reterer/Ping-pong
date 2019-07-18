#include "Game/Block.h"

PlayerBlock::PlayerBlock(int x, int y, int size_x, int size_y)
                 : Block(x, y, size_x, size_y)
{
    speed = 0;
}

void PlayerBlock::logic(int x, int y, sf::Vector2i speed)
{
    logicPhysics();
}

PlayerBlock::~PlayerBlock()
{

}

