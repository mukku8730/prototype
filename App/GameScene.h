#ifndef _MAHJONG_GAME_SCENE_HEADER_2015_0212_
#define _MAHJONG_GAME_SCENE_HEADER_2015_0212_

#include "SceneType.h"
#include "MahjongTable.h"
#include "SharedPlayers.h"
#include <vector>
#include <memory>

class GameScene
{
public:
	GameScene();
	virtual ~GameScene() throw();
	virtual void Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer) = 0;
	virtual GameScene* ChangeGameScene() = 0;
	virtual E_sceneType GetSceneType() = 0;
	bool IsNextScene() const;
	bool IsFirst();
	void NextScene(bool isNextScene);
	void NextRyuukyoku(bool isNextRyuukyoku);
	void NextAgari(bool isNextAgari);
	void NextFuuro(bool isNextFuuro);
protected:
	bool m_isNextScene;
	bool m_isFirst;
	bool m_isNextRyuukyoku;
	bool m_isNextAgari;
	bool m_isNextFuuro;
};

#endif //_MAHJONG_GAME_SCENE_HEADER_2015_0212_
