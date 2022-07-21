#include "Enemy.h"
#include "Matrix.h"
#include "EnemyStateApproach.h"
#include "EnemyStateLeave.h"
#include "Player.h"
#include <cassert>

void Enemy::Initialize(Model* model, Vector3 vec)
{
	//NULL�|�C���^�`�F�b�N
	assert(model);
	//�����Ƃ��Ď󂯂Ƃ����f�[�^�������o�ϐ��ɋL�^����
	this->model_ = model;
	this->textureHandle_ = TextureManager::Load("�G.png");
	//���[���h�ϊ��̏�����
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };//x,y,z�����̃X�P�[�����O�ݒ�
	worldTransform_.rotation_ = { 0,0,0 };//x,y,z������̉�]�p��ݒ�
	worldTransform_.translation_ = { vec.x,vec.y,vec.z };//x,y,z������̕��s�ړ���ݒ肷��
	worldTransform_.Initialize();
	MyMatrix::MatrixScale(worldTransform_);
	MyMatrix::MatrixRotation(worldTransform_);
	MyMatrix::MatrixTranslation(worldTransform_);
	//�X�e�[�g�Ǘ�
	state_ = new EnemyStateApproach();
	//�Փˑ����ݒ�
	collisionConfig_.SetcollisionAttribute(kCollisionAttributeEnemy);
	//�ՓˑΏۂ������̑����ȊO�ɐݒ�
	collisionConfig_.SetCollisionMask(~kCollisionAttributeEnemy);

	bulletMnager = BulletManager::GetInstance();
}


void Enemy::Update()
{
	state_->Action(this);
	//�s��X�V
	MyMatrix::MatrixUpdate(worldTransform_);

	

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
	
}

void Enemy::Move(Vector3 vec)
{
	worldTransform_.translation_ += vec;
	MyMatrix::MatrixUpdate(worldTransform_);
}

void Enemy::Fire()
{
	assert(player_);
	//�e�̑��x
	const float kBulletSpeed = 1.0f;
	Vector3 PlayerPos = player_->GetWorldPosition();
	Vector3 MyPos = this->GetWorldPosition();
	
	Vector3 velocity = PlayerPos - MyPos;
	velocity.normalize();
	velocity *= kBulletSpeed;

	//�e�𐶐���������
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	//�e��o�^����
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

void Enemy::OnCollision()
{
	isdead_ = true;
}

Vector3 Enemy:: GetWorldPosition()
{
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�����擾
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

Enemy::~Enemy()
{
	delete state_;
}
