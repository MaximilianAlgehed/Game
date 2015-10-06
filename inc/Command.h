#ifndef COMMAND_H
#define COMMAND_H

#include <functional>
#include <queue>

class SceneNode;

//A command object
class Command
{
    public:

        //Category of possible targets
        enum TargetCategory
        {
            None = 0,
            Spaceship = 1
        };

        //The action to be performed on the SceneNode matching target
        std::function<void(SceneNode*, sf::Time)> action;
        //The targt categories for this command
        unsigned int targetCategory;
};

//A class for queueing commands
class CommandQueue
{
    private:
        //It's just an api for this queue to be honest
        std::queue<Command> queue;
        
    public:
        //enqueu command
        void enqueue(Command command) {queue.push(command);}
        Command pop() {Command command = queue.front(); queue.pop(); return command;}
        bool isEmpty() {return queue.size() == 0;}
};

#endif
