#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"

constexpr auto PI = 3.1415926;

float ConvertToRadians(float Degrees) { return Degrees * (PI / 180.0f); }
void ScaleMatrix(WorldTransform& wtf)
{
	Matrix4 matScale;//スケーリング行列を宣言
	matScale.m[0][0] = wtf.scale_.x;//スケーリング倍率を行列に設定
	matScale.m[1][1] = wtf.scale_.y;
	matScale.m[2][2] = wtf.scale_.z;
	matScale.m[3][3] = 1;
	wtf.matWorld_ = MathUtility::Matrix4Identity();//単位行列を代入
	wtf.matWorld_ *= matScale;
	//wtf.TransferMatrix();//行列の転送
}
void TranslationMatrix(WorldTransform& wtf)
{
	Matrix4 matTrans = MathUtility::Matrix4Identity();//平行移動行列を設定
	matTrans.m[3][0] = wtf.translation_.x;//移動量を行列に代入
	matTrans.m[3][1] = wtf.translation_.y;
	matTrans.m[3][2] = wtf.translation_.z;
	wtf.matWorld_ *= matTrans;
	wtf.TransferMatrix();//行列の転送
}
void RotationXMatrix(WorldTransform& wtf)
{
	Matrix4 matRotX = MathUtility::Matrix4Identity();;//x軸回転行列を宣言
	matRotX.m[1][1] = cosf(wtf.rotation_.x);//x軸回転行列の各要素を設定する
	matRotX.m[1][2] = sinf(wtf.rotation_.x);
	matRotX.m[2][1] = -sinf(wtf.rotation_.x);
	matRotX.m[2][2] = cosf(wtf.rotation_.x);
	wtf.matWorld_ *= matRotX;
}
void RotationYMatrix(WorldTransform& wtf)
{
	Matrix4 matRotY = MathUtility::Matrix4Identity();//y軸回転行列を宣言
	matRotY.m[0][0] = cosf(wtf.rotation_.y);//y軸回転行列の各要素を設定する
	matRotY.m[2][0] = sinf(wtf.rotation_.y);
	matRotY.m[0][2] = -sinf(wtf.rotation_.y);
	matRotY.m[2][2] = cosf(wtf.rotation_.y);
	wtf.matWorld_ *= matRotY;
	wtf.TransferMatrix();//行列の転送
}
void RotationZMatrix(WorldTransform& wtf)
{
	Matrix4 matRotZ = MathUtility::Matrix4Identity();;//z軸回転行列を宣言
	matRotZ.m[0][0] = cosf(wtf.rotation_.z);//z軸回転行列の各要素を設定する
	matRotZ.m[0][1] = sinf(wtf.rotation_.z);
	matRotZ.m[1][0] = -sinf(wtf.rotation_.z);
	matRotZ.m[1][1] = cosf(wtf.rotation_.z);
	wtf.matWorld_ *= matRotZ;
	wtf.TransferMatrix();//行列の転送
}
void RotationMatrix(WorldTransform& wtf)
{
	RotationZMatrix(wtf);
	RotationXMatrix(wtf);
	RotationYMatrix(wtf);
}

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
	
	worldtransform_.scale_ = { 5.0f,5.0f,5.0f };//x,y,z方向のスケーリング設定
	ScaleMatrix(worldtransform_);
	float rad = ConvertToRadians(45.0f);
	worldtransform_.rotation_ = { rad,rad,0.0f };//x,y,z軸周りの回転角を設定
	RotationMatrix(worldtransform_);
	worldtransform_.translation_ = { 10.0f,10.0f,10.0f };//x,y,z軸周りの平行移動を設定する
	TranslationMatrix(worldtransform_);

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
