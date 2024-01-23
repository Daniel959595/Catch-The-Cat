#include "Table.h"

#include <time.h>

// creating and initializing all the vertices, posting the cat.
Table::Table(int cols, int rows) : m_cols(cols), m_rows(rows), m_playerFaild(false)
{
	float index = 0, x, y;
	bool edge;

	for (int i = 0; i < rows; i++) {
		std::vector<Vertex> vec;
		for (int j = 0; j < cols; j++) {
			x = (WINDOW_WIDTH - (m_cols * SHAPE_WIDTH)) / 2 + (j * SHAPE_WIDTH);
			y = (WINDOW_HEIGHT - (m_rows * SHAPE_HEIGHT)) / 2 + (i* SHAPE_HEIGHT);

			(i == 0 || i == (rows - 1) || j == 0 || j == (cols - 1) ? edge = true : edge = false);  
			(i % 2 != 0 ? x += SHAPE_WIDTH / 2 : x = x);     

			vec.push_back(Vertex(sf::Vector2f(x, y), int(index++), edge));
		}
		m_vertices.push_back(vec);
	}
	resetCat(true);
	setNeighbors(rows, cols);
}

void Table::setFontAndInfo(sf::Font& font)
{
	m_font = font;
	m_info.setFont(m_font);
	m_info.setCharacterSize(40);
	m_info.setFillColor(sf::Color::Black);
	m_info.setOutlineThickness(2);
	m_info.setOutlineColor(sf::Color{ 255,204,153 });
	m_info.setPosition(20, 40);
}

void Table::resetCat(bool firstTime)
{
	if (firstTime) {
		m_infoure.loadFromFile("cat.png");
		m_cat = sf::Sprite(m_infoure);
	}
	m_catSpot = &(m_vertices[5][5]);
	m_cat.setPosition(m_catSpot->getPosition());
}

// set the neighbors of every vertex.
void Table::setNeighbors(int rows, int cols)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			addNeighbors(i, j);
		}
}

void Table::addNeighbors(int row, int col)
{
	int num;
	row % 2 == 0 ? num = -1 : num = 1;
		
	checkAndAdd(row, col, row, col - 1);        // left.
	checkAndAdd(row, col, row, col + 1);        // right.
	checkAndAdd(row, col, row - 1, col);        // up.
	checkAndAdd(row, col, row + 1, col);        // down.
	checkAndAdd(row, col, row - 1, col + num);  // up and right\left.
	checkAndAdd(row, col, row + 1, col + num);  // down and right\left.
}

void Table::checkAndAdd(int indexRow, int indexCol, int x, int y)
{
	if (isVertexExist(x, y))           
		m_vertices[indexRow][indexCol].addNeighbor(&(m_vertices[x][y]));
}

bool Table::isVertexExist(int i, int j) const
{
	if (i < 0 || i >= m_rows || j < 0 || j >= m_cols)
		return false;
	return true;
}

void Table::resetTable(int numToBlock)
{
	for (int i = 0; i < m_vertices.size(); i++)
		for (int j = 0; j < m_vertices[i].size(); j++)
		{
			m_vertices[i][j].resetBfs();
			m_vertices[i][j].setIsBlocked(false);
		}
	resetCat(false);
	if (m_playerFaild)
		reloadLevel();
	else
		blockSpots(numToBlock);
	m_numSteps = 0;
}

void Table::reloadLevel()
{
	for (auto& v : m_level) {
		v->setIsBlocked(true);
	}
}

void Table::blockSpots(int numToBlock)
{
	srand(unsigned(time(NULL)));
	int i = 0, index1, index2;

	m_level.clear();
	while (i++ < numToBlock) {
		index1 = rand() % m_cols;
		index2 = rand() % m_rows;

		if (&m_vertices[index1][index2] == &(*m_catSpot))
			i--;
		else {
			m_vertices[index1][index2].setIsBlocked(true);
			m_level.push_back(&(m_vertices[index1][index2]));
		}
	}
}

