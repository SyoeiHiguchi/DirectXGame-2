#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"

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
	worldtransform_.Initialize();//ワールドトランスフォームの初期化
	viewprojection_.Initialize();//ビュープロジェクションの初期化
	debugCamera_ = new DebugCamera(1280, 720);
	AxisIndicator::GetInstance()->SetVisible(true);//軸方向表示の表示を有効化する
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());//軸方向が参照するビュープロダクションを指定する
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());//ライン描画するビュープロジェクションを指定する
}

void GameScene::Update() {
	debugCamera_->Update();//デバッグカメラの更新
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
	model_->Draw(worldtransform_, debugCamera_->GetViewProjection(), textureHandle_);
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
