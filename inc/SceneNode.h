#ifndef SCENENODE_H
#define SCENENODE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <set>

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
        //Get the global position of this object
        sf::Vector2f getWorldPosition() const;
        //Get the bounding rect of the entity
        virtual sf::FloatRect getGlobalBounds() const;
        //Get the global rotation of this object
        float getWorldRotation() const;
        //act on a command
        void onCommand(Command, sf::Time);
        //Find if this object is clicked
        bool isClicked(SceneNode **, float, float);
        //find out if this node is due to be removed
        virtual bool toRemove();
        //Remove all objects that need to be removed
        void removeNodes();
        //Collect collisions
        void checkCollision(SceneNode *, std::set<std::pair<SceneNode*, SceneNode*>>&);
        //Collect all collisions in the scene
        void collectCollisions(SceneNode * graph, std::set<std::pair<SceneNode*, SceneNode*>>&);
        //Collide with another scene node
        virtual void collide(SceneNode * other);
        //Get the category of the object
        unsigned int getCategory();

    private:
        //Parent and children
        SceneNode* parent;
        std::vector<SceneNode*> children;
        //Draw the node and all it's children
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    protected:
        //Update and draw the current node
        virtual void updateCurrent(sf::Time dt);
        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
        //The category of this node
        unsigned int category;
        //check if this object is clicked
        virtual bool clickedCurrent(float x, float y) {return false;}
};

#endif
