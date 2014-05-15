#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <cmath>
#include <math.h>
#include <sstream>

void rotate(sf::Vertex &v, int deg)
{
	float rad = M_PI * (float)deg / 180.0;
	float prevX = v.position.x;
	float prevY = v.position.y;
	v.position.x = prevX*cos(rad) - prevY*sin(rad);
	v.position.y = prevX*sin(rad) + prevY*cos(rad);
}

void rotateAtPt(sf::Vertex &v, sf::Vector2f p, int deg)
{
	float rad = M_PI * (float)deg / 180.0;
	sf::Vector2f offset = v.position - p;
	float offsetX = offset.x;
	offset.x = offset.x*cos(rad) - offset.y*sin(rad);
	offset.y = offsetX*sin(rad) + offset.y*cos(rad);
	v.position = p + offset;
}

void reverseIterateFractal(std::vector<sf::Vertex> &v)
{
	int num = log2(v.size()) - 1;
	if (v.size() > 2)
	{
		for (int i = 0; i < pow(2, num); i++)
			v.pop_back();
		for (int i = 0; i < v.size(); i++)
		{
			rotateAtPt(v[i], v[0].position, -45);
		}
	}
}

void colorize(std::vector<sf::Vertex> &v, int colors[3])
{
	float step[3];
	for (int i = 0; i < 3; i++)
	{
		step[i] = (float)(colors[i])/v.size();
	}
	for (int i = 0; i < v.size(); i++)
	{
		v[i].color = sf::Color(colors[0] - step[0]*i, colors[1] - step[1]*i, colors[2] - step[2]*i);
	}
}

void iterateFractal(std::vector<sf::Vertex> &points)
{
	std::vector<sf::Vertex> copy;
	for (int i = 0; i < points.size(); i++) //rotate by 45 to maintain orientation
	{
		rotateAtPt(points[i], points[0].position, 45); //may be positive, check later.
	}
	copy = points;
	//std::cout << "Original size: " << points.size() << ", Copy Size: " << copy.size() - 1 << std::endl;
	for (int i = 0; i < copy.size(); i++) //rotate copy 90
	{
		rotateAtPt(copy[i], copy[copy.size()-1].position, 90);
	}
	for (int i = copy.size() - 2; i >= 0; i--) //attach to end, minus the last point
	{
		points.push_back(copy[i]);
	}
}

int main ()
{
	float zoom = 1.0;

	std::vector<sf::Vertex> points;
	std::vector<sf::Vertex> dragon2;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Dragon Fractal Generator");
	sf::View view = window.getDefaultView();
	view.setCenter(window.getSize().x/2, window.getSize().y/2);

	points.push_back(sf::Vertex(sf::Vector2f(window.getSize().x/2, window.getSize().y/2), sf::Color::White)); //initial line
	points.push_back(sf::Vertex(sf::Vector2f(window.getSize().x/2 + 10, window.getSize().y/2), sf::Color::White));

	dragon2.push_back(sf::Vertex(sf::Vector2f(window.getSize().x/2, window.getSize().y/2), sf::Color::White)); //initial line
	dragon2.push_back(sf::Vertex(sf::Vector2f(window.getSize().x/2 - 10, window.getSize().y/2), sf::Color::White));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				iterateFractal(points);
				iterateFractal(dragon2);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				//iterateFractal(dragon2);
				reverseIterateFractal(points);
				reverseIterateFractal(dragon2);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				view.zoom(0.5f);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				view.zoom(2.0f);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				view.move(0, -100);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				view.move(-100, 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				view.move(0, 100);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				view.move(100, 0);
			}
		}
		window.clear();
		//window.draw();
		window.setView(view);
		int colors[3] = {0, 0, 150};
		int c[3] = {240, 0, 0};
		colorize(dragon2, colors);
		colorize(points, c);
		window.draw(&(dragon2[0]), dragon2.size(), sf::LinesStrip);
		window.draw(&(points[0]), points.size(), sf::LinesStrip);
		window.display();
	}
	return 0;
}