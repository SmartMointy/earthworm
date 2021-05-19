#include "Goal.h"

Goal::Goal()
{
}

void Goal::Respawn(const Location& at_loc)
{
	loc = at_loc;
}

void Goal::Draw(Board& board) const
{
	board.DrawFood(loc);
}

const Location& Goal::GetLocation() const
{
	return loc;
}
