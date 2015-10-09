#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "SceneNode.h"

#include <vector>
#include <SFML/Graphics.hpp>

class Trajectory : public SceneNode
{
    private:

        std::vector<sf::Vector2f> points;

    public:

        Trajectory();
        ~Trajectory();

        void add(sf::Vector2f);

    protected:

        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

};

#endif
