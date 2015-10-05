#include "SceneNode.h"

SceneNode::SceneNode() : parent(NULL)
{
}

SceneNode::~SceneNode()
{
    for(auto ptr : children)
        delete ptr;
}

void SceneNode::attachChild(SceneNode* child)
{
    child->parent = this;
    this->children.push_back(child);
}

SceneNode* SceneNode::detachChild(const SceneNode& node)
{
    std::vector<SceneNode*>::iterator it = children.begin();
    do
    {
        if(*it == &node)
            break;
        it++; 
    } while(it != children.end());
    SceneNode * found = *it;
    children.erase(it);
    return found;
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    drawCurrent(target, states);
    for(auto ptr : children)
        ptr->draw(target, states);
}

void SceneNode::update(sf::Time dt)
{
    updateCurrent(dt);
    for(auto ptr : children)
        ptr->update(dt);
}

sf::Transform SceneNode::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;

    transform *= getTransform();

    for(SceneNode * node = this->parent; node != NULL; node = node->parent)
        transform *= node->getTransform();

    return transform;
}

void SceneNode::updateCurrent(sf::Time dt)
{
}

void SceneNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
}
