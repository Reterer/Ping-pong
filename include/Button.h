#pragma once
#include "project.h"

class Button : public sf::Drawable, public sf::Transformable
{
    public:
        Button();
        void init(int x, int y, int size_x, int size_y, sf::String text, sf::Font& font);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual ~Button();

        bool isMovedOn(sf::Vector2i mouse_position);

        sf::Text text;
        sf::RectangleShape shape;

        int x,y;
        int size_x, size_y;
};
