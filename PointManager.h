#pragma once
#include <vector>


/// 点数管理クラス
class PointManager
{
public:
	PointManager();
	~PointManager();

	void Draw(std::vector<int> points);
};

