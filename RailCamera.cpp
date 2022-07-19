#include "RailCamera.h"
#include "Matrix.h"

void RailCamera::Initialize(Vector3 worldtranslation,Vector3 radian, ViewProjection* viewprojection){
	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	worldTransform_.translation_ = worldtranslation;
	worldTransform_.rotation_ = radian;
	worldTransform_.scale_ = Vector3(1, 1, 1);

	//�r���[�v���W�F�N�V�����̏�����
	viewProjection_ = viewprojection;
	viewProjection_->Initialize();


	//�f�o�b�O�e�L�X�g
	debugText_ = DebugText::GetInstance();
}

void RailCamera::Update(){
	worldTransform_.translation_ += Vector3(0, 0, 0.1f);
	//�s��X�V
	MyMatrix::MatrixUpdate(worldTransform_);

	//�r���[�v���W�F�N�V�����̏���
	viewProjection_->eye.x = worldTransform_.matWorld_.m[3][0];
	viewProjection_->eye.y = worldTransform_.matWorld_.m[3][1];
	viewProjection_->eye.z = worldTransform_.matWorld_.m[3][2];

	//���[���h�O���x�N�g��
	Vector3 forward(0, 0, 1.0f);
	//���[���J�����̉�]�𔽉f
	forward = MyMatrix::VectorProduct(forward, worldTransform_);
	//���_����O���ɓK���ȋ����i�񂾈ʒu�������_
	viewProjection_->target = viewProjection_->eye + forward;

	Vector3 up(0, 1.0f, 0);
	//���[���J�����̉�]�𔽉f(���[���J�����̏���x�N�g��
	viewProjection_->up = MyMatrix::VectorProduct(up, worldTransform_);
	//�r���[�v���W�F�N�V�������X�V
    viewProjection_->UpdateMatrix();
	viewProjection_->TransferMatrix();

	debugText_->SetPos(120, 0);
	debugText_->Printf(
		"RailCamera:(%f,%f,%f)", viewProjection_->eye.x,viewProjection_->eye.y,viewProjection_->eye.z);
}
