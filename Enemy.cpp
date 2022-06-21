#include "Enemy.h"
#include "Matrix.h"
#include "Player.h"

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
	//state_ = new EnemyStateApproach();
	ApproachPhaseInitialize();
}


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
	//	worldTransform_.translation_ += Vector3(4, 1, 3);
	//	break;
	//}
	ApproachPhaseUpdate();
	//行列更新
	MyMatrix::MatrixUpdate(worldTransform_);

	for (auto& bullet : bullets_) {
		bullet->Update();
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
	worldTransform_.translation_ = vec;
	MyMatrix::MatrixUpdate(worldTransform_);
}


//void Enemy::ChangeState(EnemyState* newState)
//{
//	delete state_;
//	state_ = newState;
//}

void Enemy::Fire()
{
	//弾の速度
	const float kBulletSpeed = 1.0f;
	Vector3 PlayerPos = player_->GetWorldPos();
	Vector3 MyPos = this->GetWorldPos();

	Vector3 velocity = PlayerPos - MyPos;
	velocity.normalize();
	velocity *= kBulletSpeed;

	//弾を生成し初期化
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	//弾を登録する
	bullets_.push_back(std::move(newBullet));
}

void Enemy::ApproachPhaseInitialize()
{
	//発射タイマーを初期化
	fireTimer_ = 60;
}

void Enemy::ApproachPhaseUpdate()
{
	fireTimer_--;
	if (fireTimer_ < 0) {
		//弾を発射
		Fire();
		fireTimer_ = kFireInterval;
	}
}

Vector3 Enemy::GetWorldPos()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動成分取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

Enemy::~Enemy()
{
}
