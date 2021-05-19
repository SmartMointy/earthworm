#pragma once
#include "Goal.h"

class Player
{
private:
	class Segment
	{
	private:
		Location loc{0, 0};
		sf::Color c;
	public:
		void initHead(const Location& loc);
		void initBody();
		void removeBody();
		void Follow(const Segment& next);
		void Render(Board& board) const;
		void RenderHead(Board& board, std::string dir) const;
		void RenderTail(Board& board, std::string dir) const;
		void unDraw(Board& board) const;
		void MoveBy(const Location& delta_loc);
		const Location& GetLocation() const;
	};

private:
	sf::Color headColor = sf::Color::Blue;
	static constexpr int nSegmentsMax = 300;
	Segment segments[nSegmentsMax];
	std::string dir;

	int nSegments = 1;

public:
	Player( const Location& loc);
	~Player();

	Location GetNextHeadLocation(const Location& delta_loc) const;

	void MoveBy( const Location& delta_loc );
	void Grow();
	void Shrink();
	void setDir(std::string new_dir);

	int GetSegmentsCount();

	bool IsInTile( const Location& target_loc) const;
	bool IsInTileExpectEnd(const Location& target_loc) const;

	void update(const float& dt);
	void render(Board& board);
};

