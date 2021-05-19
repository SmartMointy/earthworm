#pragma once
#include "ghost.h"

class Poison
{
private:
	Location loc;

public:
	Poison();

	void Respawn(const Location& loc);
	void Draw(Board& board) const;
	const Location& GetLocation() const;
};

