#include "Enemy.h"
#include "Matrix.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle)
{
	//NULLポインタチェック
	assert(model);
	//引数として受けとったデータをメンバ変数に記録する
	this->model_ = model;
	this->textureHandle_ = textureHandle;
	//ワールド変換の初期化
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };//x,y,z方向のスケーリング設定
	worldTransform_.rotation_ = { 0,0,0 };//x,y,z軸周りの回転角を設定
	worldTransform_.translation_ = { 0,0,0 };//x,y,z軸周りの平行移動を設定する
	worldTransform_.Initialize();
	MyMatrix::MatrixScale(worldTransform_);
	MyMatrix::MatrixRotation(worldTransform_);
	MyMatrix::MatrixTranslation(worldTransform_);
}

void(Enemy::* Enemy::spFuncTable[])() = {
	&Enemy::Approach,
	&Enemy::Leave
};

void Enemy::Update()
{
	//switch (phase_)
	//{
	//case Phase::Approach:
	//	//移動ベクトルを加算
	//	worldTransform_.translation_.z -= 0.1;
	//	//規定の位置に到達したら離脱
	//	if (worldTransform_.translation_.z < -10.0f) {
	//		phase_ = Phase::Leave;
	//	}
	//	break;
	//default:
	//	//移動(ベクトルを加算)
	//	worldTransform_.translation_ += Vector3(4,1,3);
	//	break;
	//}
	if (worldTransform_.translation_.z < -10.0f) {
			phase_ = Phase::Leave;
		}
	(this->*spFuncTable[static_cast<size_t>(phase_)])();

	//行列更新
	
	MyMatrix::MatrixUpdate(worldTransform_);
}

void Enemy::Draw(ViewProjection viewprojection)
{
	model_->Draw(worldTransform_, viewprojection, textureHandle_);
}

void Enemy::Approach()
{
	worldTransform_.translation_.z -= 0.1;
	//規定の位置に到達したら離脱
	if (worldTransform_.translation_.z < -10.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave()
{
	//移動(ベクトルを加算)
	worldTransform_.translation_ += Vector3(4, 1, 3);
}
