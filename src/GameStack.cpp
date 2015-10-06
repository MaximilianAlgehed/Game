#include "GameStack.h"
#include "GameState.h"

//Initialize the stack
GameStack::GameStack(sf::RenderWindow* _window)
{
    window = _window;
}

//Destroy the stack
GameStack::~GameStack()
{
}

//Remove all emenents on the stack
void GameStack::exit()
{
    while(this->stack.size() != 0)
        pop();
}

//Push a new state on the stack
void GameStack::push(GameState * state)
{
    stack.push(state);
}

//Pop a state from the stack
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

void GameStack::handleInput()
{
    peek()->handleInput();
}

GameState * GameStack::peek()
{
    return this->stack.top();
}

void GameStack::update(sf::Time dt)
{
    peek()->update(dt);
}

void GameStack::draw()
{
    peek()->draw();
}
