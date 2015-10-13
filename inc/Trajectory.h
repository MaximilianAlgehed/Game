#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "SceneNode.h"

#include <vector>
#include <SFML/Graphics.hpp>

class Trajectory : public SceneNode
{
    private:

        //Points in the trajectory, relative to it's origin
        std::vector<sf::Vector2f> points;

    public:

        //Add a point to the trajectory
        void add(sf::Vector2f);
        //Clear the trajecory
        void clear();

    protected:

        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

};

#endif
