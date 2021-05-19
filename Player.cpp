#include "Player.h"

Player::Player(const Location& loc)
{
	segments[0].initHead(loc);
}

Player::~Player()
{
}

Location Player::GetNextHeadLocation(const Location& delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

void Player::MoveBy(const Location& delta_loc)
{
	for (int i = nSegments - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}

	segments[0].MoveBy(delta_loc);
}

void Player::Grow()
{
	if ( nSegments < nSegmentsMax)
	{
		segments[nSegments].initBody();
		nSegments++;
	}
}

void Player::Shrink()
{
	if (nSegments > 1)
	{
		nSegments--;

		segments[nSegments].removeBody();
	}
}

void Player::setDir(std::string new_dir)
{
	this->dir = new_dir;
}

int Player::GetSegmentsCount()
{
	return nSegments - 1;
}

bool Player::IsInTile(const Location& target_loc) const
{
	for (int i = 0; i < nSegments; i++)
	{
		if (segments[i].GetLocation() == target_loc)
		{
			return true;
		}
	}

	return false;
}

bool Player::IsInTileExpectEnd(const Location& target_loc) const
{
	for (int i = 0; i < nSegments - 1; i++)
	{
		if (segments[i].GetLocation() == target_loc)
		{
			return true;
		}
	}

	return false;
}

void Player::update(const float& dt)
{

}

void Player::render(Board& board)
{
	for (int i = nSegments - 2; i > 0; i--)
	{
		segments[i].Render(board);
	}

	// Head
	segments[0].RenderHead(board, this->dir);

	// Tail
	if (nSegments > 1) {

		if (nSegments > 2)
		{
			Location currentLoc = segments[nSegments - 1].GetLocation();
			Location nextLoc = segments[nSegments - 2].GetLocation();
			if (currentLoc.x - nextLoc.x > 0)
			{
				segments[nSegments - 1].RenderTail(board, "left");
			}
			else if (currentLoc.x - nextLoc.x < 0)
			{
				segments[nSegments - 1].RenderTail(board, "right");
			}
			else if (currentLoc.y - nextLoc.y < 0)
			{
				segments[nSegments - 1].RenderTail(board, "down");
			}
			else if (currentLoc.y - nextLoc.y > 0)
			{
				segments[nSegments - 1].RenderTail(board, "up");
			}
		}
		else {
			segments[nSegments - 1].RenderTail(board, this->dir);
		}
	}
}

void Player::Segment::initHead(const Location& at_loc)
{
	loc = at_loc;
	c = sf::Color::Blue;
}

void Player::Segment::initBody()
{
	c = sf::Color::Green;
}

void Player::Segment::removeBody()
{
	c = sf::Color::Transparent;
}

void Player::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Player::Segment::MoveBy(const Location& delta_loc)
{
	loc.Add(delta_loc);
}

const Location& Player::Segment::GetLocation() const
{
	return loc;
}

void Player::Segment::Render(Board& board) const
{
	board.DrawCell(loc, c);
}

void Player::Segment::RenderHead(Board& board, std::string dir) const
{
	board.DrawSnekHead(loc, dir);
}

void Player::Segment::RenderTail(Board& board, std::string dir) const
{
	board.DrawSnekTail(loc, dir);
}


void Player::Segment::unDraw(Board& board) const
{
	board.DrawCell(loc, sf::Color::White);
}