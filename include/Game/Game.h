#pragma once
#include <SFML/Audio.hpp>

#include "project.h"
#include "GameState.h"
#include "Game/Block.h"

enum GameMode {PLAYER, COMPUTER, WALL};

struct Rocket
{
    sf::RectangleShape shape;
    sf::Vector2i speed;
    int x;
    int y;
};

class Game : public GameState
{
    public:
        Game(sf::RenderWindow& window, State& next_state, GameMode mode);

        void events();
        virtual void logic();
        virtual void draw();

        virtual ~Game();
    private:
        bool isCollision(Block* block);

        void handleKeyPressed();
        void rocketPhysics();
        void win();

        void respawnRocket();
        void drawRocket();
        void drawUserInterface();

        GameMode mode;

        sf::Text text;
        sf::Font font;

        sf::Sound pong_sound;
        sf::SoundBuffer pong_buff;

        sf::Vector2f start_point;

        PlayerBlock* player1;
        PlayerBlock* player2;
        ComputerBlock* enemy;

        Rocket rocket;
};
