#include "StateManager.h"

void changeState(GameState*& current_state, State& next_state, sf::RenderWindow& window)
{
    if(next_state)
    {
        int score_left,score_right;
        if(next_state == WIN_GAME)
        {
            score_left = current_state->score_left;
            score_right = current_state->score_right;
        }
        delete current_state;
        switch(next_state)
        {
            case MAIN_MENU :
            {
                current_state = new MainMenu(window, next_state);
                break;
            }
            case PL_VS_PL :
            {
                current_state = new Game(window, next_state, PLAYER);
                break;
            }
            case PL_VS_COMP :
            {
                current_state = new Game(window, next_state, COMPUTER);
                break;
            }
            case PL_VS_WALL :
            {
                current_state = new Game(window, next_state, WALL);
                break;
            }
            case WIN_GAME :
            {
                current_state = new WinGame(window, next_state, score_left, score_right);
            }
            default:
                break;
        }

        if(next_state != EXIT)
            next_state = NULL_STATE;
    }
}
