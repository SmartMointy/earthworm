#include "Poison.h"

Poison::Poison()
{
}

void Poison::Respawn(const Location& at_loc)
{
	loc = at_loc;
}

void Poison::Draw(Board& board) const
{
	board.DrawPoison(loc);
}

const Location& Poison::GetLocation() const
{
	return loc;
}
