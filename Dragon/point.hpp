#ifndef POINT_HPP
#define POINT_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

class Point 
{
private:
	sf::Vector2f* coords;
public:
	Point();
	Point(double x, double y);
	sf::Vector2f* getCoords();
	sf::Vertex* getVertex();
	void rotate(float angle);
	void setCoords(sf::Vector2f* v);
};

#endif //POINT_HPP