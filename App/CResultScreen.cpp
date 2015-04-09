#include"CResultScreen.h"
#include "../BillboardString.h"


///役のポインタ配列
static const wchar_t *RoleTable[] = {
	L"立直", L"一発", L"門前清摸和", L"平和", L"タンヤオ", L"一盃口", L"白", L"発", L"中", L"場風牌", L"自風牌", L"嶺上開花",
	L"槍槓", L"海底摸月", L"河底摸魚", L"ダブル立直", L"全帯", L"混老頭", L"三色同順", L"一気通貫", L"対々和", L"三色同刻",
	L"三暗刻", L"三槓子", L"小三元", L"七対子", L"二盃口", L"純全帯", L"混一色", L"清一色", L"四暗刻", L"四暗刻単騎待ち",
	L"大三元", L"字一色", L"四喜和", L"大四喜", L"緑一色", L"九蓮宝燈", L"純正九連宝燈", L"清老頭", L"四槓子", L"国士無双",
	L"国士無双単騎待ち", L"天和", L"地和", L"人和", L"\0"
};


static const int HEIGH_STR = 30;					//役の数によって高さ調整
static const int BESIDE_STR = 170;					//役の数によって横調整
static const int MAX_ROLE_INDEX = 46;				//役の数
typedef std::vector<const wchar_t*> DrawRoleList;

/**
	コンストラクタ
*/
CResuitScreen::CResuitScreen(){

}

CResuitScreen::~CResuitScreen() throw(){

}

/**
	役 描画関数
*/
void CResuitScreen::DrawRole(bool *RoleJudgment){

	BillboardString *pRole[MAX_ROLE_INDEX] = { NULL };
	DrawRoleList RoleList;
	int roleCount = 0;
	int roleIndex = 0;
	int beside = -1;
	int height = 0;

	//テーブルの最大要素分だけ判定を行う
	for (int judgIndex = 0; judgIndex < MAX_ROLE_INDEX; judgIndex++){
		if (RoleJudgment[judgIndex] == true){
			RoleList.push_back(RoleTable[judgIndex]);				//リストを作って文字列を格納
			roleCount++;
		}
	}

	for (int creatStr = 0; creatStr <= roleCount; creatStr++){
		pRole[creatStr] = new BillboardString();					//役の分だけ動的確保
	}


	//一気に表示するループを用意
	for (DrawRoleList::iterator roleIt = RoleList.begin(); roleIt != RoleList.end(); roleIt++){

		if (roleIndex % 6 == 0){
			height = 0;
			beside++;
		}

		//表示する
		pRole[roleIndex]->RegistString(*roleIt);
		pRole[roleIndex]->SetPosition(50.0f + (BESIDE_STR*beside), 170.0f + (HEIGH_STR*height));
		pRole[roleIndex]->SetScale(0.85f, 0.85f);
		pRole[roleIndex]->SetColor(0x00CC99CC);
		pRole[roleIndex]->Draw();
		height++;
		roleIndex++;
	}

	for (int creatStr = 0; creatStr <= roleCount; creatStr++){
		if (pRole[creatStr]){
			delete pRole[creatStr];
			pRole[creatStr] = NULL;
		}
	}
}



