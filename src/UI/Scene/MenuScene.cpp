#include "MenuScene.h"

MenuScene::MenuScene()
  : BaseScene()
{
  m_menu_str.push_back("Start game");
  m_menu_str.push_back("Edit");
  m_menu_str.push_back("Save");
  m_menu_str.push_back("Help");
  m_menu_str.push_back("Exit");
}

void
MenuScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  sf::Text text;
  text.setFont(m_font);
  text.setCharacterSize(40);
  text.setOutlineColor(sf::Color::White);
  text.setOutlineThickness(2);
  text.setColor(sf::Color::Red);
  text.setStyle(sf::Text::Bold);

  for (int countStr = 0; countStr < m_menu_str.size(); ++countStr) {
    text.setString(m_menu_str[countStr]);
    text.setPosition(m_calculations.offsetGameField.x,
                     m_calculations.offsetGameField.y + countStr * m_calculations.cellSize);
    target.draw(text, states);
  }
}