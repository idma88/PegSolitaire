#include "BaseScene.h"

BaseScene::BaseScene()
{
  m_font.loadFromFile("CyrilicOld.ttf");
}

void
BaseScene::TransitionTo(StatesID newState)
{
  Singleton<BaseScene>::GetInstance().TransitionTo(newState);
}

BaseScene::~BaseScene() {}

void
BaseScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{}