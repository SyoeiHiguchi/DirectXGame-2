#include "Enemy.h"
#include "Matrix.h"
#include "EnemyStateApproach.h"
#include "EnemyStateLeave.h"
#include "Player.h"
#include <cassert>

void Enemy::Initialize(Model* model, Vector3 vec)
{
	//NULLポインタチェック
	assert(model);
	//引数として受けとったデータをメンバ変数に記録する
	this->model_ = model;
	this->textureHandle_ = TextureManager::Load("敵.png");
	//ワールド変換の初期化
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };//x,y,z方向のスケーリング設定
	worldTransform_.rotation_ = { 0,0,0 };//x,y,z軸周りの回転角を設定
	worldTransform_.translation_ = { vec.x,vec.y,vec.z };//x,y,z軸周りの平行移動を設定する
	worldTransform_.Initialize();
	MyMatrix::MatrixScale(worldTransform_);
	MyMatrix::MatrixRotation(worldTransform_);
	MyMatrix::MatrixTranslation(worldTransform_);
	//ステート管理
	state_ = new EnemyStateApproach();
	//衝突属性設定
	collisionConfig_.SetcollisionAttribute(kCollisionAttributeEnemy);
	//衝突対象を自分の属性以外に設定
	collisionConfig_.SetCollisionMask(~kCollisionAttributeEnemy);

	bulletMnager = BulletManager::GetInstance();
}


void Enemy::Update()
{
	state_->Action(this);
	//行列更新
	MyMatrix::MatrixUpdate(worldTransform_);

	

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
	
}

void Enemy::Move(Vector3 vec)
{
	worldTransform_.translation_ += vec;
	MyMatrix::MatrixUpdate(worldTransform_);
}

void Enemy::Fire()
{
	assert(player_);
	//弾の速度
	const float kBulletSpeed = 1.0f;
	Vector3 PlayerPos = player_->GetWorldPosition();
	Vector3 MyPos = this->GetWorldPosition();
	
	Vector3 velocity = PlayerPos - MyPos;
	velocity.normalize();
	velocity *= kBulletSpeed;

	//弾を生成し初期化
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	//弾を登録する
	bulletMnager->AddEnemyBullet(newBullet);
	//bullets_.push_back(std::move(newBullet));
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

void Enemy::OnCollision()
{
	isdead_ = true;
}

Vector3 Enemy:: GetWorldPosition()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行成分取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

Enemy::~Enemy()
{
	delete state_;
}
