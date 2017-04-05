#include "Game.h"
#include <Windows.h>
#include "GameState.h"


bool Game::init()
{
	std::make_unique<Line>();
	std::make_unique<Line2>();
	//std::make_unique<Client>();
	//player1	
	rectangle1.setSize(sf::Vector2f(10, 15));
	rectangle1.setOrigin(sf::Vector2f(5, 7.5));
	rectangle1.setFillColor(sf::Color::Magenta);
	rectangle1.setOutlineColor(sf::Color::Red);
	rectangle1.setOutlineThickness(2);
	rectangle1.setPosition(100, 200);

	//player 2
	rectangle2.setSize(sf::Vector2f(10, 15));
	rectangle2.setOrigin(sf::Vector2f(5, 7.5));
	rectangle2.setFillColor(sf::Color::Cyan);
	rectangle2.setOutlineColor(sf::Color::Blue);
	rectangle2.setOutlineThickness(2);
	rectangle2.setPosition(1000, 200);

	//clear things to reset the game
	lineVector.clear();
	lineVector2.clear();
	numberStoredLine = 0;
	numberStoredLine2 = 0;
	winner = "NULL";
	firstRun = true;
	startTime = 0;
	startTime2 = 0;
	currentTime = 0;
	currentTime2 = 0;

	//create lines
	lineVector.reserve(500);
	for (int i = 0; i < 500; i++)
	{
		lineVector.push_back(Line());

		lineVector[i].CreateLine();
	}

	lineVector2.reserve(500);
	for (int i = 0; i < 500; i++)
	{
		lineVector2.push_back(Line2());

		lineVector2[i].CreateLine();
	}
	//main menu assets
	//play button 
	play.setSize(sf::Vector2f(250, 125));
	play.setFillColor(sf::Color::White);
	play.setPosition(450, 100);

	quit.setSize(sf::Vector2f(250, 125));
	quit.setFillColor(sf::Color::White);
	quit.setPosition(450, 400);

	//Load in font
	if (!font.loadFromFile("neuropol.ttf"))
	{
		return false;
	}
	//text for play screen
	text.setFont(font);
	text.setString("Play");
	text.setFillColor(sf::Color::Blue);
	text.setPosition(460, 120);
	text.setCharacterSize(72);

	menuquit.setFont(font);
	menuquit.setString("Quit");
	menuquit.setFillColor(sf::Color::Blue);
	menuquit.setPosition(470, 420);
	menuquit.setCharacterSize(72);

	//loading screen
	waiting.setFont(font);
	waiting.setString("Waiting for clients to connect");
	waiting.setFillColor(sf::Color::Blue);
	waiting.setPosition(460, 120);
	waiting.setCharacterSize(72);

	//Gameover screen
	gameOver.setFont(font);
	gameOver.setString("Game Over");
	gameOver.setFillColor(sf::Color::Blue);
	gameOver.setPosition(300, 200);
	gameOver.setCharacterSize(72);

	player1.setFont(font);
	player1.setString("Player 1 Wins");
	player1.setFillColor(sf::Color::Blue);
	player1 .setPosition(300, 300);
	player1.setCharacterSize(72);

	player2.setFont(font);
	player2.setString("Player 2 Wins");
	player2.setFillColor(sf::Color::Blue);
	player2.setPosition(300, 300);
	player2.setCharacterSize(72);

	returnMainMenu.setFont(font);
	returnMainMenu.setString("Press Enter");
	returnMainMenu.setFillColor(sf::Color::Blue);
	returnMainMenu.setPosition(300, 500);
	returnMainMenu.setCharacterSize(72);
	return true;
}

