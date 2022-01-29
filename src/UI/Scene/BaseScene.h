#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "../../Field/Field.h"
#include "../../Game/SingleMode.h"
#include "../../Utils/Singletone.h"
#include "../Calculations.h"

enum class StatesID
{
  MenuScene,
  GameScene
};

class StateScene;

class BaseScene : public sf::Drawable
{
public:
  BaseScene();
  virtual ~BaseScene();

public:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
  void TransitionTo(StatesID newState);

protected:
  Calculations& m_calculations = Singleton<Calculations>::GetInstance();
  Field& m_field = Singleton<SingleMode>::GetInstance().GetField();

  sf::Font m_font;
};