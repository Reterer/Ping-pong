#include <string>
#include "Game/Game.h"

Game::Game(sf::RenderWindow& window, State& next_state, GameMode mode)
{
    this->window = &window;
    this->next_state = &next_state;

    this->mode = mode;

    start_point = sf::Vector2f(WINDOW_WIDTH/2-10,WINDOW_HEIGHT/2-10);

    player1 = new PlayerBlock(20,20,20,100);
    player2 = new PlayerBlock(WINDOW_WIDTH-40,20,20,100);

    enemy = new ComputerBlock(WINDOW_WIDTH-40,20,20,100);

    rocket.shape.setPosition(start_point);
    rocket.shape.setSize(sf::Vector2f(ROCKET_SIZE,ROCKET_SIZE));
    rocket.shape.setFillColor(COLOR_WHITE);
    rocket.speed = sf::Vector2i(SPEED_ROCKET,SPEED_ROCKET);
    rocket.speed.x = 10;
    rocket.x = start_point.x;
    rocket.y = start_point.y;

    score_left = 0;
    score_right = 0;

    font.loadFromFile("data\\fonts\\Inconsolata-Regular.ttf");
    pong_buff.loadFromFile("data\\tracks\\pong.wav");

    text.setFont(font);
    text.setCharacterSize(45);
    text.setColor(COLOR_WHITE);
    text.setPosition(sf::Vector2f(WINDOW_WIDTH/2-55,20));
    text.setString("0 : 0");

    pong_sound.setBuffer(pong_buff);
}

Game::~Game()
{

}

void Game::handleKeyPressed()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        player1->speed = -SPEED_PLAYER;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        player1->speed = +SPEED_PLAYER;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        player2->speed = -SPEED_PLAYER;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        player2->speed = +SPEED_PLAYER;
}

void Game::events()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            (*next_state) = EXIT;
    }
    handleKeyPressed();
}

void Game::win()
{
    (*next_state) = WIN_GAME;
}

void Game::respawnRocket()
{
    rocket.x = start_point.x;
    rocket.y = start_point.y;
    rocket.speed.y *= -1;
}

bool Game::isCollision(Block* block)
{
    bool is_collision = false;

    if(block->x-ROCKET_SIZE <= rocket.x && block->x+block->size_x >= rocket.x
    && block->y-ROCKET_SIZE <= rocket.y && block->y+block->size_y >= rocket.y)
    {
        //Left side
        if(block->x < rocket.x)
        {
            is_collision = true;
            if(rocket.speed.x/25 == 0)
                rocket.speed.x += rocket.speed.x>0?1:-1;
        }
        //Right side
        else
        {
            is_collision = true;
            if(rocket.speed.x/25 == 0)
                rocket.speed.x += rocket.speed.x>0?1:-1;
        }
    }
    return is_collision;
}

void Game::rocketPhysics()
{
    //update cords rocket
    rocket.x += rocket.speed.x;
    rocket.y += rocket.speed.y;

    //collision with window
    bool is_collision = false;
    //left
    if(rocket.x < 0)
    {
        is_collision = true;
        rocket.speed.x = -rocket.speed.x;
        respawnRocket();
        score_right++;
        if(score_right >= MAX_SCORE)
            win();
    }
    //right
    else if(rocket.x + ROCKET_SIZE > WINDOW_WIDTH)
    {
        is_collision = true;
        rocket.x = WINDOW_WIDTH - ROCKET_SIZE;
        rocket.speed.x = -rocket.speed.x;
        score_left++;
        if(mode != WALL)
        {
            respawnRocket();
            if(score_left >= MAX_SCORE)
                win();
        }
        else
        {
            if(rocket.speed.x/32 == 0)
                rocket.speed.x += rocket.speed.x>0?1:-1;
        }
    }
    //up
    if(rocket.y < 0)
    {
        is_collision = true;
        rocket.y = 0;
        rocket.speed.y = -rocket.speed.y;
    }
    //down
    else if(rocket.y + ROCKET_SIZE > WINDOW_HEIGHT)
    {
        is_collision = true;
        rocket.y = WINDOW_HEIGHT - ROCKET_SIZE;
        rocket.speed.y = -rocket.speed.y;
    }

    //Collision with blocks
    //Collision with player1
    if (isCollision(player1))
    {
        rocket.speed.x = -rocket.speed.x;
        is_collision = true;
    }
    //... player2
    if (mode == PLAYER && isCollision(player2))
    {
        rocket.speed.x = -rocket.speed.x;
        is_collision = true;
    }
    //... enemy
    if (mode == COMPUTER && isCollision(enemy))
    {
        rocket.speed.x = -rocket.speed.x;
        is_collision = true;
    }
    //Sound
    if(is_collision)
        pong_sound.play();
}

void Game::logic()
{
    events();
    rocketPhysics();

    player1->logic(rocket.x, rocket.y, rocket.speed);

    if(mode == COMPUTER)
        enemy->logic(rocket.x, rocket.y, rocket.speed);
    else if(mode == PLAYER)
        player2->logic(rocket.x, rocket.y, rocket.speed);

    if(score_left >= MAX_SCORE || score_right >= MAX_SCORE)
        win();
}

void Game::drawRocket()
{
    rocket.shape.setPosition(sf::Vector2f(rocket.x,rocket.y));
    window->draw(rocket.shape);
}

void Game::drawUserInterface()
{
    //text
    text.setString(std::to_string(score_left)+" : "+std::to_string(score_right));
    window->draw(text);
}

void Game::draw()
{
    window->clear(COLOR_DARK);

    drawRocket();

    //drawing blocks
    window->draw(*player1);
    switch(mode)
    {
        case PLAYER:
            window->draw(*player2);
            break;
        case COMPUTER:
            window->draw(*enemy);
            break;
    }
    //--------------
    drawUserInterface();

    window->display();
}
