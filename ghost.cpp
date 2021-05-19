#include "ghost.h"

ghost::ghost()
	:loc{0,0}
{
}

void ghost::Respawn(const Location& at_loc)
{
	loc = at_loc;
}

void ghost::Draw(Board& board) const
{
	board.DrawGhost(loc);
}

const Location& ghost::GetLocation() const
{
	return loc;
}