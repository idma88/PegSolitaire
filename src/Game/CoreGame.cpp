#include "CoreGame.h"

CoreGame::CoreGame()
{
  /// передаем нашему шрифту файл шрифта
  m_font.loadFromFile("CyrilicOld.ttf");
  /// создаем объект текст. закидываем в объект текст строку, шрифт, размер
  m_text.setCharacterSize(40);
  m_text.setFont(m_font);
  m_text.setColor(sf::Color::Red);
  m_text.setStyle(sf::Text::Bold);
  m_text.setString("Start Game");

  // Выбирем английскую версию
  fld.Create(COMMON::ETypeField::ENGLISH);
  // Создаём список игроков
  std::vector<Player> list_player{ playerOne };

  calculations.Init();
  calculations.CalcOffsetGame(fld.GetWidth(), fld.GetHeight());
  m_test.SetOffsetGame(calculations.offsetGameField);

  // Загрузим список игроков
  singleMode.SetPlayerList(list_player);
  // Загрузим копию поля
  singleMode.SetField(fld);
  // Размер поля
  SIZE.x = fld.GetWidth();
  SIZE.y = fld.GetHeight();

  m_grid.SetSize(calculations.coverSize, calculations.cellSize);
  m_test.SetActiveRect(calculations.activeRect, calculations.cellSize);

  rectField.setSize(
    sf::Vector2f((calculations.cellSize * SIZE.x) - 1, (calculations.cellSize * SIZE.y) - 1));
  rectField.move(calculations.offsetGameField.x, calculations.offsetGameField.y);
  rectField.setFillColor(sf::Color::Transparent);
  rectField.setOutlineColor(sf::Color::White);
  rectField.setOutlineThickness(6.f);

  singleMode.SetField(fld);
  singleMode.CreateNewGame();
}

void
CoreGame::Lounch()
{
  sf::RenderWindow& window = calculations.window;

  sf::Event event;
  while (window.isOpen()) {
    window.clear(sf::Color(9, 133, 205));

    window.draw(m_grid, calculations.gridTr);
    window.draw(m_test, calculations.activeTr);
    window.draw(rectField, calculations.activeTr);

    window.display();

    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::KeyPressed:
          if (event.key.code == sf::Keyboard::Escape) window.close();
          break;
        case sf::Event::MouseButtonPressed:
          if (event.key.code == sf::Mouse::Left) {
            // if(!isBeginMove && )
          }
          break;
        default:
          break;
      }
    }
  }
}