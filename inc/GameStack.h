#ifndef GAMESTACK_H
#define GAMESTACK_H

#include <stack>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//Forward definition to avoid
//circular includes
class GameState;

//Represent the game stack
class GameStack
{
    private:
        //Window and stack
        std::stack<GameState*> stack; 

    public:
        //The window
        sf::RenderWindow*  window;

        //constructor destructor, of course
        GameStack(sf::RenderWindow * _window);
        ~GameStack();

        //Exit the gamestack (pop all states)
        void exit();

        //Push a new state on the sack
        void push(GameState * state);
        //Remove the top state
        void pop();
        //Retrieve the current top state
        GameState * peek();

        //Update, handle an event, draw the world etc
        void update(sf::Time dt);
        void handleEvent(sf::Event event);
        void draw();
        void handleInput();

        //Is the game exiting?
        bool isExiting();
};
#endif
