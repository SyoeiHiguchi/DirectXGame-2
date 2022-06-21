#include "Enemy.h"
#include "Matrix.h"
#include "EnemyStateApproach.h"
#include "EnemyStateLeave.h"

void Enemy::Initialize(Model* model)
{
	//NULL�|�C���^�`�F�b�N
	assert(model);
	//�����Ƃ��Ď󂯂Ƃ����f�[�^�������o�ϐ��ɋL�^����
	this->model_ = model;
	this->textureHandle_ = TextureManager::Load("�G.png");
	//���[���h�ϊ��̏�����
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };//x,y,z�����̃X�P�[�����O�ݒ�
	worldTransform_.rotation_ = { 0,0,0 };//x,y,z������̉�]�p��ݒ�
	worldTransform_.translation_ = { 0,0,0 };//x,y,z������̕��s�ړ���ݒ肷��
	worldTransform_.Initialize();
	MyMatrix::MatrixScale(worldTransform_);
	MyMatrix::MatrixRotation(worldTransform_);
	MyMatrix::MatrixTranslation(worldTransform_);
	//state_ = new EnemyStateApproach();
	ApproachPhaseInitialize();
	state_ = new EnemyStateApproach();
}


void Enemy::Update()
{
	//switch (phase_)
	//{
	//case Phase::Approach:
	//	//�ړ��x�N�g�������Z
	//	worldTransform_.translation_.z -= 0.1;
	//	//�K��̈ʒu�ɓ��B�����痣�E
	//	if (worldTransform_.translation_.z < -10.0f) {
	//		phase_ = Phase::Leave;
	//	}
	//	break;
	//default:
	//	//�ړ�(�x�N�g�������Z)
	//	worldTransform_.translation_ += Vector3(4, 1, 3);
	//	break;
	//}
	state_->Action(this);
	ApproachPhaseUpdate();
	//�s��X�V
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
	worldTransform_.translation_ += vec;
	MyMatrix::MatrixUpdate(worldTransform_);
}


//void Enemy::ChangeState(EnemyState* newState)
//{
//	delete state_;
//	state_ = newState;
//}

void Enemy::Fire()
{
	//�e�̑��x
	const float kBulletSpeed = 1.0f;
	Vector3 velocity(0, kBulletSpeed, kBulletSpeed);

	//�e�𐶐���������
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	//�e��o�^����
	bullets_.push_back(std::move(newBullet));
}

void Enemy::ApproachPhaseInitialize()
{
	//���˃^�C�}�[��������
	fireTimer_ = 60;
}

void Enemy::ApproachPhaseUpdate()
{
	fireTimer_--;
	if (fireTimer_ < 0) {
		//�e�𔭎�
		Fire();
		fireTimer_ = kFireInterval;
	}
}

void Enemy::ChangeState(BaseEnemyState* newState)
{
	delete state_;
	state_ = newState;
}

Enemy::~Enemy()
{
	delete state_;
}