void Game::keyPress(sf::Event isevent, sf::RenderWindow* window)
{
	//set timers
	currentTime = GetTickCount() - startTime;
	currentTime2 = GetTickCount() - startTime2;

	//close when esc is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		//set event to close
		//why does this not work?
		isevent.type = sf::Event::Closed;
		window->close();
	}

	//for clicking the play button
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && gameState == GameState::MainMenu)
	{
		// left click...
		if (sf::Mouse::getPosition().x >= (play.getPosition().x + 70) && sf::Mouse::getPosition().x <= (play.getPosition().x + 350))
		{
			if (sf::Mouse::getPosition().y >= (play.getPosition().y + 100) && sf::Mouse::getPosition().y <= (play.getPosition().y + 240))
			{
				//gameState = GameState::connecting;
				init();
				gameState = GameState::Game;
			}
		}
	}

	//for clicking the exit button
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && gameState == GameState::MainMenu)
	{
		// left click...
		if (sf::Mouse::getPosition().x >= (quit.getPosition().x + 70) && sf::Mouse::getPosition().x <= (quit.getPosition().x + 350))
		{
			if (sf::Mouse::getPosition().y >= (quit.getPosition().y + 100) && sf::Mouse::getPosition().y <= (quit.getPosition().y + 240))
			{

				isevent.type = sf::Event::Closed;
				window->close();
			}
		}
	}

//A is pressed
	//if (getPlayerTag() ==0)
	//{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && gameState == GameState::Game && rectangle1.getPosition().x > 0
			|| lastKeyPressed == "A" && gameState == GameState::Game && rectangle1.getPosition().x > 0)
		{
			lastKeyPressed = "A";
			//move character left
			rectangle1.move(sf::Vector2f(-1.5, 0));
			rectangle1.setRotation(90);

			//check enough time has passed
			if (currentTime >= 350)
			{
				//position of line 
				numberStoredLine++;
				lineVector[numberStoredLine].setPos((rectangle1.getPosition().x + 5), rectangle1.getPosition().y);
				lineVector[numberStoredLine].setRotation(rectangle1.getRotation());
				lineVector[numberStoredLine].setAlive(true);

				startTime = GetTickCount();
			}
		}


	//}
	//if (getPlayerTag() == 1)
	//{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && gameState == GameState::Game && rectangle2.getPosition().x > 0
			|| lastKeyPressed2 == "left" && gameState == GameState::Game && rectangle2.getPosition().x > 0)
			//stop multiple keys being pressed at the same time
		{
			lastKeyPressed2 = "left";
			rectangle2.move(sf::Vector2f(-1.5, 0));
			rectangle2.setRotation(90);

			//check enough time has passed
			if (currentTime2 >= 350)
			{
				numberStoredLine2++;
				lineVector2[numberStoredLine2].setPos((rectangle2.getPosition().x + 5), rectangle2.getPosition().y);
				lineVector2[numberStoredLine2].setRotation(rectangle2.getRotation());
				lineVector2[numberStoredLine2].setAlive(true);
				//reset timer
				startTime2 = GetTickCount();
			}
		}
		
