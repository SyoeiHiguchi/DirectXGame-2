#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <input/Input.h>
#include <2d/DebugText.h>
#include <assert.h>
#include "PlayerBullet.h"
#include <memory>
#include "Collider.h"
/// <summary>
/// 自キャラ
/// </summary>
class Player : public Collider
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
	/// 衝突を検出したら呼び出されるコールバック関数
	/// </summary>
	void OnCollision();
	/// <summary>
	/// 弾リストを取得する
	/// </summary>
	/// <returns></returns>
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; };
	/// <summary>
	/// 座標のゲッター
	/// </summary>
	/// <returns></returns>
	Vector3 GetWorldPosition();

	void SetPearent(const WorldTransform& worldtransform) { worldTransform_.parent_ = &worldtransform; }
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

