#pragma once


/// �f�o�b�N�p������\���i�V���O���g���j
class DebugFont 
{
private:
	DebugFont();
	~DebugFont();
	DebugFont(const DebugFont& input);
	DebugFont& operator=(const DebugFont& input);
	static DebugFont* m_instance;

public:
	/// �\���I�v�V����
	struct Option {
		enum Align {
			LEFT, RIGHT, CENTER
		};
		bool clip;
		int clipWidth;
		Align align;
		Option() : clip(), clipWidth(), align(LEFT) {}
	};

	// �C���X�^���X�擾
	static DebugFont* GetInstance();

	// ������
	static bool Initialize(unsigned maxStrNum, unsigned maxWorkingBufferSize);

	// �f�o�b�O�������ǉ�
	static bool Print(int x, int y, unsigned color, const char *format, ...);

	// �f�o�b�O��������I�v�V�����t���Œǉ�
	static bool Print(int x, int y, unsigned color, Option &option, const char *format, ...);

	// �`��
	static bool Draw();

	// �o�b�t�@���N���A
	static void Clear();

	// �I��������
	static void Terminate();
};
