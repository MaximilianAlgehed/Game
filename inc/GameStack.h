#ifndef GAMESTACK_H
#define GAMESTACK_H

#include <stack>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class GameState;

class GameStack
{
    private:
        std::stack<GameState*> stack; 
        sf::RenderWindow * window;

    public:
        GameStack(sf::RenderWindow * _window);
        ~GameStack();

        void exit();

        void push(GameState * state);
        void pop();
        GameState * peek();

        void update(float dt);
        void handleEvent(sf::Event event);
        void draw();

        bool isExiting();
};
#endif
