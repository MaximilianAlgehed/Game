#include "GameplayState.h"

GameplayState::GameplayState(GameStack * stack) : GameState(stack)
{
    loadResources(); 
    buildScene();
}

void GameplayState::update(sf::Time dt)
{
    sceneGraph.update(dt);
}

void GameplayState::handleEvent(sf::Event event)
{
}

void GameplayState::draw(sf::RenderWindow * window)
{
    window->draw(sceneGraph);
}

void GameplayState::buildScene()
{
}

void GameplayState::loadResources()
{
    textureHolder.load(Textures::Destroyer, "Media/Destroyer.png");
}
