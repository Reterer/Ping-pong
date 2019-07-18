#pragma once
#include "project.h"

class Block : public sf::Drawable, public sf::Transformable
{
    public:
        Block(int x, int y, int size_x, int size_y);
        void logicPhysics();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual ~Block();

        int x,y;
        int size_x, size_y;

        int speed;

    protected:
        sf::RectangleShape shape;
};

class PlayerBlock : public Block
{
    public:
        PlayerBlock(int x, int y, int size_x, int size_y);
        void logic(int x, int y, sf::Vector2i speed);
        virtual ~PlayerBlock();
};

class ComputerBlock : public Block
{
    public:
        ComputerBlock(int x, int y, int size_x, int size_y);
        void logic(int x, int y, sf::Vector2i speed);
        virtual ~ComputerBlock();
};
