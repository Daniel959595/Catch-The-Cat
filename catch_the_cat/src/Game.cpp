#include "Game.h"

#include <thread>

Game::Game(int numLevels)
    : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Catch the cat!"),
      m_table(11, 11), m_numLevels(numLevels)
{
    setFontAndInfo();
    m_table.setFontAndInfo(m_font);
}

void Game::setFontAndInfo()
{
    m_font.loadFromFile("c:/Windows/Fonts/arial.ttf");
    m_info.setFont(m_font);
    m_info.setCharacterSize(100);
    m_info.setFillColor(sf::Color::Black);
    m_info.setOutlineThickness(3);
    m_info.setOutlineColor(sf::Color{ 255,204,153 });
    m_info.setPosition(20, 40);
}

void Game::runGame()
{
    int level = 1, numToBlock = BASIC_BLOKS;
    Situation situation = Situation::GameBegin;
    displayMessege(level, situation);
    situation = Situation::LevelRunnig;

    while (m_window.isOpen() && level <= m_numLevels)
    {
        displayMessege(level, situation);
        situation = Situation::LevelRunnig;
        m_table.resetTable(numToBlock);
        runLevel(situation);
        if (situation == Situation::LevelSucced)
        {
            level++;
            numToBlock -= 4;
        }    
    }
    situation = Situation::GameFinished;
    displayMessege(level, situation);
}

void Game::displayMessege(int levelIndex, Situation& situation)
{
    using namespace std::chrono_literals;
    
    setInfo(levelIndex, situation);

    m_window.clear();
    m_window.draw(m_info);
    m_window.display();
    std::this_thread::sleep_for(3s);
}

void Game::setInfo(int levelIndex, Situation& situation)
{
    float x, y;
    std::string level(std::to_string(levelIndex));
    std::string messege;

    switch (situation)
    {
    case Situation::GameBegin:     messege = std::string("catch the cat!"); break;
    case Situation::LevelRunnig:   messege = std::string("level number " + level); break;
    case Situation::LevelFailed:   messege = std::string("you faild! try again"); break;
    case Situation::LevelSucced:   messege = std::string("level number " + level); break;
    case Situation::GameFinished:  messege = std::string("see you later!"); break;
    default: break;
    }
    m_info.setString(messege);

    x = (WINDOW_WIDTH - m_info.getGlobalBounds().width) / 2;
    y = (WINDOW_HEIGHT - m_info.getGlobalBounds().height) / 2 - (m_info.getGlobalBounds().height / 2);
    m_info.setPosition(sf::Vector2f(x, y));
}

void Game::runLevel(Situation& situation)
{
    while (m_window.isOpen())
    {
        draw();
        handleEvents(situation);
        if (situation != Situation::LevelRunnig)
            return;
    }
}

void Game::draw()
{
    m_window.clear();
    m_table.draw(m_window);
    m_window.display();
}

void Game::handleEvents(Situation& situation)
{
    if (auto event = sf::Event{}; m_window.waitEvent(event))
    {
        sf::Vector2f location;
        switch (event.type)
        {
            case sf::Event::Closed:
                m_window.close();
                break;

            case sf::Event::MouseButtonReleased:
                location = m_window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
                m_table.handleClick(location, situation);
                break;

        }
    }
}