//	}
	//D pressed
	//if (getPlayerTag() == 0)
	//{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && gameState == GameState::Game && rectangle1.getPosition().x < 1200
			|| lastKeyPressed == "D" && gameState == GameState::Game && rectangle1.getPosition().x < 1200)
		{
			lastKeyPressed = "D";
			//move character right
			rectangle1.move(sf::Vector2f(1.5, 0));
			rectangle1.setRotation(-90);
			if (currentTime >= 350)
			{
				//add line
				numberStoredLine++;
				lineVector[numberStoredLine].setPos((rectangle1.getPosition().x - 5), rectangle1.getPosition().y);
				lineVector[numberStoredLine].setRotation(rectangle1.getRotation());
				lineVector[numberStoredLine].setAlive(true);

				//reset timer
				startTime = GetTickCount();
			}

		}
	//}
	//if(getPlayerTag() == 1)
	//{ 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && gameState == GameState::Game && rectangle2.getPosition().x < 1200
			|| lastKeyPressed2 == "right" && gameState == GameState::Game && rectangle2.getPosition().x < 1200)
		{
			lastKeyPressed2 = "right";
			rectangle2.move(sf::Vector2f(1.5, 0));
			rectangle2.setRotation(-90);

			//check enough time has passed
			if (currentTime2 >= 350)
			{
				numberStoredLine2++;
				lineVector2[numberStoredLine2].setPos((rectangle2.getPosition().x - 5), rectangle2.getPosition().y);
				lineVector2[numberStoredLine2].setRotation(rectangle2.getRotation());
				lineVector2[numberStoredLine2].setAlive(true);

				//reset timer
				startTime2 = GetTickCount();
			}

		}
	//}
	//W is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && gameState == GameState::Game && rectangle1.getPosition().y > 0
		|| lastKeyPressed == "W" && gameState == GameState::Game && rectangle1.getPosition().y > 0 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::W) && gameState == GameState::Game && rectangle2.getPosition().y > 0
		|| lastKeyPressed == "W" && gameState == GameState::Game && rectangle2.getPosition().y > 0)
	{
		lastKeyPressed = "W";
		//move character up
		rectangle1.move(sf::Vector2f(0, -1.5));
		rectangle1.setRotation(0);


		//check enough time has passed
		if (currentTime >= 350)
		{
			//add line 
			numberStoredLine++;
			lineVector[numberStoredLine].setPos(rectangle1.getPosition().x, (rectangle1.getPosition().y + 5));
			lineVector[numberStoredLine].setRotation(rectangle1.getRotation());
			lineVector[numberStoredLine].setAlive(true);

			

			//rest timer
			startTime = GetTickCount();
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && gameState == GameState::Game && rectangle2.getPosition().y > 0
		|| lastKeyPressed2 == "up" && gameState == GameState::Game && rectangle2.getPosition().y > 0)
	{

		lastKeyPressed2 = "up";
		rectangle2.move(sf::Vector2f(0, -1.5));
		rectangle2.setRotation(0);

		//check enough time has passed
		if (currentTime2 >= 350)
		{
		
			//player 2
			numberStoredLine2++;
			lineVector2[numberStoredLine2].setPos(rectangle2.getPosition().x, (rectangle2.getPosition().y + 5));
			lineVector2[numberStoredLine2].setRotation(rectangle2.getRotation());
			lineVector2[numberStoredLine2].setAlive(true);

			//rest timer
			startTime2 = GetTickCount();
		}
	}
	//S is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && gameState == GameState::Game && rectangle1.getPosition().y < 600
		|| lastKeyPressed == "S"&& gameState == GameState::Game && rectangle1.getPosition().y < 600)
	{
		lastKeyPressed = "S";
		//move character down
		rectangle1.move(sf::Vector2f(0, 1.5));
		rectangle1.setRotation(180);

		//check enough time has passed
		if (currentTime >= 350)
		{
			//add the line
			numberStoredLine++;
			lineVector[numberStoredLine].setPos(rectangle1.getPosition().x, (rectangle1.getPosition().y - 5));
			lineVector[numberStoredLine].setRotation(rectangle1.getRotation());
			lineVector[numberStoredLine].setAlive(true);


			//reset timer
			startTime = GetTickCount();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && gameState == GameState::Game && rectangle2.getPosition().y < 600
		|| lastKeyPressed2 == "down"&& gameState == GameState::Game && rectangle2.getPosition().y < 600)
	{
		lastKeyPressed2 = "down";

		rectangle2.move(sf::Vector2f(0, 1.5));
		rectangle2.setRotation(180);
		//check enough time has passed
		if (currentTime2 >= 350)
		{

			//if player 2
			numberStoredLine2++;
			lineVector2[numberStoredLine2].setPos(rectangle2.getPosition().x, (rectangle2.getPosition().y - 5));
			lineVector2[numberStoredLine2].setRotation(rectangle2.getRotation());
			lineVector2[numberStoredLine2].setAlive(true);

			//reset timer
			startTime2 = GetTickCount();
		}
	}
	//retrun is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && gameState == GameState::MainMenu)
	{
		//game starts
		init();
		gameState = GameState::Game;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && gameState == GameState::GameOver)
	{
		gameState = GameState::MainMenu;
		//init();
	}
}

