#include "GameState.h"

GameState::GameState(GameStack * stack) :
    stack(stack),
    window(stack->window),
    view(window->getView())
{
}

GameState::~GameState()
{
}
