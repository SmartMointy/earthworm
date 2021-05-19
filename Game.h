#pragma once
#include "States.h"

/*
	Game Engine
*/

class Game
{
private:
	// Variables
	std::string title;
	std::string version;
	int window_width;
	int window_height;
	int frame_rate;
	int video_mode;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	sf::RenderWindow* window;
	sf::Event ev;


	// Private methods
	void initVariables();
	void initWindow();
	void initStates();
	void loadConfigs();
public:
	// Constuctor / Deconstructor
	Game();
	virtual ~Game();

	// Methods
	const bool getWindowIsOpen() const;

	void updateDt();
	void updateEvents();
	void update();
	void render();

};

