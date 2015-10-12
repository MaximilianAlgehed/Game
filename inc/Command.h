#ifndef COMMAND_H
#define COMMAND_H

#include <functional>
#include <list>

class SceneNode;

//A command object
class Command
{
    public:

        //Category of possible targets
        enum TargetCategory
        {
            None = 0,
            Spaceship = 1,
            Projectile = 2,
            Weapon = 4
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
        std::list<Command> queue;
        
    public:
        //enqueu command
        void enqueue(Command command) {queue.push_back(command);}
        Command pop() {Command command = queue.front(); queue.pop_front(); return command;}
        bool isEmpty() {return queue.size() == 0;}
};

#endif
