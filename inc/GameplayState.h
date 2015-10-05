#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "Textures.h"
#include "GameState.h"
#include "SceneNode.h"

#include <array>

class GameplayState : public GameState
{
    private:

        enum SceneLayer
        {
            Background,
            Foreground,
            LayerCount
        };

        SceneNode sceneGraph;
        std::array<SceneNode*, LayerCount> sceneLayers;
        ResourceHolder<sf::Texture, Textures::ID> textureHolder;

        void loadResources();
        void buildScene();

    public:
        GameplayState(GameStack * stack);

        virtual void update(sf::Time dt);
        virtual void handleEvent(sf::Event event);
        virtual void draw(sf::RenderWindow* window);
};

#endif
