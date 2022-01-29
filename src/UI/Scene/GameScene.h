#pragma once

#include "BaseScene.h"

class GameScene : public BaseScene
{
public:
  GameScene();

public:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
