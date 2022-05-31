#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Matrix.h"
#include <input/Input.h>
#include <2d/DebugText.h>
#include <assert.h>
/// <summary>
/// ���L����
/// </summary>
class Player
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model,uint32_t textureHandle);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	///	�`��
	/// </summary>
	void Draw(ViewProjection viewprojection);
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//���o�͂����邽��
	Input* input_ = nullptr;
	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;
	
};

