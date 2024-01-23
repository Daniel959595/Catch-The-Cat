#include "Vertex.h"
#include <iostream>

Vertex::Vertex(const sf::Vector2f& position, int index, bool isEdge)
	: m_position(position), m_index(index), m_isEdge(isEdge), m_SourceDistance(0), m_parent(NULL)
{
    m_circle.setPosition(m_position);
    m_circle.setFillColor(m_shapeColor);
}

void Vertex::draw(sf::RenderWindow& window)
{
    window.draw(m_circle);
}

bool Vertex::handleClick(const sf::Vector2f& clickLocation)
{
    if (m_circle.getGlobalBounds().contains(clickLocation))
    {
        m_shapeColor = sf::Color{ 204,102,1, };
        m_circle.setFillColor(m_shapeColor);
        m_isBlocked = true;
        return true;
    }
    return false;
}

void Vertex::addNeighbor(Vertex* v)
{
    m_neighbors.push_back(v);
}

void Vertex::resetBfs()
{
    m_color = Color::white;
    m_SourceDistance = DEFUALT_DISTANCE;
    m_parent = NULL;
}

std::vector<Vertex*> Vertex::getNeighbors()
{
    return m_neighbors;
}

void Vertex::setIsBlocked(bool flag)
{
    m_isBlocked = flag;
    if (flag) {
        m_shapeColor = sf::Color{ 204,102,1, };
        m_circle.setFillColor(m_shapeColor);
    }
    else {
        m_shapeColor = sf::Color{ 255,204,153 };
        m_circle.setFillColor(m_shapeColor);
    }
}

bool Vertex::isBlocked() const
{
    return m_isBlocked;
}

bool Vertex::isEdge() const
{
    return m_isEdge;
}

Color Vertex::GetColor() const
{
    return m_color;
}

void Vertex::markAsVisited(Vertex* v)
{
    m_color = Color::gray;
    m_SourceDistance = v->getSourceDistance() + 1;
    m_parent = v;
}

int Vertex::getSourceDistance() const
{
    return m_SourceDistance;
}

void Vertex::setSourceDistance(int distance) 
{
    m_SourceDistance = distance;
}

Vertex* Vertex::getParent()
{
    return m_parent;
}

sf::Vector2f Vertex::getPosition() const
{
    return m_position;
}
