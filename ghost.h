#pragma once
#include "Board.h"

class ghost
{
private:
	Location loc;

public:
	ghost();

	void Respawn(const Location& loc);
	void Draw(Board& board) const;
	const Location& GetLocation() const;
};

