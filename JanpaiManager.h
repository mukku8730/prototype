#pragma once
#include "app/Hai.h"
#include "app/FuuroHai.h"
#include <vector>
#include <set>
#include <memory>

class Janpai;
class BillboardString;


/// �����v���Y�H�ꌓ�Ǘ��N���X
class JanpaiManager
{
private:
	static const int m_mahjongTilesNum;
	Janpai* m_janpai;
	enum DirectionType {
		DirectionType_South,
		DirectionType_East,
		DirectionType_North,
		DirectionType_West,

		DirectionType_Max,
	};


public:
	JanpaiManager();
	~JanpaiManager();

	// �X�V����
	void Update();

	// ��v��`��
	void DrawTehai(std::vector<std::multiset<HaiType>> tehai);

	// �̔v��`��
	void DrawSuteHai(std::vector<std::vector<HaiType>> fuuroHai);

	// ���I�v��`��
	void DrawFuuroHai(std::vector<std::vector<std::shared_ptr<FuuroHai>>> fuuroHai);

	// �c���v��`��
	void DrawTsumoHai(const std::vector<HaiType>& tsumoHai);

	//�v�̎R��`��
	void DrawMountainHai(int maxHaiCount, int doraSize);

	//���v�̎R��`��
	void DrawDeadWall(std::vector<HaiType> doras);

};
