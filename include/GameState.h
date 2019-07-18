#pragma once
#include "project.h"
#include "Button.h"

enum State {NULL_STATE, MAIN_MENU, PL_VS_PL, PL_VS_COMP, PL_VS_WALL, WIN_GAME, EXIT};

class GameState
{
    public:
        GameState();
        virtual void logic() = 0;
        virtual void draw() = 0;
        virtual ~GameState();

        int score_left, score_right;
    protected:
        sf::RenderWindow* window;
        State* next_state;
};

class MainMenu : public GameState
{
    public:
        MainMenu(sf::RenderWindow& window, State& next_state);

        void events();

        void logicButtons();
        virtual void logic();

        virtual void draw();
        virtual ~MainMenu();

    private:
        sf::Font font;
        sf::RectangleShape shape_bg;

        sf::Vector2i mouse_position;
        bool mouse_is_left_btn_released;

        Button btn_player2player;
        Button btn_player2comp;
        Button btn_player2wall;
        Button btn_exit;
};

class WinGame : public GameState
{
    public:
        WinGame(sf::RenderWindow& window, State& next_state, int score_left, int score_right);
        virtual void logic();
        virtual void draw();
        virtual ~WinGame();
    private:
        sf::Font font;
        Button table;

        int timer;
};
