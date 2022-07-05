#include "EnemyBullet.h"
#include "Matrix.h"
#include <cmath>

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3 velocity)
{
	assert(model);
	model_ = model;
	//テクスチャの読み込み
	textureHandle_ = TextureManager::Load("敵の弾.png");
	//ワールド変換の初期化
	worldTransform_.scale_ = { 0.5f,0.5f,3.0f };//x,y,z方向のスケーリング設定
	worldTransform_.rotation_ = { 0,0,0 };//x,y,z軸周りの回転角を設定
	//y軸周り角度(θy)
	worldTransform_.rotation_.y = std::atan2(velocity.x, velocity.z);
	//横軸方向の長さをもとめる
	Vector3 vel = velocity;
	vel.y = 0;
	//ｙ軸周り角度を求める(θx)
	worldTransform_.translation_.x = std::atan2(velocity.z, vel.length());

	worldTransform_.translation_ = { 0,0,0 };//x,y,z軸周りの平行移動を設定する
	worldTransform_.Initialize();
	MyMatrix::MatrixScale(worldTransform_);
	MyMatrix::MatrixRotation(worldTransform_);
	MyMatrix::MatrixTranslation(worldTransform_);
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	//引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
	//衝突属性設定
	collisionConfig_.SetcollisionAttribute(kCollisionAttributeEnemy);
	//衝突対象を自分の属性以外に設定
	collisionConfig_.SetCollisionMask(!kCollisionAttributeEnemy);
}

void EnemyBullet::Update()
{
	worldTransform_.translation_ += velocity_;
	MyMatrix::MatrixUpdate(worldTransform_);
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

Vector3 EnemyBullet::GetWorldPosition()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行成分取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void EnemyBullet::OnCollision(){
	isDead_ = true;
}

