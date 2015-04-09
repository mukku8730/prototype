#pragma once


/// デバック用文字列表示（シングルトン）
class DebugFont 
{
private:
	DebugFont();
	~DebugFont();
	DebugFont(const DebugFont& input);
	DebugFont& operator=(const DebugFont& input);
	static DebugFont* m_instance;

public:
	/// 表示オプション
	struct Option {
		enum Align {
			LEFT, RIGHT, CENTER
		};
		bool clip;
		int clipWidth;
		Align align;
		Option() : clip(), clipWidth(), align(LEFT) {}
	};

	// インスタンス取得
	static DebugFont* GetInstance();

	// 初期化
	static bool Initialize(unsigned maxStrNum, unsigned maxWorkingBufferSize);

	// デバッグ文字列を追加
	static bool Print(int x, int y, unsigned color, const char *format, ...);

	// デバッグ文字列をオプション付きで追加
	static bool Print(int x, int y, unsigned color, Option &option, const char *format, ...);

	// 描画
	static bool Draw();

	// バッファをクリア
	static void Clear();

	// 終了時処理
	static void Terminate();
};
