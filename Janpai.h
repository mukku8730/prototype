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

	// 位置を設定
	void SetPosition(const Vector3 position);

	// 姿勢を設定
	void SetRotation(const Vector3 rotation);

	// テクスチャを設定
	HRESULT SetTexture(int janpaiID);

	// 更新処理
	void Update();

	// 描画処理
	void Draw();
};


