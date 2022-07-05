#pragma once
#include<WorldTransform.h>
#include <3d/Model.h>
/// <summary>
/// 天球
/// </summary>
class Skydome
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection viewprojection);

	~Skydome();
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
};

