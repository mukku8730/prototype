#include "PopupMenuKey.h"

static const E_popupMenuKey popupMenuTBL[]
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

E_popupMenuKey PopupMenuKey::GetPopupMenuKey(int popupMenuKeyNumber)
{
	return popupMenuTBL[popupMenuKeyNumber];
}

int PopupMenuKey::GetPopupMenuKeyNumber(E_popupMenuKey popupMenuKey)
{
	return popupMenuKey;
}
