#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "Player.h"
#include "Enemy.h"
#include <memory>
#include "Skydome.h"
#include "RailCamera.h"
#include "BulletManager.h"
#include <fstream>
#include <sstream>


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopDate();

	void UpdateEnemyPopCommands();

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	uint32_t textureHandle_ = 0;//テクスチャハンドル
	Model* model_ = nullptr;//3dモデル
	Model* ModelSkydome_ = nullptr;//３ｄモデル　スカイドーム
	ViewProjection viewProjection_;//ビュープロジェクション
	DebugCamera* debugCamera_ = nullptr;//デバッグカメラ
	float viewAngel = 0.0f;//カメラ上方向の角度
	std::unique_ptr<Player> player_ = nullptr;
	std::list<std::unique_ptr<Enemy>> enemys_;
	std::unique_ptr<Skydome> skydome_ = nullptr;
	std::unique_ptr<RailCamera> railcamera_ = nullptr;//レールカメラ
	BulletManager* bulletManager_ = nullptr;//敵の弾管理クラス
	bool isDubugCameraActive_ = false;//デバッグカメラを有効化

	std::stringstream enemyPopCommands;


	//時間管理
	bool waitflag;
	int waitTimer;

	
private:
	/// <summary>
	/// コライダー二つの衝突判定と応答
	/// </summary>
	/// <param name="A">コライダーA</param>
	/// <param name="B">コライダーB</param>
	void CheckOnCollisions(Collider* A, Collider* B);
};
