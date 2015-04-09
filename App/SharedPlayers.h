#ifndef _SHAREDPLAYERS_H_20150225194920_
#define _SHAREDPLAYERS_H_20150225194920_

#include "Player.h"
#include <vector>
#include <memory>
typedef std::shared_ptr<Player> SharedPlayer;
typedef std::vector<SharedPlayer> SharedPlayers;

#endif //_SHAREDPLAYERS_H_20150225194920_
