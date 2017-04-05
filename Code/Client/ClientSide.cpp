#include "ClientSide.h"
#include<Server\stdafx.h>
#include<Server\targetver.h>
#include <string>
#include "Game.h"
#include <vector>
#include <memory>

class  Game;

const sf::IpAddress SERVER_IP("127.0.0.1");
constexpr int SERVER_TCP_PORT(53000);
constexpr int SERVER_UDP_PORT(53001);

void Client::Start()
{
	TcpClient socket;
	if (!connect(socket))
	{
		return;
	}

/*	auto handle = std::async(std::launch::async, [&]
	{
		// keep track of the socket status
		sf::Socket::Status status;
		do
		{
		
					sf::Packet packet;
					status = socket.receive(packet);
				
			if (status == sf::Socket::Done)
			{
				int header = 0;
				packet >> header;

				NetMsg msg = static_cast<NetMsg>(header);
				if (msg == NetMsg::CHAT)
				{
					std::string str;
					packet >> str;
					std::cout << "< " << str << std::endl;
				}
				else if (msg == NetMsg::PING)
				{
					sf::Packet pong;
					pong << NetMsg::PONG;
					socket.send(pong);
				}
			}
		} while (status != sf::Socket::Disconnected);

	});
	sf::TcpListener tcp_listener;

	sf::SocketSelector selector;
	selector.add(tcp_listener);

	TcpClients tcp_clients;

	//return listen(tcp_listener, selector, tcp_clients);*/
}


void Client::listen(sf::TcpListener& tcp_listener, sf::SocketSelector& selector, TcpClients& tcp_clients)
{
	while (true)
	{
		const sf::Time timeout = sf::Time(sf::milliseconds(250));
		if (selector.wait(timeout))
		{

			receive(tcp_clients, selector);

		}
	}
}

void Client::send(TcpClient &socket)
{
	sf::Packet packet;
	std::unique_ptr<Game> main = std::make_unique<Game>();
	if (main->getGameState() == 2)
	{
		if (main->getPlayerTag() == 0)
		{

			int GS1 = main->getGameState();
			int P1X = main->getPlayer1PosX();
			int P1Y = main->getPlayer1PosY();
			int L1X = main->Line1X();
			int L1Y = main->Line1Y();

			packet << GS1 << P1X << P1Y << L1X << L1Y;

			socket.send(packet);
		}

		if (main->getPlayerTag() == 1)
		{

			int GS2 = main->getGameState();
			int P2X = main->getPlayer2PosX();
			int P2Y = main->getPlayer2PosY();
			int L2X = main->Line2X();
			int L2Y = main->Line2Y();

			packet << GS2 << P2X << P2Y << L2X << L2Y;

			socket.send(packet);
		}
	}
}

void Client::input(TcpClient &socket)
{
	while (true)
	{
		//taking input from a chat line
		std::string input;
		std::getline(std::cin, input);

		sf::Packet packet;
		packet << NetMsg::CHAT << input;
		socket.send(packet);
	}
}



bool Client::connect(TcpClient& socket)
{
	auto status = socket.connect(SERVER_IP, SERVER_TCP_PORT);
	if (status != sf::Socket::Done)
	{
		return false;
	}

	std::cout << "Connected to server: " << SERVER_IP << std::endl;

	int num = 5;
	int noClients = 0;
	sf::Packet packet;

	socket.receive(packet);
	packet >> noClients >> num;

	std::cout << "< " << noClients << std::endl;
	std::unique_ptr<Game> main = std::make_unique<Game>();
	main->SetPlayerTag(num);


	socket.setBlocking(false);
	return true;
}

void Client::receive(TcpClients& tcp_clients, sf::SocketSelector& selector)
{
	TcpClient socket;
	sf::Socket::Status status;
	sf::Packet packet;
	status = socket.receive(packet);

	std::unique_ptr<Game> main = std::make_unique<Game>();

	if (main->getPlayerTag() == 0)
	{

		int GS2;
		int P2X;
		int P2Y;
		int L2X;
		int L2Y;

		packet >> GS2 >> P2X >> P2Y >> L2X >> L2Y;

		main->setPlayer2PosX(P2X, P2Y);
		main->Line2Pos(L2X, L2Y);
	}

	if (main->getPlayerTag() == 1)
	{
		int GS1;
		int P1X;
		int P1Y;
		int L1X;
		int L1Y;

		packet >> GS1 >> P1X >> P1Y >> L1X >> L1Y;

		main->setPlayer1PosX(P1X, P1Y);
		main->Line1Pos(L1X, L1Y);
	}

}

