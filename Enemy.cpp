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
	state_ = new EnemyStateApproach();
	ApproachPhaseInitialize();
}


void Enemy::Update()
{
	//�f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		return bullet->IsDead();
		});

	state_->Action(this);
	//�s��X�V
	MyMatrix::MatrixUpdate(worldTransform_);

	for (auto& bullet : bullets_) {
		bullet->Update();
	}

	//�I�������^�C�}�[���폜
	timedCalls_.remove_if([](std::unique_ptr<TimedCall>& timedcall) {
		return timedcall->IsFinished();
		});
	//�͈�for�őS�v�f�ɂ��ĉ�
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
	BulettTimeReset();
}

void Enemy::ChangeState(BaseEnemyState* newState)
{
	delete state_;
	state_ = newState;
}

void Enemy::BulettTimeReset()
{
	//�e�𔭎�
	Fire();
	//���˃^�C�}�[���Z�b�g����
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
