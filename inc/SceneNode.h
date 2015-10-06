#ifndef SCENENODE_H
#define SCENENODE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "Command.h"

//Represent a scene node
class SceneNode : public sf::Transformable, public sf::Drawable
{
    public:
        //Constructor destructor pair
        SceneNode();
        ~SceneNode();
        //Attach a new child to the scene node
        void attachChild(SceneNode *);
        //Detach a child
        SceneNode* detachChild(const SceneNode&);
        //Update the scene node
        void update(sf::Time dt);
        //get the transform of this object relative to the world
        sf::Transform getWorldTransform() const;
        //act on a command
        void onCommand(Command, sf::Time);

    private:
        //Parent and children
        SceneNode* parent;
        std::vector<SceneNode*> children;
        //Draw the node and all it's children
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    protected:
        //Update and draw the current node
        virtual void updateCurrent(sf::Time dt);
        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
        //The category of this node
        unsigned int category;
};

#endif
