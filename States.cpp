#include "States.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
	this->window = window;
	this->states = states;
	this->quit = false;
}

State::~State()
{
}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->quit = true;
	}
}

void State::update(const float& dt)
{
}

void State::render(sf::RenderTarget* target)
{
}

const Location GameState::RandomLoc()
{
	std::uniform_int_distribution<int> xDist(0, 40 - 1);
	std::uniform_int_distribution<int> yDist(0, 30 - 1);

	Location newLoc;

	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (player.IsInTile(newLoc));

	return newLoc;
}

GameState::GameState(sf::RenderWindow* win, std::stack<State*>* states)
	:
	State(win, states),
	board(win),
	player({ 12, 3 }),
	goal(),
	poison(),
	ghost()
{
	if (font.loadFromFile("arial.ttf"))
	{
		// Error...
	}

	player.Grow();
	player.MoveBy(delta_loc);
	player.Grow();
	player.MoveBy(delta_loc);
	goal.Respawn(RandomLoc());
	poison.Respawn(RandomLoc());
	ghost.Respawn(RandomLoc());
}

GameState::~GameState()
{
}

void GameState::updateInput(const float& dt)
{

	this->checkForQuit();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		this->states->push(new GameState(this->window, this->states));
		this->quit = true;

	}

	if (!gameIsOver)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && dir != "right" && nextStepPlanned == false)
		{
			dir = "left";
			player.setDir(dir);
			delta_loc = { -1,0 };
			nextStepPlanned = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && dir != "left" && nextStepPlanned == false)
		{
			dir = "right";
			player.setDir(dir);
			delta_loc = { 1,0 };
			nextStepPlanned = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && dir != "down" && nextStepPlanned == false)
		{
			dir = "up";
			player.setDir(dir);
			delta_loc = { 0,-1 };
			nextStepPlanned = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && dir != "up" && nextStepPlanned == false)
		{
			dir = "down";
			player.setDir(dir);
			delta_loc = { 0,1 };
			nextStepPlanned = true;
		}

		++moveCounter;
		if (moveCounter >= movePeriod)
		{

			nextStepPlanned = false;

			const Location next = player.GetNextHeadLocation(delta_loc);
			if (!board.IsInsideBoard(next))
			{
				gameIsOver = true;
			}
			else
			{
				if (next == ghost.GetLocation()) {
					isGhost = true;
					ghost.Respawn(RandomLoc());
				}


				if (player.IsInTileExpectEnd(next)) {
					if (isGhost)
					{
						isGhost = false;
					}
					else {
						gameIsOver = true;
					}
				}


				const bool eat = next == goal.GetLocation();
				if (eat)
				{
					player.Grow();
				}
				if (next == poison.GetLocation()) {
					if (isGhost)
					{
						isGhost = false;
					}
					else {
						if (player.GetSegmentsCount() == 2)
						{
							gameIsOver = true;
							gameOverMessage = "You died from the poison!";
						}
						else {
							player.Shrink();
							poison.Respawn(RandomLoc());
						}
					}
				}

				moveCounter = 0;
				player.MoveBy(delta_loc);
				if (eat)
				{
					goal.Respawn(RandomLoc());
				}
			}
		}
	}
}

void GameState::update(const float& dt)
{
	this->updateInput(dt);

	this->player.update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	this->board.render(target);
	this->goal.Draw(board);
	this->poison.Draw(board);
	this->ghost.Draw(board);
	this->player.render(board);

	if (isGhost)
	{
		showGhostMessage();
	}

	if (gameIsOver)
	{
		sf::Text gameOverText;
		gameOverText.setFillColor(sf::Color::Red);
		gameOverText.setOutlineColor(sf::Color::White);
		gameOverText.setCharacterSize(80);
		gameOverText.setString("GAME OVER!");

		gameOverText.setFont(font);

		sf::FloatRect textRect = gameOverText.getLocalBounds();
		gameOverText.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		gameOverText.setPosition(sf::Vector2f(800 / 2.0f, 600 / 2.0f));

		sf::RectangleShape background;
		float width = textRect.width + 100.f;
		float height = textRect.height + 150.f;

		background.setSize(sf::Vector2f(width, height));
		background.setPosition(sf::Vector2f((800 / 2.0f) - (width / 2.f), (600 / 2.0f) - (height / 2.f) + 30.f));
		sf::Color col(0, 0, 0, 150);
		background.setFillColor(col);

		this->window->draw(background);
		this->window->draw(gameOverText);
		showGameOverMessage();
	}
}

void GameState::showGhostMessage()
{
	sf::Text ghostText;
	ghostText.setFillColor(sf::Color::Red);
	ghostText.setCharacterSize(20);
	ghostText.setString("Ghost");

	ghostText.setFont(font);
	ghostText.setPosition(sf::Vector2f(10.f, 5.f));

	sf::RectangleShape background;
	background.setSize(sf::Vector2f(75.f, 35.f));
	background.setPosition(sf::Vector2f(0, 0));
	sf::Color col(0, 0, 0, 150);
	background.setFillColor(col);

	this->window->draw(background);
	this->window->draw(ghostText);
}

void GameState::showGameOverMessage()
{
	sf::Text gameOverText;
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setOutlineColor(sf::Color::White);
	gameOverText.setCharacterSize(30);
	gameOverText.setString(gameOverMessage);
	gameOverText.setStyle(sf::Text::Bold);
	gameOverText.setFont(font);

	sf::FloatRect textRect = gameOverText.getLocalBounds();
	gameOverText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	gameOverText.setPosition(sf::Vector2f(800 / 2.0f, 380.f));

	this->window->draw(gameOverText);
}


MainMenu::MainMenu(sf::RenderWindow* window, std::stack<State*>* states)
	: State(window, states)
{
	this->window = window;
	this->background.setFillColor(sf::Color::White);
	this->background.setSize(sf::Vector2f(800.f, 600.f));
}

MainMenu::~MainMenu()
{
}

void MainMenu::checkForQuit()
{
}

void MainMenu::updateInput(const float& dt)
{
	this->checkForQuit();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		this->quit = true;
	}
}

void MainMenu::update(const float& dt)
{
	this->updateInput(dt);
}

void MainMenu::render(sf::RenderTarget* target)
{
	this->window->draw(this->background);

	sf::Text text;
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color::Black);
	text.setCharacterSize(30);
	text.setString("Press Space to enjoy the game!");

	sf::Font font;
	if (font.loadFromFile("arial.ttf"))
	{
		// Error...
	}

	text.setFont(font);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(800 / 2.0f, 600 / 2.0f));

	this->window->draw(text);
}