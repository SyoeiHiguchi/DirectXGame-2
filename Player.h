#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <input/Input.h>
#include <2d/DebugText.h>
#include <assert.h>
#include "PlayerBullet.h"
#include <memory>
/// <summary>
/// 自キャラ
/// </summary>
class Player
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model,uint32_t textureHandle);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	///	描画
	/// </summary>
	void Draw(ViewProjection viewprojection);
	/// <summary>
	/// 座標のゲッター
	/// </summary>
	/// <returns></returns>
	Vector3 GetTransform();
private:
	/// <summary>
	///	描画
	/// </summary>
	void Attack();
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
	//弾
	std::list<std::unique_ptr<PlayerBullet>> bullets_;

	void Rotate();
	
};

