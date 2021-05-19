#pragma once
#include "Location.h"

class Board
{
private:
	sf::Texture backgroundTexture;
	sf::Sprite background;
	sf::Texture foodTexture;
	sf::Sprite food;
	sf::Texture poisonTexture;
	sf::Sprite poison;
	sf::Texture ghostTexture;
	sf::Sprite ghost;
	sf::Texture SnekHeadTexture;
	sf::Sprite SnekHead;
	sf::Texture SnekTailTexture;
	sf::Sprite SnekTail;
	
	sf::RenderTarget* window;
	float dimension = 20;
	float width = 40;
	float height = 30;

public:
	Board(sf::RenderTarget* target);

	void DrawCell( const Location& loc, sf::Color c );
	void DrawSnekHead(const Location& loc, std::string dir);
	void DrawSnekTail(const Location& loc, std::string dir);
	void DrawFood(const Location& loc);
	void DrawPoison(const Location& loc);
	void DrawGhost(const Location& loc);
	bool IsInsideBoard(const Location& loc) const;

	void render(sf::RenderTarget* target);
};