void Game::update(sf::RenderWindow* window)
{

	//changes game states
	if (gameState == GameState::MainMenu)
	{
		UpdateMainMenu(window);
	}

	else if (gameState == GameState::connecting)
	{
		LoadingScreen(window);
	}

	else if (gameState == GameState::Game)
	{
		UpdateGame(window);
	}

	else if (gameState == GameState::GameOver)
	{
		UpdateGameOver(window);
	}

}

void Game::UpdateMainMenu(sf::RenderWindow* window)
{
	window->draw(play);
	window->draw(text);
	window->draw(quit);
	window->draw(menuquit);
}

void Game::UpdateGame(sf::RenderWindow* window)
{
	//sets the first movement
	if (firstRun == true)
	{
		//if it is too close to the top it will go the other way
		if (rectangle1.getPosition().y < 200 || rectangle2.getPosition().y < 200)
		{
			lastKeyPressed = "S";
			lastKeyPressed2 = "dowm";
		}
		//otherwise it will head up the screen
		else
		{
			lastKeyPressed = "W";
			lastKeyPressed2 = "up";
		}
		firstRun = false;
	}

	//if the player goes off the screen they die
	if (rectangle1.getPosition().x > 1200 || rectangle1.getPosition().x < 0
		|| rectangle1.getPosition().y < 0 || rectangle1.getPosition().y > 600)
	{
		//player dies
		winner = "Player2";
		lastKeyPressed = "NULL";
		gameState = GameState::GameOver;
	}

	//if the player goes off the screen they die
	if (rectangle2.getPosition().x > 1200 || rectangle2.getPosition().x < 0
		|| rectangle2.getPosition().y < 0 || rectangle2.getPosition().y > 600)
	{
		winner = "Player1";
		//player dies
		lastKeyPressed = "NULL";
		gameState = GameState::GameOver;
	}


	//if the player collides with anything they die
	CollisionCheck();
	window->draw(rectangle1);
	window->draw(rectangle2);

	for (int i = 0; i < numberStoredLine; i++)
	{
		window->draw(lineVector[i].draw());
	}

	for (int i = 0; i < numberStoredLine2; i++)
	{
		window->draw(lineVector2[i].draw());
	}

}

void Game::UpdateGameOver(sf::RenderWindow* window)
{

	window->draw(gameOver);
	window->draw(returnMainMenu);

	if (winner == "Player1")
	{
		window->draw(player1);
	}

	if (winner == "Player2")
	{
		window->draw(player2);
	}

}

