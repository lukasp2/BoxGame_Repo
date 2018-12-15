#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>

#include "State.h"

class Menu : public State
{
public:
	virtual void process_input() = 0;
	virtual State* update() = 0;
	virtual void render() = 0;

	void moveUp();
	void moveDown();

	virtual void moveRight() {};
	virtual void moveLeft() {};

protected:
	Menu(sf::RenderWindow& window) : State{ window } {}

	sf::Text header; //"Main Menu", "Game Paused", "Highscore" etc..
	
	std::vector<sf::Text> textVector;	
	int selection{ 0 };
};

