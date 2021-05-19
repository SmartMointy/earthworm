#include "Game.h"

void Game::initVariables()
{
	this->title = "Rainbow";
	this->version = "0.0.1";
	this->window_width = 800;
	this->window_height = 600;
	this->frame_rate = 30;

	this->window = nullptr;
}

void Game::initWindow()
{
	this->loadConfigs();

	sf::VideoMode video_mode(this->window_width, this->window_height);
	std::string window_title = this->title + " v" + this->version;
	
	this->window = new sf::RenderWindow(video_mode, window_title, sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(this->frame_rate);
}

void Game::initStates()
{
	this->states.push(new GameState(this->window, &this->states));
	this->states.push(new MainMenu(this->window, &this->states));
}

void Game::loadConfigs()
{
	std::ifstream ifs("configs.ini");

	if (ifs.is_open())
	{
		std::getline(ifs, this->title);
		ifs >> this->version;
		ifs >> this->window_width >> this->window_height;
		ifs >> this->frame_rate;
	}

	ifs.close();
}

// Constuctor / Deconstructor

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

// Methods

const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateEvents()
{
	// Events
	while (this->window->pollEvent(this->ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}

}

void Game::update()
{
	this->updateEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			delete this->states.top();
			this->states.pop();
		}
	}
	else
	{
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();
	
	// Draw Content
	if (!this->states.empty())
	{
		this->states.top()->render();
	}

	this->window->display();
}
