#include "Button.h"

Button::Button()
{

}

void Button::init(int x, int y, int size_x, int size_y, sf::String str, sf::Font& font)
{
    this->x = x;
    this->y = y;
    this->size_x = size_x;
    this->size_y = size_y;

    shape.setPosition(sf::Vector2f(x,y));
    shape.setSize(sf::Vector2f(size_x,size_y));
    shape.setFillColor(COLOR_MIDLE);

    text.setPosition(sf::Vector2f(x+10,y+15));
    text.setCharacterSize(size_y/2);
    text.setFont(font);
    text.setString(str);

}

Button::~Button()
{

}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(shape, states);
    target.draw(text, states);
}

bool Button::isMovedOn(sf::Vector2i mouse_position)
{
    return x <= mouse_position.x && x+size_x >= mouse_position.x
        && y <= mouse_position.y && y+size_y >= mouse_position.y;
}


