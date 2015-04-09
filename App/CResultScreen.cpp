#include"CResultScreen.h"
#include "../BillboardString.h"


///���̃|�C���^�z��
static const wchar_t *RoleTable[] = {
	L"����", L"�ꔭ", L"��O���̘a", L"���a", L"�^�����I", L"��u��", L"��", L"��", L"��", L"�ꕗ�v", L"�����v", L"���J��",
	L"����", L"�C��̌�", L"�͒�̋�", L"�_�u������", L"�S��", L"���V��", L"�O�F����", L"��C�ʊ�", L"�΁X�a", L"�O�F����",
	L"�O�Í�", L"�O�Ȏq", L"���O��", L"���Ύq", L"��u��", L"���S��", L"����F", L"����F", L"�l�Í�", L"�l�Í��P�R�҂�",
	L"��O��", L"����F", L"�l��a", L"��l��", L"�Έ�F", L"��@��", L"������A��", L"���V��", L"�l�Ȏq", L"���m���o",
	L"���m���o�P�R�҂�", L"�V�a", L"�n�a", L"�l�a", L"\0"
};


static const int HEIGH_STR = 30;					//���̐��ɂ���č�������
static const int BESIDE_STR = 170;					//���̐��ɂ���ĉ�����
static const int MAX_ROLE_INDEX = 46;				//���̐�
typedef std::vector<const wchar_t*> DrawRoleList;

/**
	�R���X�g���N�^
*/
CResuitScreen::CResuitScreen(){

}

CResuitScreen::~CResuitScreen() throw(){

}

/**
	�� �`��֐�
*/
void CResuitScreen::DrawRole(bool *RoleJudgment){

	BillboardString *pRole[MAX_ROLE_INDEX] = { NULL };
	DrawRoleList RoleList;
	int roleCount = 0;
	int roleIndex = 0;
	int beside = -1;
	int height = 0;

	//�e�[�u���̍ő�v�f������������s��
	for (int judgIndex = 0; judgIndex < MAX_ROLE_INDEX; judgIndex++){
		if (RoleJudgment[judgIndex] == true){
			RoleList.push_back(RoleTable[judgIndex]);				//���X�g������ĕ�������i�[
			roleCount++;
		}
	}

	for (int creatStr = 0; creatStr <= roleCount; creatStr++){
		pRole[creatStr] = new BillboardString();					//���̕��������I�m��
	}


	//��C�ɕ\�����郋�[�v��p��
	for (DrawRoleList::iterator roleIt = RoleList.begin(); roleIt != RoleList.end(); roleIt++){

		if (roleIndex % 6 == 0){
			height = 0;
			beside++;
		}

		//�\������
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



