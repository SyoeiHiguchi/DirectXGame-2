﻿#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include <random>

constexpr auto PI = 3.1415926;

float ConvertToRadians(float Degrees) { return Degrees * (PI / 180.0f); }
float ConvertToDegrees(float Radians)  { return Radians * (180.0f / PI); }


GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	textureHandle_ = TextureManager::Load("mario.jpg");
	model_ = Model::Create();
	
	player_ = std::make_unique<Player>();//自キャラの生成
	player_->Initialize(model_,textureHandle_);//プレイヤーの初期化

	enemy_ = std::make_unique<Enemy>();//エネミーの生成
	enemy_->Initialize(model_);//エネミーの初期化

	//viewProjection_.eye = { 0,0,-50 };    //カメラ視点座標を設定
	//viewProjection_.target = {10,0,0}; //カメラ注視点を設定
	//viewProjection_.up = {ConvertToRadians(45.0f),ConvertToRadians(45.0f) ,0};
	//viewProjection_.fovAngleY = ConvertToRadians(10.0f); //カメラ垂直方向視野角を設定
	//viewProjection_.aspectRatio = 1.0f;                    //アスペクト比の設定
	//viewProjection_.nearZ = 52.0f;                          //ニアクリップ距離を設定
	//viewProjection_.farZ = 53.0f;//ファークリップ距離を設定
	viewProjection_.Initialize();//ビュープロジェクションの初期化
	debugCamera_ = new DebugCamera(1280, 720);
	AxisIndicator::GetInstance()->SetVisible(true);//軸方向表示の表示を有効化する
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);//軸方向が参照するビュープロダクションを指定する
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());//ライン描画するビュープロジェクションを指定する

	enemy_->SetPlayer(player_.get());	
}

