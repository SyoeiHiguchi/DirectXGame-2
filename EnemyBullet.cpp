#include "EnemyBullet.h"
#include "Matrix.h"
#include <cmath>

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3 velocity)
{
	assert(model);
	model_ = model;
	//�e�N�X�`���̓ǂݍ���
	textureHandle_ = TextureManager::Load("�G�̒e.png");
	//���[���h�ϊ��̏�����
	worldTransform_.scale_ = { 0.5f,0.5f,3.0f };//x,y,z�����̃X�P�[�����O�ݒ�
	worldTransform_.rotation_ = { 0,0,0 };//x,y,z������̉�]�p��ݒ�
	//y������p�x(��y)
	worldTransform_.rotation_.y = std::atan2(velocity.x, velocity.z);
	//���������̒��������Ƃ߂�
	Vector3 vel = velocity;
	vel.y = 0;
	//��������p�x�����߂�(��x)
	worldTransform_.translation_.x = std::atan2(velocity.z, vel.length());

	worldTransform_.translation_ = { 0,0,0 };//x,y,z������̕��s�ړ���ݒ肷��
	worldTransform_.Initialize();
	MyMatrix::MatrixScale(worldTransform_);
	MyMatrix::MatrixRotation(worldTransform_);
	MyMatrix::MatrixTranslation(worldTransform_);
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;
	//�����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;
	//�Փˑ����ݒ�
	collisionConfig_.SetcollisionAttribute(kCollisionAttributeEnemy);
	//�ՓˑΏۂ������̑����ȊO�ɐݒ�
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
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�����擾
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void EnemyBullet::OnCollision(){
	isDead_ = true;
}

