#include "Skydome.h"
#include "Matrix.h"
#include <cassert>

void Skydome::Initialize(Model* model){
	assert(model);
	this->model_ = model;
	//���[���h�ϊ��̏�����
	worldTransform_.scale_ = { 100.0f,100.0f,100.0f };//x,y,z�����̃X�P�[�����O�ݒ�
	worldTransform_.rotation_ = { 0,0,0 };//x,y,z������̉�]�p��ݒ�
	worldTransform_.translation_ = { 0,0,60 };//x,y,z������̕��s�ړ���ݒ肷��
	worldTransform_.Initialize();
	MyMatrix::MatrixScale(worldTransform_);
	MyMatrix::MatrixRotation(worldTransform_);
	MyMatrix::MatrixTranslation(worldTransform_);
}

void Skydome::Update()
{
	MyMatrix::MatrixUpdate(worldTransform_);
}

void Skydome::Draw(ViewProjection viewprojection)
{
	model_->Draw(worldTransform_, viewprojection);
}

Skydome::~Skydome()
{
	//delete model_;
}
