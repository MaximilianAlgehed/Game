#ifndef TEXTNODE_H
#define TEXTNODE_H

#include "SceneNode.h"

#include <SFML/Graphics.hpp>

class TextNode : public SceneNode
{
    public:
        TextNode(std::string, sf::Font, unsigned int, sf::Color);

    protected:
        sf::Font font;
        std::string text;
        unsigned int size;
        sf::Color color;
        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif
