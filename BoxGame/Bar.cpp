#include "Bar.h"

Bar::Bar(Game& game, sf::Vector2f position, sf::Vector2f size, sf::Color color)
	: GUI_Object{ game }
{
	bar.setSize(size);
	bar.setPosition(position);
	bar.setFillColor(color);

	edge.setSize(size);
	edge.setPosition(position);
	edge.setFillColor(sf::Color::Transparent);
	edge.setOutlineColor(sf::Color(60,60,60));
	edge.setOutlineThickness(1.0f);
}

void Bar::draw()
{
	game.window.draw(bar);
	game.window.draw(edge);
}

