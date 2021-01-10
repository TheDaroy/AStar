#pragma once
#include <cstdint>
#include <vector>
struct BoardCoordinates
{
	int16_t x;
	int16_t y;

};
inline bool operator ==(const BoardCoordinates& lHS, const BoardCoordinates& rHS)
{
	return std::tie(lHS.x, lHS.y) ==
		   std::tie(rHS.x, rHS.y);
}
inline bool operator <(const BoardCoordinates& lHS, const BoardCoordinates& rHS)
{
	return std::tie(lHS.x, lHS.y) < std::tie(rHS.x, rHS.y);
}
struct AIComponent
{
	BoardCoordinates currentPosition;
	BoardCoordinates targetPosition;
	std::vector<BoardCoordinates> path;

	float updateTime = 0.05f;
	float timer = 0; 


};

