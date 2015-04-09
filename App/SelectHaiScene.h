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

	// �V�[����ύX
	GameScene* ChangeGameScene();

	// �V�[���^�C�v���擾
	E_sceneType GetSceneType();

	// ��v��ݒ�
	void SetTehai(std::vector<HaiType> tehai);

	// �I�������v���擾
	HaiType GetSelectHai();

private:
	Character* m_character;
	std::vector<HaiType> m_tehai;
	int m_order;
	int m_frame;
	bool m_isPushed;
};

#endif //_MAHJONG_SELECT_HAI_SCENE_HEADER_2015_0212_
