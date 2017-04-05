#pragma once

#include <future>
#include <iostream>
#include <string>

#include <SFML/Network.hpp>
#include <Game/MessageTypes.h>
class Game;

class Client
{
public:
	Client();
	~Client() = default;
	using TcpClient = sf::TcpSocket;
	using TcpClientPtr = std::unique_ptr<TcpClient>;
	using TcpClients = std::vector<TcpClientPtr>;

	void Start();
	bool connect(TcpClient&);
	void receive(TcpClients& tcp_clients, sf::SocketSelector& selector);
	//void packets();
	void send(TcpClient&);
	void input(TcpClient&);
	void listen(sf::TcpListener& tcp_listener, sf::SocketSelector& selector, TcpClients& tcp_clients);

private:

};

