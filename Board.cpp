#include "Board.h"

Board::Board( sf::RenderTarget* target )
{
	this->window = target;

	if (!foodTexture.loadFromFile("Images/apple.png", sf::IntRect(0, 0, 20, 20)))
	{
		// error...
	}
	food.setTexture(foodTexture, true);

	if (!poisonTexture.loadFromFile("Images/poison.png", sf::IntRect(0, 0, 20, 20)))
	{
		// error...
	}
	poison.setTexture(poisonTexture, true);

	if (!ghostTexture.loadFromFile("Images/ghost.png", sf::IntRect(0, 0, 20, 20)))
	{
		// error...
	}
	ghost.setTexture(ghostTexture, true);

	if (!backgroundTexture.loadFromFile("Images/background.png", sf::IntRect(0, 0, 800, 600)))
	{
		// error...
	}
	background.setTexture(backgroundTexture, true);
	background.setPosition(sf::Vector2f(0.f, 0.f));

	if (!SnekHeadTexture.loadFromFile("Images/head.png", sf::IntRect(0, 0, 20, 20)))
	{
		// error...
	}
	SnekHead.setTexture(SnekHeadTexture, true);
	SnekHead.setOrigin(10.f, 10.f);
	SnekHead.setRotation(90.f);

	if (!SnekTailTexture.loadFromFile("Images/tail.png", sf::IntRect(0, 0, 20, 20)))
	{
		// error...
	}
	SnekTail.setTexture(SnekTailTexture, true);
	SnekTail.setOrigin(10.f, 10.f);
	SnekTail.setRotation(90.f);
}

void Board::DrawCell( const Location& loc, sf::Color c )
{
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(dimension, dimension));
	shape.setPosition(sf::Vector2f(loc.x * dimension, loc.y * dimension));
	shape.setFillColor(sf::Color(138, 101, 83));
	this->window->draw(shape);
}

void Board::DrawSnekHead(const Location& loc, std::string dir)
{
	if (dir == "up")
	{
		SnekHead.setRotation(0.f);
	}
	else if (dir == "down")
	{
		SnekHead.setRotation(180.f);
	}
	else if (dir == "left")
	{
		SnekHead.setRotation(270.f);
	}
	else if (dir == "right")
	{
		SnekHead.setRotation(90.f);
	}
	SnekHead.setPosition(sf::Vector2f((loc.x * dimension) + 10.f, (loc.y * dimension) + 10.f));

	this->window->draw(SnekHead);
}

void Board::DrawSnekTail(const Location& loc, std::string dir)
{
	if (dir == "up")
	{
		SnekTail.setRotation(0.f);
	}
	else if (dir == "down")
	{
		SnekTail.setRotation(180.f);
	}
	else if (dir == "left")
	{
		SnekTail.setRotation(270.f);
	}
	else if (dir == "right")
	{
		SnekTail.setRotation(90.f);
	}
	SnekTail.setPosition(sf::Vector2f((loc.x * dimension)+ 10.f, (loc.y * dimension) +10.f));

	this->window->draw(SnekTail);
}

void Board::DrawFood(const Location& loc)
{
	food.setPosition(sf::Vector2f(loc.x * dimension, loc.y * dimension));
	this->window->draw(food);
}

void Board::DrawPoison(const Location& loc)
{
	poison.setPosition(sf::Vector2f(loc.x * dimension, loc.y * dimension));
	this->window->draw(poison);
}

void Board::DrawGhost(const Location& loc)
{
	ghost.setPosition(sf::Vector2f(loc.x * dimension, loc.y * dimension));
	this->window->draw(ghost);
}

bool Board::IsInsideBoard(const Location& loc) const
{
	return loc.x >= 0 && loc.x < width &&
		loc.y >= 0 && loc.y < height;
}

void Board::render(sf::RenderTarget* target)
{
	 this->window->draw(background);
}
