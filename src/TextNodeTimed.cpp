#include "TextNodeTimed.h"

TextNodeTimed::TextNodeTimed(std::string text, sf::Font font, unsigned int size, sf::Color color, sf::Time timeout)
    : TextNode(text, font, size, color),
    timeout(timeout)
{
}

bool TextNodeTimed::toRemove()
{
    return timeout == sf::Time::Zero;
}

void TextNodeTimed::updateCurrent(sf::Time dt)
{
    if(timeout < dt)
        timeout = sf::Time::Zero;
    else
        timeout -= dt;
}
