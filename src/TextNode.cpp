#include "TextNode.h"

TextNode::TextNode(std::string text, sf::Font font, unsigned int size, sf::Color color) : text(text), font(font), size(size), color(color)
{
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Text textObj = sf::Text(text, font, size);
    textObj.setColor(color);
    target.draw(textObj, states);
}
