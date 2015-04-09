#ifndef _MAHJONG_POPUP_MENU_KEY_HEADER_2015_0224_
#define _MAHJONG_POPUP_MENU_KEY_HEADER_2015_0224_

enum E_popupMenuKey
{
	E_popupMenuKey_none,
	E_popupMenuKey_Pon,
	E_popupMenuKey_Kan,
	E_popupMenuKey_Chii,
	E_popupMenuKey_Ron,
	E_popupMenuKey_Tsumo,
	E_popupMenuKey_Reach,
	E_popupMenuKey_Cancel,
	E_popupMenuKey_MAX
};

class PopupMenuKey
{
public:
	static E_popupMenuKey GetPopupMenuKey(int PopupMenuKeyNumber);
	static int GetPopupMenuKeyNumber(E_popupMenuKey popupMenuKey);
};

#endif //_MAHJONG_POPUP_MENU_KEY_HEADER_2015_0224_
