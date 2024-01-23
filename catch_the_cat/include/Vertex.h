#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"

enum class Color {
	white, 
	gray,
};

class Vertex {
public:
	Vertex(const sf::Vector2f& position, int index, bool isEdge);

	void draw(sf::RenderWindow& window);
	bool handleClick(const sf::Vector2f& clickLocation);
	void addNeighbor(Vertex* v);

	void markAsVisited(Vertex* v);
	void resetBfs();

	std::vector<Vertex*> getNeighbors();

	void setIsBlocked(bool flag);
	bool isBlocked() const;
	bool isEdge() const;
	Color GetColor() const;

	int  getSourceDistance() const;
	void setSourceDistance(int distance);
	Vertex* getParent();
	sf::Vector2f getPosition() const;

private:
	sf::CircleShape m_circle{ 40, 100 };
	sf::Vector2f m_position;
	sf::Color m_shapeColor = sf::Color{ 255,204,153 };

	int  m_index;
	int  m_SourceDistance;
	bool m_isBlocked = false, m_isEdge;
	Vertex* m_parent;

	std::vector<Vertex*> m_neighbors;
	Color m_color = Color::white;

};