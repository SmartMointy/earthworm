#pragma once
#include "Poison.h"

class Goal
{
private:
	Location loc;

public:
	Goal();

	void Respawn( const Location& loc);
	void Draw(Board& board) const;
	const Location& GetLocation() const;
};

