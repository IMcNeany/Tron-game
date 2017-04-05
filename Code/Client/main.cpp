#include <SFML/Graphics.hpp>
#include "ClientSide.h"
#include <memory>
#include "Game.h"

int main()
{
	std::unique_ptr<Client>client;
	std::unique_ptr<Game>game = std::make_unique<Game>();

	game->init();
	sf::RenderWindow window(sf::VideoMode(1200, 600), "Tron game");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	//sf::CircleShape shape(100.f);
	//shape.setPosition(sf::Vector2f(100, 200));
	//shape.setFillColor(sf::Color::Green);
	client->Start();

	while (window.isOpen())
	{
		
		sf::Event isevent;
		while (window.pollEvent(isevent))
		{
			if (isevent.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear();
		
		game->keyPress(isevent, &window);
		
		game->update(&window);
		window.display();
	
		
	}

	return 0;
}