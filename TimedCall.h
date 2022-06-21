#pragma once
#include <functional>

/// <summary>
/// 時限発動
/// </summary>
class TimedCall{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TimedCall(std::function<void(void)> f, uint32_t time);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 完了ならtrueを返す
	/// </summary>
	bool IsFinished() { return finishdFlag_; };
private:
	//コールバック
	std::function<void(void)> f_;
	//残り時間
	uint32_t time_;
	//完了フラグ
	bool finishdFlag_ = false;

};

