#pragma once

#include "BaseScene.h"

class MenuScene : public BaseScene
{
public:
  MenuScene();

public:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
  std::vector<std::string> m_menu_str;
};
