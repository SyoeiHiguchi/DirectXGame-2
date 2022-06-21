#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <input/Input.h>
#include <2d/DebugText.h>
#include <assert.h>
#include <memory>
#include "EnemyBullet.h"

enum class Phase {
	Approach,//接近する
	Leave,//離脱する
};

class Enemy
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	///	描画
	/// </summary>
	void Draw(ViewProjection viewprojection);
	/// <summary>
	///	移動させる関数
	/// </summary>
	void Move(Vector3 vec);
	/// <summary>
	///	座標のgetter
	/// </summary>
	Vector3 Tramsform() { return worldTransform_.translation_; };
	/// <summary>
	///	玉発射
	/// </summary>
	void Fire();
	/// <summary>
	///	接近フェーズ初期化
	/// </summary>
	void ApproachPhaseInitialize();
	void ApproachPhaseUpdate();

	~Enemy();//デストラクタ
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//EnemyState* state_;
	// 
	//弾
	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	//発射感覚
	static const int kFireInterval = 60;
	//発射タイマー
	int32_t fireTimer_ = 0;

	//フェーズ
	Phase phase_ = Phase::Approach;

	static void(Enemy::*spFuncTable[])();
};

