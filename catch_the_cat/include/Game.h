#pragma once

#include "Table.h"
#include "Utilities.h"

class Game {
public:
	Game(int numLevels);

	void setFontAndInfo();
	void runGame();
	void displayMessege(int levelIndex, Situation& situation);
	void setInfo(int levelIndex, Situation& situatio);
	void runLevel(Situation& situation);
	void draw();
	void handleEvents(Situation& situation);

private:
	Table m_table;

	sf::RenderWindow m_window;
	sf::Text m_info;
	sf::Font m_font;
	
	int m_numLevels;
};