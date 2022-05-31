#include "Player.h"



void Player::Initialize(Model* model, uint32_t textureHandle)
{
	//NULLポインタチェック
	assert(model);
	//引数として受けとったデータをメンバ変数に記録する
	this->model_ = model;
	this->textureHandle_ = textureHandle;
	//シングルトンインスタンスを取得
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	//ワールド変換の初期化
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };//x,y,z方向のスケーリング設定
	worldTransform_.rotation_ = { 0,0,0};//x,y,z軸周りの回転角を設定
	worldTransform_.translation_ = { 0,0,0 };//x,y,z軸周りの平行移動を設定する
	worldTransform_.Initialize();
	MyMatrix::MatrixScale(worldTransform_);
	MyMatrix::MatrixRotation(worldTransform_);
	MyMatrix::MatrixTranslation(worldTransform_);
}

void Player::Update()
{
	//キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };
	//移動ベクトルを変更する処理
	if (input_->PushKey(DIK_UP))	move.y = 0.5;
	if (input_->PushKey(DIK_DOWN))	move.y = -0.5;
	if (input_->PushKey(DIK_LEFT))  move.x = -0.5;
	if (input_->PushKey(DIK_RIGHT)) move.x = 0.5;
	//座標移動
	worldTransform_.translation_ += move;
	//移動限界処理
	const float kMoveLimitX = 30;
	const float kMoveLimitY = 10;
	worldTransform_.translation_.x = min(kMoveLimitX, max(worldTransform_.translation_.x, -kMoveLimitX));
	worldTransform_.translation_.y = min(kMoveLimitY, max(worldTransform_.translation_.y, -kMoveLimitY));
	//行列更新
	MyMatrix::MatrixUpdate(worldTransform_);
	debugText_->Printf(
		"transform:(%f,%f,%f)", worldTransform_.translation_.x,worldTransform_.translation_.y,worldTransform_.translation_.z);	
}

void Player::Draw(ViewProjection viewprojection)
{
	model_->Draw(worldTransform_, viewprojection, textureHandle_);
}
