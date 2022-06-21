#include "Player.h"
#include "Matrix.h"


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
	//デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});

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
	Rotate();
	//行列更新
	MyMatrix::MatrixUpdate(worldTransform_);
	debugText_->Printf(
		"transform:(%f,%f,%f)", worldTransform_.translation_.x,worldTransform_.translation_.y,worldTransform_.translation_.z);
	//キャラクター攻撃処理
	Attack();
	for (auto& bullet : bullets_) {
		bullet->Update();
	}
}

void Player::Draw(ViewProjection viewprojection)
{
	model_->Draw(worldTransform_, viewprojection, textureHandle_);
	for (auto& bullet : bullets_) {
		bullet->Draw(viewprojection);
	}
}

Vector3 Player::GetTransform()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行成分取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Player::Attack()
{
	if (input_->PushKey(DIK_SPACE)) {
		//弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		//速度ベクトルを自機の向きに合わせて回転させる
		velocity =  MyMatrix::VectorProduct(velocity, worldTransform_);

		//弾を生成し初期化
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_, worldTransform_.translation_,velocity);
		//弾を登録する
		bullets_.push_back(std::move(newBullet));
	}
}

void Player::Rotate()
{
	//キャラクターの移動ベクトル
	Vector3 rot = { 0,0,0 };
	//移動ベクトルを変更する処理
	if (input_->PushKey(DIK_LEFT))  rot.y = 0.5;
	if (input_->PushKey(DIK_RIGHT)) rot.y = -0.5;
	//座標移動
	worldTransform_.rotation_ = rot;
}