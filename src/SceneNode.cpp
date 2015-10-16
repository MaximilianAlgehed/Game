#include <set>

#include "SceneNode.h"
#include "Command.h"

//Initialize a new scene node
SceneNode::SceneNode() : parent(NULL), category(Command::None)
{
}

//Destroy the scene node
SceneNode::~SceneNode()
{
    //Delete all children
    for(SceneNode * ptr : children)
        delete ptr;
}

//Is this node or one of it's children clicked?
bool SceneNode::isClicked(SceneNode ** node, float x, float y)
{
    if(clickedCurrent(x, y))
    {
        *node = this;
        return true;
    }

    for(auto ptr : children)
    {
        if(ptr->isClicked(node, x, y))
            return true;
    }

    return false;
}


//attach a child to the node
void SceneNode::attachChild(SceneNode* child)
{
    child->parent = this;
    this->children.push_back(child);
}

//Find, detach, and return a child node
SceneNode* SceneNode::detachChild(const SceneNode& node)
{
    //Find the child
    auto it = children.begin();
    do
    {
        if(*it == &node)
            break;
        it++; 
    } while(it != children.end());
    //Get the node
    SceneNode * found = *it;
    //Erase the node from the children
    children.erase(it);
    //Detach the child
    found->parent = NULL;
    //Return the node
    return found;
}

//Draw the node
void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //Draw relative to this transform
    states.transform *= getTransform();
    //Draw the current node
    drawCurrent(target, states);
    //Draw the children
    for(auto ptr : children)
    {
        if(ptr)
            ptr->draw(target, states);
    }
}

//Update the node
void SceneNode::update(sf::Time dt)
{
    //Update the curent node
    updateCurrent(dt);
    //Update all children
    for(int i = 0; i < children.size(); i++)
    {
        SceneNode * ptr = children[i];
        ptr->update(dt);
    }
}

//Get the transform of this node relative to the world
sf::Transform SceneNode::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;

    transform = getTransform()*transform;
    //Get the transform by traversing the parents
    for(SceneNode * node = this->parent; node != NULL; node = node->parent)
        transform = node->getTransform() * transform;

    return transform;
}

//Get the global position of this object
sf::Vector2f SceneNode::getWorldPosition() const
{
    return getWorldTransform()*sf::Vector2f();
}

//Get the global bounding rect of this object
sf::FloatRect SceneNode::getGlobalBounds() const
{
    return sf::FloatRect(0, 0, 0, 0);
}

//Get the world rotation of this object
float SceneNode::getWorldRotation() const
{
    return getRotation() + (parent ? parent->getWorldRotation() : 0);
}

//Rect to a command
void SceneNode::onCommand(Command command, sf::Time dt)
{
    if(command.targetCategory&category)
        command.action(this, dt);

    for(auto ptr : children)
    {
        if(ptr)
            ptr->onCommand(command, dt);
    }
}

//Update function dummy 
void SceneNode::updateCurrent(sf::Time dt)
{
}

//Draw function dummy
void SceneNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
}

//Remove function dummy
bool SceneNode::toRemove()
{
    return false;
}

//Remove all nodes that need to go
void SceneNode::removeNodes()
{
    for(int i = 0; i < children.size(); i++)
    {
        SceneNode * ptr = children[i];
        if(ptr->toRemove())
        {
            delete ptr;
            children.erase(children.begin()+i);
            i--;
        }
    }
    for(auto ptr : children)
        ptr->removeNodes();
}

//Check if a scene node is colliding with another one
bool colliding(SceneNode * obj, SceneNode * node)
{
    return obj->getGlobalBounds().intersects(node->getGlobalBounds());
}

//Get the category of a scene node
unsigned int SceneNode::getCategory()
{
    return category;
}

//Collect collisions
void SceneNode::checkCollision(SceneNode * other, std::set<std::pair<SceneNode*, SceneNode*>>& set)
{
    if(other != this && colliding(this, other))
        set.insert(std::minmax(this, other));

    for(int i = 0; i < children.size(); i++)
        children[i]->checkCollision(other, set);
}

//Collect collisions globally
void SceneNode::collectCollisions(SceneNode * graph, std::set<std::pair<SceneNode*, SceneNode*>>& set)
{
    checkCollision(graph, set);

    for(int i = 0; i < graph->children.size(); i++)
        collectCollisions(graph->children[i], set);
}

//Collide with another scene node
void SceneNode::collide(SceneNode * other)
{
}
