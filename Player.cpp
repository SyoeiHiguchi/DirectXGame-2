#include "Player.h"
#include "Matrix.h"


void Player::Initialize(Model* model, uint32_t textureHandle)
{
	//NULL�|�C���^�`�F�b�N
	assert(model);
	//�����Ƃ��Ď󂯂Ƃ����f�[�^�������o�ϐ��ɋL�^����
	this->model_ = model;
	this->textureHandle_ = textureHandle;
	//�V���O���g���C���X�^���X���擾
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	//���[���h�ϊ��̏�����
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };//x,y,z�����̃X�P�[�����O�ݒ�
	worldTransform_.rotation_ = { 0,0,0};//x,y,z������̉�]�p��ݒ�
	worldTransform_.translation_ = { 0,0,0 };//x,y,z������̕��s�ړ���ݒ肷��
	worldTransform_.Initialize();
	MyMatrix::MatrixScale(worldTransform_);
	MyMatrix::MatrixRotation(worldTransform_);
	MyMatrix::MatrixTranslation(worldTransform_);
}

void Player::Update()
{
	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,0,0 };
	//�ړ��x�N�g����ύX���鏈��
	if (input_->PushKey(DIK_UP))	move.y = 0.5;
	if (input_->PushKey(DIK_DOWN))	move.y = -0.5;
	if (input_->PushKey(DIK_LEFT))  move.x = -0.5;
	if (input_->PushKey(DIK_RIGHT)) move.x = 0.5;
	//���W�ړ�
	worldTransform_.translation_ += move;
	//�ړ����E����
	const float kMoveLimitX = 30;
	const float kMoveLimitY = 10;
	worldTransform_.translation_.x = min(kMoveLimitX, max(worldTransform_.translation_.x, -kMoveLimitX));
	worldTransform_.translation_.y = min(kMoveLimitY, max(worldTransform_.translation_.y, -kMoveLimitY));
	Rotate();
	//�s��X�V
	MyMatrix::MatrixUpdate(worldTransform_);
	debugText_->Printf(
		"transform:(%f,%f,%f)", worldTransform_.translation_.x,worldTransform_.translation_.y,worldTransform_.translation_.z);
	//�L�����N�^�[�U������
	Attack();
	if (bullet_) {
		bullet_->Update();
	}
}

void Player::Draw(ViewProjection viewprojection)
{
	model_->Draw(worldTransform_, viewprojection, textureHandle_);
	if (bullet_) {
		bullet_->Draw(viewprojection);
	}
}

void Player::Attack()
{
	if (input_->PushKey(DIK_SPACE)) {
		//�e�𐶐���������
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);
		//�e��o�^����
		bullet_ = newBullet;
	}
}

void Player::Rotate()
{
	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 rot = { 0,0,0 };
	//�ړ��x�N�g����ύX���鏈��
	if (input_->PushKey(DIK_LEFT))  rot.y = 0.5;
	if (input_->PushKey(DIK_RIGHT)) rot.y = -0.5;
	//���W�ړ�
	worldTransform_.rotation_ = rot;
}