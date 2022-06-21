#include "Enemy.h"
#include "Matrix.h"
#include "EnemyStateApproach.h"
#include "EnemyStateLeave.h"


void Enemy::Initialize(Model* model)
{
	//NULLポインタチェック
	assert(model);
	//引数として受けとったデータをメンバ変数に記録する
	this->model_ = model;
	this->textureHandle_ = TextureManager::Load("敵.png");
	//ワールド変換の初期化
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };//x,y,z方向のスケーリング設定
	worldTransform_.rotation_ = { 0,0,0 };//x,y,z軸周りの回転角を設定
	worldTransform_.translation_ = { 0,0,0 };//x,y,z軸周りの平行移動を設定する
	worldTransform_.Initialize();
	MyMatrix::MatrixScale(worldTransform_);
	MyMatrix::MatrixRotation(worldTransform_);
	MyMatrix::MatrixTranslation(worldTransform_);
	state_ = new EnemyStateApproach();
	ApproachPhaseInitialize();
}


void Enemy::Update()
{
	//デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		return bullet->IsDead();
		});

	state_->Action(this);
	//行列更新
	MyMatrix::MatrixUpdate(worldTransform_);

	for (auto& bullet : bullets_) {
		bullet->Update();
	}

	//終了したタイマーを削除
	timedCalls_.remove_if([](std::unique_ptr<TimedCall>& timedcall) {
		return timedcall->IsFinished();
		});
	//範囲forで全要素について回す
	for (auto& timedcall : timedCalls_) {
		timedcall->Update();
	}
}

void Enemy::Draw(ViewProjection viewprojection)
{
	model_->Draw(worldTransform_, viewprojection, textureHandle_);
	for (auto& bullet : bullets_) {
		bullet->Draw(viewprojection);
	}
}

void Enemy::Move(Vector3 vec)
{
	worldTransform_.translation_ += vec;
	MyMatrix::MatrixUpdate(worldTransform_);
}

void Enemy::Fire()
{
	//弾の速度
	const float kBulletSpeed = 1.0f;
	Vector3 velocity(0, kBulletSpeed, kBulletSpeed);

	//弾を生成し初期化
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	//弾を登録する
	bullets_.push_back(std::move(newBullet));
}

void Enemy::ApproachPhaseInitialize()
{
	BulettTimeReset();
}

void Enemy::ChangeState(BaseEnemyState* newState)
{
	delete state_;
	state_ = newState;
}

void Enemy::BulettTimeReset()
{
	//弾を発射
	Fire();
	//発射タイマーをセットする
	timedCalls_.push_back(std::make_unique<TimedCall>(
		std::bind(&Enemy::BulettTimeReset, this), 60));
}

void Enemy::TimeListReset()
{
	timedCalls_.clear();
}

Enemy::~Enemy()
{
	delete state_;
}
