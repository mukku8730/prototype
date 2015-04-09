#pragma once
#include "Player.h"
#include "../BillboardString.h"
#include <memory>

class RealUser :
	public Player
{
public:
	RealUser(E_place place, std::shared_ptr<MahjongTable> mahjongTablePtr);
	virtual ~RealUser() throw();
	void Update();
};