void Table::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_vertices.size(); i++)
		for (auto& v : m_vertices[i])
		{
			v.draw(window);
		}
	setInfo();
	window.draw(m_info);
	window.draw(m_cat);
}

void Table::setInfo()
{
	std::string text("steps: ");
	std::string num(std::to_string(m_numSteps));
	m_info.setString(text + num);
}

void Table::handleClick(const sf::Vector2f& location, Situation& situation)
{
	for (auto& vector : m_vertices)
		for (auto& vertex : vector)
		{
			if (!vertex.isBlocked() && vertex.handleClick(location))
			{
				moveCat(situation);
				m_numSteps++;
			}
		}
}

void Table::moveCat(Situation& situation)
{
	m_catSpot = getDirection(m_catSpot);
	m_cat.setPosition(m_catSpot->getPosition());
	if (m_catSpot->isEdge()) {
		situation = Situation::LevelFailed;
		m_playerFaild = true;
	}
	else if (isCatCaptured()) {
		situation = Situation::LevelSucced;
		m_playerFaild = false;
	}
}

Vertex* Table::getDirection(Vertex* source) 
{
	BFS(source);
	if (!isCatFramed())        // there is a path to the edge.
		return trackBFSTrail();
	else
		return dummyDirection(source);
}

void Table::BFS(Vertex* source)
{
	resetBFS();
	std::vector<Vertex*> queue;  
	queue.push_back(source);

	Vertex* vertex;
	std::vector<Vertex*> neighborsList; 
	for (int i = 0; i < queue.size(); i++)
	{
		vertex = queue[i];
		neighborsList = vertex->getNeighbors();
		for (auto& neighbor : neighborsList)
		{
			if (!neighbor->isBlocked() && neighbor->GetColor() == Color::white 
				                          && &(*neighbor) != &(*source))
			{
				neighbor->markAsVisited(vertex);
				queue.push_back(neighbor);
			}
		}
	}
}

void Table::resetBFS()
{
	for (int i = 0; i < m_vertices.size(); i++)
		for (int j = 0; j < m_vertices[i].size(); j++)
			m_vertices[i][j].resetBfs();
}

Vertex* Table::trackBFSTrail() 
{
	Vertex* dest = getClosetEdge();
	Vertex* temp = dest;

	while (temp->getSourceDistance() > 0) {
		temp = temp->getParent();
	}
	return temp;
}

Vertex* Table::dummyDirection(Vertex* source) const
{
	std::vector<Vertex*> neighbors = source->getNeighbors();

	for (auto& neighbor : neighbors)
	{
		if (!neighbor->isBlocked())
			return neighbor;
	}
	return source;         // there is nowhere to go.
}

bool Table::isCatCaptured() const
{
	std::vector<Vertex*> neighbors = m_catSpot->getNeighbors();

	for (int i = 0; i < neighbors.size(); i++)
		if (!neighbors[i]->isBlocked())
			return false;

	return true;
}

bool Table::isCatFramed() const
{
	for (int i = 0; i < m_vertices.size(); i++)
		for (int j = 0; j < m_vertices[i].size(); j++)
			if (m_vertices[i][j].isEdge() && m_vertices[i][j].getSourceDistance() != DEFUALT_DISTANCE)
				return false;
	return true;
}

Vertex* Table::getClosetEdge() 
{
	int distance = 121; 
	Vertex* dest = NULL;

	for (int i = 0; i < m_vertices.size(); i++)
		for (int j = 0; j < m_vertices[i].size(); j++)
			if (m_vertices[i][j].isEdge() && m_vertices[i][j].getSourceDistance() < distance
				&& !m_vertices[i][j].isBlocked() && m_vertices[i][j].getSourceDistance() != DEFUALT_DISTANCE)
			{
				distance = m_vertices[i][j].getSourceDistance();
				dest = &(m_vertices[i][j]);
			}
	return dest;
}