void Game::CollisionCheck()
{
	//collsion pink car with pink line
	for (int i = 0; i < numberStoredLine; i++)
	{
		if ((rectangle1.getPosition().x + rectangle1.getSize().x) >= lineVector[i].getXPos() && rectangle1.getPosition().x <= (lineVector[i].getXPos() + lineVector[i].getSizeX())
			&& (rectangle1.getPosition().y + rectangle1.getSize().y) >= lineVector[i].getYPos() && rectangle1.getPosition().y <= (lineVector[i].getYPos() + lineVector[i].getSizeY()))
		{
			winner = "Player2";
			lastKeyPressed = "NULL";
			gameState = GameState::GameOver;

		}

	}

	//collision blue car with pink line
	for (int i = 0; i < numberStoredLine; i++)
	{
		if ((rectangle2.getPosition().x + rectangle2.getSize().x) >= lineVector[i].getXPos() && rectangle2.getPosition().x <= (lineVector[i].getXPos() + lineVector[i].getSizeX())
			&& (rectangle2.getPosition().y + rectangle2.getSize().y) >= lineVector[i].getYPos() && rectangle2.getPosition().y <= (lineVector[i].getYPos() + lineVector[i].getSizeY()))
		{
			winner = "Player1";
			lastKeyPressed = "NULL";
			gameState = GameState::GameOver;

		}
	}
	//pink car with blue line
	for (int i = 0; i < numberStoredLine2; i++)
	{
		if ((rectangle1.getPosition().x + rectangle1.getSize().x) >= lineVector2[i].getXPos() && rectangle1.getPosition().x <= (lineVector2[i].getXPos() + lineVector2[i].getSizeX())
			&& (rectangle1.getPosition().y + rectangle1.getSize().y) >= lineVector2[i].getYPos() && rectangle1.getPosition().y <= (lineVector2[i].getYPos() + lineVector2[i].getSizeY()))
		{

			winner = "Player2";
			lastKeyPressed = "NULL";
			gameState = GameState::GameOver;

		}

	}

	//blue car with blue line
	for (int i = 0; i < numberStoredLine2; i++)
	{
		if ((rectangle2.getPosition().x + rectangle2.getSize().x) >= lineVector2[i].getXPos() && rectangle2.getPosition().x <= (lineVector2[i].getXPos() + lineVector2[i].getSizeX())
			&& (rectangle2.getPosition().y + rectangle2.getSize().y) >= lineVector2[i].getYPos() && rectangle2.getPosition().y <= (lineVector2[i].getYPos() + lineVector2[i].getSizeY()))
		{
			winner = "Player1";
			lastKeyPressed = "NULL";
			gameState = GameState::GameOver;

		}

	}
	//pink car with blue car
	if ((rectangle1.getPosition().x + rectangle1.getSize().x) >= rectangle2.getPosition().x && (rectangle1.getPosition().x <= (rectangle2.getPosition().x + rectangle2.getSize().x))
		&& (rectangle1.getPosition().y + rectangle1.getSize().y) >= rectangle2.getPosition().y && rectangle1.getPosition().y <= (rectangle2.getPosition().y + rectangle2.getSize().y))
	{
		winner = "Player2";
		lastKeyPressed = "NULL";
		gameState = GameState::GameOver;

	}

	//blue car with pink car
	if ((rectangle2.getPosition().x + rectangle2.getSize().x) >= rectangle1.getPosition().x && (rectangle2.getPosition().x <= (rectangle1.getPosition().x + rectangle1.getSize().x))
		&& (rectangle2.getPosition().y + rectangle2.getSize().y) >= rectangle1.getPosition().y && rectangle2.getPosition().y <= (rectangle1.getPosition().y + rectangle1.getSize().y))
	{
		winner = "Player1";
		lastKeyPressed = "NULL";
		gameState = GameState::GameOver;

	}

	//if(A.x +A.width >= b.x && A.x <= B.x +B.width && A.y +A height >= B.Y && A.Y <= B.Y +B.Heght)

}

void Game::SetPlayerTag(int num)
{
	playerTag = num;
}

int Game::getGameState()
{
	if (gameState == GameState::MainMenu)
	{
		return 0;
	}
	if (gameState == GameState::connecting)
	{
		return 1;
	}
	if (gameState == GameState::Game)
	{
		return 2;
	}

	if (gameState == GameState::GameOver)
	{
		return 3;
	}
}

void Game::setPlayer1PosX(int posx, int posy)
{
	rectangle1.setPosition(posx, posy);
}

void Game::setPlayer2PosX(int pos, int posy)
{
	rectangle2.setPosition(pos, posy);
}

void Game::Line2Pos(int x, int y)
{
	lineVector2[numberStoredLine2].setPos(x, y);
}

void Game::Line1Pos(int x, int y)
{
	lineVector[numberStoredLine].setPos(x, y);
}

void Game::LoadingScreen(sf::RenderWindow* window)
{
	window->draw(waiting);
}
