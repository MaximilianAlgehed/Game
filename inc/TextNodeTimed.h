#ifndef TEXTNODETIMED_H
#define TEXTNODETIMED_H

#include "TextNode.h"

class TextNodeTimed : public TextNode
{
    public:
        TextNodeTimed(std::string, sf::Font, unsigned int, sf::Color, sf::Time timout);

        virtual bool toRemove(); 

        void destroy();

    protected:
        sf::Time timeout;

        virtual void updateCurrent(sf::Time dt);
};

#endif
