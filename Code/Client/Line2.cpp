#include "Line2.h"

//pass in position of the car and rotation
Line2::Line2()
{

	line.setOrigin(sf::Vector2f(12, 25));
	line.setSize(sf::Vector2f(25, 50));
	line.setPosition(sf::Vector2f(-10, 0));
	line.setFillColor(sf::Color::Magenta);
	alive = false;

}

void Line2::CreateLine()
{

	line.setOrigin(sf::Vector2f(1, 2.5));
	line.setSize(sf::Vector2f(2, 4));
	line.setFillColor(sf::Color::Cyan);
	alive = false;

}

void Line2::setPos(int x, int y)
{
	line.setPosition(sf::Vector2f(x, y));
	xpos = x;
	ypos = y;


}


int Line2::getXPos()
{

	return xpos;
}

int Line2::getYPos()
{
	return ypos;
}

void Line2::setRotation(int x)
{
	line.setRotation(x);
}

void Line2::setAlive(bool isalive)
{
	alive = isalive;
}

bool Line2::getAlive()
{
	return alive;
}

sf::RectangleShape Line2::draw()
{
	return line;
}

int Line2::getSizeX()
{
	return line.getSize().x;
}

int Line2::getSizeY()
{
	return line.getSize().y;
}