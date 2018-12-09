#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "State.h"
#include "GUI_Object.h"

class Button : public GUI_Object
{
public:
	Button(State& state, std::string attackName, sf::Vector2f position);

	void draw() override;
	void update() override;

private:
	std::vector<sf::RectangleShape> shapes;
	sf::Text attack_name;
	int effect_counter;
};