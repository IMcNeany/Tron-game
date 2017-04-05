#include "Line.h"

//pass in position of the car and rotation
Line::Line()
{

	line.setOrigin(sf::Vector2f(12, 25));
	line.setSize(sf::Vector2f(25, 50));
	line.setPosition(sf::Vector2f(-10, 0));
	line.setFillColor(sf::Color::Magenta);
	alive = false;


}

void Line::CreateLine()
{
	

	line.setOrigin(sf::Vector2f(1, 2.5));
	line.setSize(sf::Vector2f(2, 4));
	line.setFillColor(sf::Color::Magenta);
	alive = false;

	/*line.setOrigin(sf::Vector2f(12, 25));
	line.setSize(sf::Vector2f(25, 30));
	line.setFillColor(sf::Color::Cyan);
	alive = false;*/
}

void Line::setPos(int x, int y)
{
	line.setPosition(sf::Vector2f(x, y));
	xpos = x;
	ypos = y;


}


int Line::getXPos()
{

	return xpos;
}

int Line::getYPos()
{
	return ypos;
}

void Line::setRotation(int x)
{
	line.setRotation(x);
}

void Line::setAlive(bool isalive)
{
	alive = isalive;
}

bool Line::getAlive()
{
	return alive;
}

sf::RectangleShape Line::draw()
{
	return line;
}

int Line::getSizeX()
{
	return line.getSize().x;
}

int Line::getSizeY()
{
	return line.getSize().y;
}