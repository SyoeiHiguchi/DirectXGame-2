#include "Skydome.h"
#include "Matrix.h"
#include <cassert>

void Skydome::Initialize(Model* model){
	assert(model);
	this->model_ = model;
	//ワールド変換の初期化
	worldTransform_.scale_ = { 100.0f,100.0f,100.0f };//x,y,z方向のスケーリング設定
	worldTransform_.rotation_ = { 0,0,0 };//x,y,z軸周りの回転角を設定
	worldTransform_.translation_ = { 0,0,60 };//x,y,z軸周りの平行移動を設定する
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