void GameScene::Update() {
#ifdef DEBUG
	if (input_->TriggerKey(DIK_D)) {
		isDubugCameraActive_ = !isDubugCameraActive_;
	}
	if (isDubugCameraActive_) {
		debugCamera_->Update();//デバッグカメラの更新
		viewProjection_.matView = debugCamera_->GetViewProjection();
		viewProjection_.matProjection = debugCamera_->SetDistance();

	}
	else{
		viewProjection_.UpdateMatrix(); //行列の再計算
	}
#endif // DEBUG
	
	//視点移動処理
	//{
	//	Vector3 move = {0, 0, 0};    //視点の移動ベクトル
	//	const float kEyeSpeed = 0.2f; //視点移動の速さ
	//	if (input_->PushKey(DIK_W)) { //押した方向で移動ベクトルを変更
	//		move = {0, 0, kEyeSpeed};
	//	} else if (input_->PushKey(DIK_S)) {
	//		move = {0, 0, -kEyeSpeed};
	//	}
	//	viewProjection_.eye += move; //視点移動（ベクトルの移動）
	//	viewProjection_.UpdateMatrix(); //行列の再計算
	//	debugText_->SetPos(50, 50);
	//	debugText_->Printf(
	//	"eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
	//}
	//注視点移動処理
	//{
	//	Vector3 move = {0, 0, 0};       //注視点の移動ベクトル
	//	const float kTargetSpeed = 0.2f; //注視点の移動速度
	//	if (input_->PushKey(DIK_LEFT)) { //押した方向で移動ベクトルを変更
	//		move = {-kTargetSpeed, 0, 0};
	//	} else if (input_->PushKey(DIK_RIGHT)) {
	//		move = {kTargetSpeed, 0, 0};
	//	}
	//	viewProjection_.target += move; //注視点移動（ベクトルの加算）
	//	viewProjection_.UpdateMatrix(); //行列の再計算
	//	debugText_->SetPos(50, 70);
	//	debugText_->Printf(
	//	"target:(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y,
	//	viewProjection_.target.z);
	//}
	//上方向の回転
	//{
	//	const float kUpRotSpeed = 0.05f;//上方向の回転の速さ[ラジアン/fream]
	//	if (input_->PushKey(DIK_SPACE)) { //押した方向で移動ベクトルを変更
	//		viewAngel += kUpRotSpeed;
	//		viewAngel = fmodf(viewAngel, PI * 2.0f);//2πを超えたら0に戻す
	//	}
	//	viewProjection_.up = {cosf(viewAngel), sinf(viewAngel),0.0f};//上方向ベクトルを計算(半径１の円周上の座標)   
	//	viewProjection_.UpdateMatrix();//行列の再計算
	//	debugText_->SetPos(50, 90);
	//	debugText_->Printf(
	//	 "up:(%f,%f,%f)", viewProjection_.up.x, viewProjection_.up.y, viewProjection_.up.z);
	//}
	// FoV変更処理
	//{
	//	 if (input_->PushKey(DIK_UP)) {//上キーで視野角が広がる
	//		viewProjection_.fovAngleY += 0.01f;
	//		viewProjection_.fovAngleY = min(viewProjection_.fovAngleY, PI);
	//	 } else if (input_->PushKey(DIK_DOWN))//下キーで視野角が狭まる
	//	 {
	//		viewProjection_.fovAngleY -= 0.01f;
	//		viewProjection_.fovAngleY = max(viewProjection_.fovAngleY, 0.01f);
	//	 }
	//	 viewProjection_.UpdateMatrix(); //行列の再計算
	//	 debugText_->SetPos(50, 110); //デバック用表示
	//	 debugText_->Printf("fovAngeleY(Degree):%f", ConvertToDegrees(viewProjection_.fovAngleY));
	//}
	//クリップ距離変更設定
	//{
	//	 if (input_->PushKey(DIK_UP)) { //上下キーでニアクリップ処理を増減
	//		viewProjection_.nearZ += 0.1f;
	//	 } else if (input_->PushKey(DIK_DOWN)) //下キーで視野角が狭まる
	//	 {
	//		viewProjection_.nearZ -= 0.1f;
	//	 }
	//	 viewProjection_.MatrixUpdate(); //行列の再計算
	//	debugText_->SetPos(50, 130); //デバック用表示
	//	debugText_->Printf("nearZ:%f", viewProjection_.nearZ);
	//}
	
	player_->Update();
	enemy_->Update();
	CheckAllCollisions();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	/// 3Dモデル描画
	player_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);

	{
		Vector3 p1 = { 0,0,0 };//線描画
		Vector3 p2 = { 1000,0,0 };
		Vector4 color = { 100,0,0,255 };
		PrimitiveDrawer::GetInstance()->DrawLine3d(p1, p2, color);
		p2 = { 0,1000,0 };
		color = { 0,100,0,255 };
		PrimitiveDrawer::GetInstance()->DrawLine3d(p1, p2, color);
		p2 = { 0,0,1000 };
		color = { 0,0,100,255 };
		PrimitiveDrawer::GetInstance()->DrawLine3d(p1, p2, color);
	}
	

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions(){
	//　判定対象AとBの座標
	Vector3 posA, posB;

	//自弾リストを取得
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();
	//敵弾リストを取得
	const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemy_->GetBullets();

#pragma region 自キャラと敵弾の当たり判定
	//自キャラの座標
	posA = player_->GetTransform();

	//自キャラと敵弾全ての当たり判定
	for (const std::unique_ptr<EnemyBullet>& bullets : enemyBullets) {
		//敵弾の座標
		posB = bullets->GetTransform();
		//座標Aと座標Bの距離を求める
		Vector3 Dir = posA - posB;
		float rad = 1;
		bool collision = Dir.x * Dir.x + Dir.y * Dir.y + Dir.z * Dir.z <= rad * rad;
		if (collision) {
			//自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			//敵弾の衝突時コールバックを呼び出す
			bullets->OnCollision();
		}
	}

#pragma endregion

#pragma region 自弾と敵の当たり判定
	//自キャラの座標
	posA = enemy_->GetTransform();

	//自キャラと敵弾全ての当たり判定
	for (const std::unique_ptr<PlayerBullet>& bullets : playerBullets) {
		//敵弾の座標
		posB = bullets->GetTransform();
		//座標Aと座標Bの距離を求める
		Vector3 Dir = posA - posB;
		float rad = 1;
		bool collision = Dir.x * Dir.x + Dir.y * Dir.y + Dir.z * Dir.z <= rad * rad;
		if (collision) {
			//敵の衝突時コールバックを呼び出す
			enemy_->OnCollision();
			//弾の衝突時コールバックを呼び出す
			bullets->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵弾の当たり判定
	//自弾と敵弾全ての当たり判定
	for (const std::unique_ptr<PlayerBullet>& Pbullets : playerBullets) {
		for (const std::unique_ptr<EnemyBullet>& Ebullets : enemyBullets) {
			//自弾の座標
			posA = Pbullets->GetTransform();
			posB = Ebullets->GetTransform();
			//座標Aと座標Bの距離を求める
			Vector3 Dir = posA - posB;
			float rad = 1;
			bool collision = Dir.x * Dir.x + Dir.y * Dir.y + Dir.z * Dir.z <= rad * rad;
			if (collision) {
				//自弾の衝突時コールバックを呼び出す
				Pbullets->OnCollision();
				//敵弾の衝突時コールバックを呼び出す
			    Ebullets->OnCollision();
			}
		}
	}
	//自キャラと敵弾全ての当たり判定
	
#pragma endregion
}
