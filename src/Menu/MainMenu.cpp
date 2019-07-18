#include "GameState.h"

MainMenu::MainMenu(sf::RenderWindow& window, State& next_state)
{
    this->window = &window;
    this->next_state = &next_state;

    //Загрузка
    font.loadFromFile("data\\fonts\\Inconsolata-Regular.ttf");

    //Фон
    shape_bg.setPosition(sf::Vector2f(0,0));
    shape_bg.setSize(sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT));
    shape_bg.setFillColor(COLOR_DARK);

    //Кнопки
    btn_player2player.init(WINDOW_WIDTH/2-225,100,450,80,"Player vs Player",font);
    btn_player2comp.init(WINDOW_WIDTH/2-225,210,450,80,"Player vs Comp",font);
    btn_player2wall.init(WINDOW_WIDTH/2-225,320,450,80,"Player vs Wall",font);
    btn_exit.init(WINDOW_WIDTH/2+75,430,150,80,"Exit",font);
}

MainMenu::~MainMenu()
{

}

void MainMenu::draw()
{
    window->clear();

    //Фон
    window->draw(shape_bg);

    //Кнопки
    window->draw(btn_player2player);
    window->draw(btn_player2comp);
    window->draw(btn_player2wall);
    window->draw(btn_exit);

    window->display();
}

void MainMenu::events()
{
    sf::Event event;

    mouse_position = sf::Mouse::getPosition(*window);
    mouse_is_left_btn_released = false;

    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            (*next_state) = EXIT;

        if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            mouse_is_left_btn_released = true;
    }
}

void MainMenu::logicButtons()
{
    btn_player2player.shape.setFillColor(COLOR_MIDLE);
    btn_player2comp.shape.setFillColor(COLOR_MIDLE);
    btn_player2wall.shape.setFillColor(COLOR_MIDLE);
    btn_exit.shape.setFillColor(COLOR_MIDLE);

    if(btn_player2player.isMovedOn(mouse_position))
    {
        btn_player2player.shape.setFillColor(COLOR_MOVED_ON);
        if(mouse_is_left_btn_released)
            (*next_state) = PL_VS_PL;
    }
    else if(btn_player2comp.isMovedOn(mouse_position))
    {
        btn_player2comp.shape.setFillColor(COLOR_MOVED_ON);
        if(mouse_is_left_btn_released)
            (*next_state) = PL_VS_COMP;
    }
    else if(btn_player2wall.isMovedOn(mouse_position))
    {
        btn_player2wall.shape.setFillColor(COLOR_MOVED_ON);
        if(mouse_is_left_btn_released)
            (*next_state) = PL_VS_WALL;
    }
    else if(btn_exit.isMovedOn(mouse_position))
    {
        btn_exit.shape.setFillColor(COLOR_MOVED_ON);
        if(mouse_is_left_btn_released)
            (*next_state) = EXIT;
    }
}

void MainMenu::logic()
{
    events();
    logicButtons();
}
