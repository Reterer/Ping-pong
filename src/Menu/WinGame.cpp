#include "GameState.h"

WinGame::WinGame(sf::RenderWindow& window, State& next_state, int score_left, int score_right)
{
    this->window = &window;
    this->next_state = &next_state;
    this->score_left = score_left;
    this->score_right = score_right;

    //Загрузка
    font.loadFromFile("data\\fonts\\Inconsolata-Regular.ttf");
    table.init(WINDOW_WIDTH/2-225,100,450,80,"That's all!",font);

    timer = FPS*5;
}

void WinGame::draw()
{
    window->clear(COLOR_DARK);
    window->draw(table);
    window->display();
}

void WinGame::logic()
{
    if(timer <= 0)
        (*next_state) = MAIN_MENU;
    timer--;

    sf::Event event;

    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            (*next_state) = EXIT;

        if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            (*next_state) = MAIN_MENU;
    }
}

WinGame::~WinGame()
{

}
