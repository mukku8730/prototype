#ifndef _PLAYER_HEADER_2015_0212_
#define _PLAYER_HEADER_2015_0212_

#include "Place.h"
#include "Kaze.h"
#include "MahjongTable.h"
#include "HaiKey.h"
#include "PopupMenuKey.h"
#include "SceneType.h"
#include <memory>

#define SELECT_HAI_MAX (2)

class Player
{
public:
	Player(E_place place, std::shared_ptr<MahjongTable> mahjongTablePtr);
	virtual ~Player() throw();
	virtual void Update();
	E_haiKey GetHaiKey() const;
	void ClearHaiKey();
	E_popupMenuKey GetPopupMenuKey() const;
	void ClearPopupMenuKey();
	E_kaze GetKaze() const;
	void SetKaze(E_kaze kaze);
	E_place GetPlace() const;
	void SetPlace(E_place place);
	void SetSceneType(E_sceneType sceneType);
	bool IsMyTurn() const;
	void MyTurn(bool isMyTurn);
	bool HasSelected();
protected:
	std::shared_ptr<MahjongTable> m_mahjongTablePtr;
	E_haiKey m_haiKey;
	std::unique_ptr<HaiType[]> m_selectHaiType;
	E_popupMenuKey m_popupMenuKey;
	E_place m_place;
	E_kaze m_kaze;
	E_sceneType m_sceneType;
	bool m_isMyTurn;
	bool m_hasSelected;
};

#endif //_PLAYER_HEADER_2015_0212_
