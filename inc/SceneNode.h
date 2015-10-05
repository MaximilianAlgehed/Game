#ifndef SCENENODE_H
#define SCENENODE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

class SceneNode : public sf::Transformable, public sf::Drawable
{
    public:
        SceneNode();
        ~SceneNode();
        void attachChild(SceneNode *);
        SceneNode* detachChild(const SceneNode&);

    private:
        SceneNode* parent;
        std::vector<SceneNode*> children;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    protected:
        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif