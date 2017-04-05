#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include<SFML\Window.hpp>
#include <string>
#include <vector>
#include <memory>
#include "Line.h"
#include "Line2.h"
#include "ClientSide.h"

class Client;
class Line;

class Game
{
public:
	Game() = default;
	~Game() = default;

	void keyPress(sf::Event event, sf::RenderWindow* window);
	bool init();
	void update(sf::RenderWindow* window);

	void UpdateMainMenu(sf::RenderWindow* window);
	void UpdateGame(sf::RenderWindow* window);
	void UpdateGameOver(sf::RenderWindow* window);
	void LoadingScreen(sf::RenderWindow* window);
	void CollisionCheck();

	void SetPlayerTag(int num);
	int getPlayerTag(){ return playerTag; }
	int getGameState();

	int getPlayer1PosX() { return rectangle1.getPosition().x; }
	void setPlayer1PosX(int pos, int posy);
	int getPlayer1PosY() { return rectangle1.getPosition().y; }
	//void setPlayer1PosY(int pos);


	int getPlayer2PosX() { return rectangle2.getPosition().x; }
	void setPlayer2PosX(int pos, int posy);
	int getPlayer2PosY() { return rectangle2.getPosition().y; }
	//void setPlayer2PosY(int pos);

	int line1Length() { return numberStoredLine; }
	int line2Length() { return numberStoredLine2; }

	int Line1X() { return lineVector[numberStoredLine].getXPos(); }
	int Line1Y() { return lineVector[numberStoredLine].getYPos(); }


	int Line2X() { return lineVector2[numberStoredLine2].getXPos(); }
	int Line2Y() { return lineVector2[numberStoredLine2].getYPos(); }

	void Line2Pos(int x, int y);
	void Line1Pos(int x, int y);

private:
	//doubles for time
	double startTime;
	double currentTime;
	//doubles for time
	double startTime2;
	double currentTime2;

	//rect for player 1
	sf::RectangleShape rectangle1;
	//rect for player 2
	sf::RectangleShape rectangle2;



	//vector for lines
	std::vector<Line> lineVector;
	std::vector<Line2> lineVector2;

	//playscreen  buttons
	sf::RectangleShape play;
	sf::RectangleShape quit;

	//std::unique_ptr<Client>client;
	

	//text
	sf::Font font;
	sf::Text waiting;
	sf::Text text;
	sf::Text gameOver;
	sf::Text menuquit;
	sf::Text returnMainMenu;
	sf::Text player1;
	sf::Text player2;

	//store the last key pressed by the player
	std::string lastKeyPressed;
	std::string lastKeyPressed2;

	//win player
	std::string winner;
	//number of lines 
	int numberStoredLine = 0;
	int numberStoredLine2 = 0;
	int playerTag;
	bool firstRun = true;
};
