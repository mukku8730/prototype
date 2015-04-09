#include "Vector3.h"

class FileMesh;

class Janpai {
private:
	FileMesh* m_janpai;
	Vector3 m_position;
	Matrix16 m_rotation;
	Vector3 m_scale;


public:
	Janpai();
	~Janpai();

	// �ʒu��ݒ�
	void SetPosition(const Vector3 position);

	// �p����ݒ�
	void SetRotation(const Vector3 rotation);

	// �e�N�X�`����ݒ�
	HRESULT SetTexture(int janpaiID);

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();
};


