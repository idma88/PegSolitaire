#pragma once

#include "../../Utils/Singletone.h"
#include "BaseScene.h"
#include "GameScene.h"
#include "MenuScene.h"

class BaseScene;
class RunUPState;
class StandbyState;

class StateScene
{
  friend class Singleton<StateScene>;

  friend class BaseScene;

private:
  StateScene();

public:
  std::shared_ptr<BaseScene> GetCurrentState() const;

  void TransitionTo(StatesID newState);

private:
  /// Указатель на текущее состояние
  std::shared_ptr<BaseScene> m_current;

  /// Указатель на состояние Подготовка
  std::shared_ptr<MenuScene> m_menuScene;
  /// Указатель на состояние Дежурного режима
  std::shared_ptr<GameScene> m_gameScene;
};