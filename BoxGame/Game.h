#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <fstream>
#include "State.h"
#include "Clock.h"

class GUI;
class Hero;
class Entity;

class Game : public State
{
public:
	Game(sf::RenderWindow& window);
	~Game();

	virtual void	process_input() override;
	virtual State*	update()		override;
	virtual void	render()		override;

	// private
	std::unique_ptr<GUI> user_interface;
	std::shared_ptr<Hero> player;
	std::vector< std::shared_ptr<Entity> > entities;
	//

	Clock getClock() { return system_clock; }

private:
	//flytta ut som hj�lpfunktioner ist
	void read_settings();
	void read_options();
	void read_spawns();
	bool level_complete();

	sf::Clock frame_clock{};
	float deltaTime{};
	
	Clock system_clock{};
	
	sf::Clock spawn_clock{};
	std::ifstream spawn_stream;
	int next_spawn;
	void spawn_enemy();
	
	struct Options
	{
		bool pause{ false };
		bool quit{ false };
		bool gameover{ false };
	};
	Options option{};

	struct Controls
	{
		Controls() : Q{ 16 }, W{ 22 }, E{ 4 }, R{ 17 }, LAlt{ 39 } {}
		int Q;
		int W;
		int E;
		int R;
		int LAlt;
	};

	struct Settings
	{
		bool display_healthbar;
	};
};