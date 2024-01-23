#pragma once

#include "Vertex.h"
#include "Utilities.h"

class Table {
public:
	Table(int cols, int rows);

	void setFontAndInfo(sf::Font& font);
	void resetTable(int numToBlock);
	void blockSpots(int numToBlock);
	void draw(sf::RenderWindow& window);
	void handleClick(const sf::Vector2f& location, Situation& situation);
	void setInfo();
	void reloadLevel();
	void resetCat(bool firstTime);
	void setNeighbors(int row, int col);
	void addNeighbors(int row, int col);
	void checkAndAdd(int indexRow, int indexCol, int x, int y);
	bool isVertexExist(int i, int j) const;

	void moveCat(Situation& situation);
	bool isCatCaptured() const;
	bool isCatFramed() const;
	void resetBFS();
	Vertex* getDirection(Vertex* source);
	void    BFS(Vertex* source);            // executing BFS algorithm on the given source vertex. 
	Vertex* trackBFSTrail();                // track the shortest path to the closet edge and return the first step.

	Vertex* dummyDirection(Vertex* source) const; // in case that there is no path to the edge.
	Vertex* getClosetEdge();                // return the closet edge to the source.

private:
	int  m_cols, m_rows, m_numSteps = 0;
	bool m_playerFaild;

	sf::Text m_info;
	sf::Font m_font;

	sf::Texture m_infoure;
	sf::Sprite m_cat;
	Vertex* m_catSpot;

	std::vector<std::vector<Vertex>> m_vertices;

	std::vector<Vertex*> m_level;           // represent the original blocked vertex in the level.
};