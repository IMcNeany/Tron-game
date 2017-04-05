#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <memory>



class Line
{
public:
	Line();
	~Line() = default;
	void CreateLine();
	void setPos(int x, int y);
	int getXPos();
	int getYPos();
	void setRotation(int x);
	bool getAlive();
	void setAlive(bool isalive);
	int getSizeX();
	int getSizeY();
	sf::RectangleShape draw();

private:

	sf::RectangleShape line;
	int xpos = NULL;
	int ypos = NULL;
	bool alive = false;
};