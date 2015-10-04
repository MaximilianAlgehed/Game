#include "GameStack.h"
#include "GameState.h"

GameStack::GameStack(sf::RenderWindow * _window)
{
    window = _window;
}

GameStack::~GameStack()
{
}

void GameStack::exit()
{
    while(this->stack.size() != 0)
        pop();
}

void GameStack::push(GameState * state)
{
    stack.push(state);
}

void GameStack::pop()
{
    delete this->stack.top();
    this->stack.pop();
}

bool GameStack::isExiting()
{
    return stack.size() == 0;
}

void GameStack::handleEvent(sf::Event event)
{
    peek()->handleEvent(event);
}

GameState * GameStack::peek()
{
    return this->stack.top();
}

void GameStack::update(float dt)
{
    peek()->update(dt);
}

void GameStack::draw()
{
    peek()->draw(window);
}
