#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <input/Input.h>
#include <2d/DebugText.h>
#include <assert.h>
#include <memory>
#include "EnemyBullet.h"
#include "TimedCall.h"
#include "Collider.h"
#include "BulletManager.h"


class BaseEnemyState;
//自キャラの前方宣言
class Player;


enum class Phase {
	Approach,//接近する
	Leave,//離脱する
};

class Enemy : public Collider
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model,Vector3 vec);
	/// <summary>
	///	接近フェーズ初期化
	/// </summary>
	void ApproachPhaseInitialize();
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
	///	状態を変更する
	/// </summary>
	void ChangeState(BaseEnemyState* newState);
	/// <summary>
	/// 弾を発射し、タイマーをリセットする関数
	/// </summary>
	void BulettTimeReset();
	/// <summary>
	/// タイマーのlistをリセットする関数
	/// </summary>
	void TimeListReset();
	/// <summary>
	/// 衝突を検出したら呼び出されるコールバック関数
	/// </summary>
	void OnCollision();
	/// <summary>
	/// プレイヤーのセッター
	/// </summary>
	void SetPlayer(Player* player) { player_ = player; }
	/// <summary>
	/// 座標のゲッター
	/// </summary>
	/// <returns></returns>
	Vector3 GetWorldPosition();

	/// <summary>
	/// やられたかどうか
	/// </summary>
	/// <returns></returns>
	bool IsDead() const { return isdead_; }

	~Enemy();//デストラクタ
private:
	/// <summary>
	///	玉発射
	/// </summary>
	void Fire();
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//自キャラ
	Player* player_ = nullptr;
	
	//状態
	BaseEnemyState* state_;
	
	//弾
	BulletManager* bulletMnager = nullptr;

	//発射感覚
	static const int kFireInterval = 60;
	//発射タイマー
	int32_t fireTimer_ = 0;

	//フェーズ
	Phase phase_ = Phase::Approach;

	//時限発動のリスト
	std::list<std::unique_ptr<TimedCall>> timedCalls_;

	bool isdead_ = false;
};

