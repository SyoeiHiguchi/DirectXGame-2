#include "PlayerBullet.h"
#include "Matrix.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3 velocity)
{
	assert(model);
	model_ = model;
	//�e�N�X�`���̓ǂݍ���
	textureHandle_ = TextureManager::Load("���@�̒e.png");
	//���[���h�ϊ��̏�����
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };//x,y,z�����̃X�P�[�����O�ݒ�
	worldTransform_.rotation_ = { 0,0,0 };//x,y,z������̉�]�p��ݒ�
	worldTransform_.translation_ = { 0,0,0 };//x,y,z������̕��s�ړ���ݒ肷��
	worldTransform_.Initialize();
	MyMatrix::MatrixScale(worldTransform_);
	MyMatrix::MatrixRotation(worldTransform_);
	MyMatrix::MatrixTranslation(worldTransform_);
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;
	//�����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;
}

void PlayerBullet::Update()
{
	worldTransform_.translation_ += velocity_;
	MyMatrix::MatrixUpdate(worldTransform_);
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void PlayerBullet::OnCollision()
{
	isDead_ = true;
}

Vector3 PlayerBullet::GetTransform()
{
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�����擾
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}
