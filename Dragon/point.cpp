#include "point.hpp"

Point::Point()
{
	coords->x = 0;
	coords->y = 0;
}

Point::Point(double x, double y)
{
	coords->x = x;
	coords->y = y;
}

sf::Vector2f* Point::getCoords()
{
	return coords;
}

sf::Vertex* getVertex()
{
	return new sf::Vertex(coords);
}

void rotate(double angle)
{
	double rad = angle * PI / 180.0;
	prevX = coords->x;
	coords->x = coords->x*cos(rad) - coords->y*sin(rad);
	coords->y = prevX*sin(rad) + coords->y*cos(rad);
}

void Point::setCoords(sf::Vector2f* v)
{
	coords = v;
}

