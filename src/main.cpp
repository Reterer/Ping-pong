#include "project.h"
#include "GameState.h"
#include "StateManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ping Pong");
    window.setFramerateLimit(FPS);

    State next_state = NULL_STATE;
    GameState* current_state = new MainMenu(window, next_state);

    while (window.isOpen() && next_state != EXIT)
    {
        current_state->logic();
        current_state->draw();
        changeState(current_state, next_state, window);
    }

    window.close();
    return 0;
}
