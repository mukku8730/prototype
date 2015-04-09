#include "PointManager.h"
#include "DebugFont.h"

PointManager::PointManager()
{
}


PointManager::~PointManager()
{
}


void PointManager::Draw(std::vector<int> points) {
	DebugFont::GetInstance()->Print(260, 50, 0xffffffff, "Player1 %d", points[0]);
	DebugFont::GetInstance()->Print(260, 70, 0xffffffff, "Player1 %d", points[1]);
	DebugFont::GetInstance()->Print(260, 90, 0xffffffff, "Player1 %d", points[2]);
	DebugFont::GetInstance()->Print(260, 110, 0xffffffff, "Player1 %d", points[3]);
}
