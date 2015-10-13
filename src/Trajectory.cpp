#include "Trajectory.h"

void Trajectory::add(sf::Vector2f point)
{
     points.push_back(point);
}

void Trajectory::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
    if(points.size() == 0)
        return;
    for(int i = 0; i < points.size()-1; i++)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(points[i]),
            sf::Vertex(points[i+1])
        };
        target.draw(line, 2, sf::Lines);
    }
}

void Trajectory::clear()
{
    points.clear();
}
