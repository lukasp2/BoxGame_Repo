#include "Hero.h"
#include "Game.h"
#include "GUI.h"
#include "Damage_Text.h"
#include "Enemy.h"

Hero::Hero(Game& game, sf::Color color, float size, float speed, std::string name) 
	: Character{ game, size, speed, 100, 1, name, color }, XP{ 0 }, mana{ 100 }, mana_regen{9.22}, health_regen{1.38}
{
	Character::name.setFillColor(sf::Color::Green);
	Character::name.setCharacterSize(20);
	Character::upgrades_avalible = 1;

	body.setPosition(0,200);
	setInnerBodyPos();
}

bool Hero::update(float deltaTime)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		changed_movement = true;
		float mouse_posx = sf::Mouse::getPosition(game.window).x - static_cast<float>(game.window.getSize().x / 2);
		float mouse_posy = sf::Mouse::getPosition(game.window).y - static_cast<float>(game.window.getSize().y / 2);

		seekPosition = sf::Vector2f{ mouse_posx, mouse_posy };
		startPosition = sf::Vector2f{ body.getPosition().x, body.getPosition().y };

		x = 0;
	}
	
	Character::move();


	if (level != 18 && XP >= 100)
	{
		level_up();
	}

	if (mana < 100)
	{
		mana += mana_regen * deltaTime;
	}

	if (health < 100)
	{
		health += health_regen * deltaTime;
 	}

	return health <= 0;
}

void Hero::proccess_input(sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		switch (event.key.code)
		{
		case sf::Keyboard::Q:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
				upgrade_Q();
			else
				Q();
			break;
		case sf::Keyboard::W:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
				upgrade_W();
			else
				W();
			break;
		case sf::Keyboard::E:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
				upgrade_E();
			else
				E();
			break;
		case sf::Keyboard::R:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
				upgrade_R();
			else
				R();
			break;
		}
	default:
		break;
	}
}

void Hero::onCollision(Entity& otherEntity)
{
	if (Enemy* e = dynamic_cast<Enemy*>(&otherEntity))
	{
		damage_char(e->melee_attack());
	}
}

void Hero::damage_char(int damage)
{
	if (damage != 0)
	{
		health -= damage;
		game.user_interface->add(std::make_unique<Damage_Text>(game, std::to_string(damage), sf::Color::Red, body.getPosition()));
	}
}

void Hero::on_kill()
{
	XP += 100 / (3 * level);
	kills++;
}

void Hero::level_up()
{
	level++;
	if (level < 17)
	{
		upgrades_avalible++;
	}

	mana_regen *= 1.2;
	health_regen *= 1.2;

	XP -= 100;
}

bool Hero::can_upgrade(int& ability_level)
{
	if (ability_level != 4 && upgrades_avalible > 0)
	{
		ability_level++;
		upgrades_avalible--;

		return true;
	}

	return false;
}

void Hero::draw_more()
{
	//window.draw(name);
}