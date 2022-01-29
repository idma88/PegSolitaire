#include "StateScene.h"

StateScene::StateScene()
{
  // Выделение ресурсов
  m_menuScene = std::make_shared<MenuScene>();
  m_gameScene = std::make_shared<GameScene>();

  m_current = m_menuScene;
}

std::shared_ptr<BaseScene>
StateScene::GetCurrentState() const
{
  return m_current;
}

void
StateScene::TransitionTo(StatesID newState)
{
  switch (newState) {
    case StatesID::MenuScene:
      m_current = std::static_pointer_cast<BaseScene>(m_menuScene);
      break;
    case StatesID::GameScene:
      m_current = std::static_pointer_cast<BaseScene>(m_gameScene);
      break;
    default:
      return;
  }
}