#ifndef _MAHJONG_SELECT_HAI_SCENE_HEADER_2015_0212_
#define _MAHJONG_SELECT_HAI_SCENE_HEADER_2015_0212_
#include "GameScene.h"


class Character;

class SelectHaiScene : public GameScene
{
public:
	SelectHaiScene();
	virtual ~SelectHaiScene() throw();
	void Update(MahjongTable* pMahjongTable, SharedPlayers* pSharedPlayers, SharedPlayer* pOwnerPlayer);

	// シーンを変更
	GameScene* ChangeGameScene();

	// シーンタイプを取得
	E_sceneType GetSceneType();

	// 手牌を設定
	void SetTehai(std::vector<HaiType> tehai);

	// 選択した牌を取得
	HaiType GetSelectHai();

private:
	Character* m_character;
	std::vector<HaiType> m_tehai;
	int m_order;
	int m_frame;
	bool m_isPushed;
};

#endif //_MAHJONG_SELECT_HAI_SCENE_HEADER_2015_0212_
