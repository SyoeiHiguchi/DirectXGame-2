#pragma once
#include "WorldTransform.h"
#include "Model.h"

#include <input/Input.h>
#include <2d/DebugText.h>
#include <assert.h>
class PlayerBullet
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name = "model">モデル</pram>
	/// <param name = "position">初期座標</pram>
	void Initialize(Model* model, const Vector3& position);
	/// <summary>
	///  更新
	/// </summary>
	void Update();
	/// <summary>
	///  描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection);
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//入出力をするため
	Input* input_ = nullptr;
	//デバッグテキスト
	DebugText* debugText_ = nullptr;
};

