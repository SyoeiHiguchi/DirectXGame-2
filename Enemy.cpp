#include "Enemy.h"
#include "Matrix.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle)
{
	//NULL�|�C���^�`�F�b�N
	assert(model);
	//�����Ƃ��Ď󂯂Ƃ����f�[�^�������o�ϐ��ɋL�^����
	this->model_ = model;
	this->textureHandle_ = textureHandle;
	//���[���h�ϊ��̏�����
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };//x,y,z�����̃X�P�[�����O�ݒ�
	worldTransform_.rotation_ = { 0,0,0 };//x,y,z������̉�]�p��ݒ�
	worldTransform_.translation_ = { 0,0,0 };//x,y,z������̕��s�ړ���ݒ肷��
	worldTransform_.Initialize();
	MyMatrix::MatrixScale(worldTransform_);
	MyMatrix::MatrixRotation(worldTransform_);
	MyMatrix::MatrixTranslation(worldTransform_);
}

void(Enemy::* Enemy::spFuncTable[])() = {
	&Enemy::Approach,
	&Enemy::Leave
};

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
	//	worldTransform_.translation_ += Vector3(4,1,3);
	//	break;
	//}
	if (worldTransform_.translation_.z < -10.0f) {
			phase_ = Phase::Leave;
		}
	(this->*spFuncTable[static_cast<size_t>(phase_)])();

	//�s��X�V
	
	MyMatrix::MatrixUpdate(worldTransform_);
}

void Enemy::Draw(ViewProjection viewprojection)
{
	model_->Draw(worldTransform_, viewprojection, textureHandle_);
}

void Enemy::Approach()
{
	worldTransform_.translation_.z -= 0.1;
	//�K��̈ʒu�ɓ��B�����痣�E
	if (worldTransform_.translation_.z < -10.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave()
{
	//�ړ�(�x�N�g�������Z)
	worldTransform_.translation_ += Vector3(4, 1, 3);
}
