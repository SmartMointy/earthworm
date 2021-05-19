#pragma once
#include "Player.h"

class State
{
protected:
	sf::RenderWindow* window;
	std::vector<sf::Texture*> textures;
	bool quit;

	std::stack<State*>* states;

public:
	State(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;

	virtual void checkForQuit();

	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

class MainMenu :
	public State
{
private:
	sf::RectangleShape background;

public:
	MainMenu(sf::RenderWindow* target, std::stack<State*>* states);
	~MainMenu();

	void checkForQuit();

	// Methods
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

class GameState :
    public State
{
private:
    Player player;
    Board board;
    Location delta_loc = { 1,0 };
    std::mt19937 rng;
    ghost ghost;
    Goal goal;
    Poison poison;
    const Location RandomLoc();
    static constexpr int  movePeriod = 10;
    int moveCounter = 0;
    bool gameIsOver = false;
    bool isGhost = false;
    bool nextStepPlanned = false;
    std::string dir = "right";
    std::string gameOverMessage = "You died! :(";
    sf::Font font;

public:
    GameState(sf::RenderWindow* window, std::stack<State*>* states);
    virtual ~GameState();

    // Methods
    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    void showGhostMessage();
    void showGameOverMessage();
};
