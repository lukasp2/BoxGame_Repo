#include "Button.h"
#include "Hero.h"
#include "Timed_Text.h"
#include "GUI.h"

#include <iostream>

Button::Button(Game& game, std::string attackName, sf::Vector2f position, ability* a, sf::Keyboard::Key key)
	: GUI_Object{ game }, a{ a }, key { key }
{
	// the big box
	sf::RectangleShape big_box;
	big_box.setSize(sf::Vector2f(40, 40));
	big_box.setPosition(position.x, position.y);
	big_box.setFillColor(sf::Color(15,15,15));
	big_box.setOutlineColor(sf::Color(30,30,30));
	big_box.setOutlineThickness(1.0f);
	shapes.push_back(big_box);

	// the visualeffect of the cooldown
	sf::RectangleShape cd_box;
	cd_box.setSize(sf::Vector2f(38, 38));
	cd_box.setPosition(position.x + 1, position.y + 1);
	cd_box.setFillColor(sf::Color(15,15,15)); // set to 35,35,35
	shapes.push_back(cd_box);

	// the smaller boxes
	for (int i{}; i < 4; ++i)
	{
		sf::RectangleShape small_box;
		small_box.setSize(sf::Vector2f(5, 5));
		small_box.setPosition( position.x + 2 + i * 10, position.y + big_box.getSize().y - 7);
		small_box.setFillColor(sf::Color::Black);
		small_box.setOutlineColor(sf::Color::White);
		small_box.setOutlineThickness(1.0f);
		shapes.push_back(small_box);
	}

	// the text
	attack_name.setFont(game.courier_font);
	attack_name.setCharacterSize(18);
	attack_name.setPosition(sf::Vector2f(position.x + big_box.getSize().x / 2 - 13, position.y + big_box.getSize().y / 2 - 20));
	attack_name.setString(attackName);

	mana_costs.setFont(game.courier_font);
	mana_costs.setCharacterSize(10);
	mana_costs.setPosition(sf::Vector2f(position.x + big_box.getSize().x - 13, position.y + 2));
	mana_costs.setString(std::to_string(a->mana_cost));
}

void Button::draw()
{
	for (auto&& shape : shapes)
	{
		game.window.draw(shape);
	}

	game.window.draw(attack_name);
	game.window.draw(mana_costs);
}

bool Button::update()
{
	if (game.player->upgrades_avalible > 0)
	{
		// set outline color
	}

	if (option.upgrade)
	{
		option.upgrade = false;
		shapes[a->level + 1].setFillColor(sf::Color::Yellow);
		shapes[0].setOutlineColor(sf::Color(120, 100, 0));
	}

	if (option.upgrade_unavalible)
	{
		option.upgrade_unavalible = false;
		shapes[0].setOutlineColor(sf::Color::Red);
	}

	if (game.player->mana < a->mana_cost)
	{
		option.mana_too_low = false;
		shapes[0].setOutlineColor(sf::Color(90, 0, 0));
	}

	//update cooldown thingy

	mana_costs.setString(std::to_string(a->mana_cost));

	return false;
}

void Button::proccess_input(sf::Event event)
{	
	shapes[0].setOutlineColor(sf::Color(30, 30, 30));

	if (sf::Keyboard::isKeyPressed(key) && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
		if (game.player->upgrades_avalible > 0 && a->level < 4)
		{
			option.upgrade = true;
		}

		else if (game.player->upgrades_avalible < 2 || a->level == 4)
		{
			option.upgrade_unavalible = true;
		}
	}

	else if (sf::Keyboard::isKeyPressed(key))
	{ 
		if (game.player->mana >= a->mana_cost) // && a->cooldown_count == 0 // sf::Time cooldown_count;
		{
			shapes[0].setOutlineColor(sf::Color(100, 100, 100));
			option.use = true;
		}

		//else if (game.player->mana < a->mana_cost)
		{
		//		option.mana_too_low = true;
		}
	}
}
/*
void Button::upgrade_avalible()
{

}
*/