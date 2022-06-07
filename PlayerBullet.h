#pragma once
#include "WorldTransform.h"
#include "Model.h"

#include <input/Input.h>
#include <2d/DebugText.h>
#include <assert.h>
class PlayerBullet
{
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name = "model">���f��</pram>
	/// <param name = "position">�������W</pram>
	void Initialize(Model* model, const Vector3& position);
	/// <summary>
	///  �X�V
	/// </summary>
	void Update();
	/// <summary>
	///  �`��
	/// </summary>
	void Draw(const ViewProjection& viewProjection);
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

