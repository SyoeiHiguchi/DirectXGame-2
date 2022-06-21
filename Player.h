#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <input/Input.h>
#include <2d/DebugText.h>
#include <assert.h>
#include "PlayerBullet.h"
#include <memory>
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
	/// <summary>
	/// ���W�̃Q�b�^�[
	/// </summary>
	/// <returns></returns>
	Vector3 GetTransform();
private:
	/// <summary>
	///	�`��
	/// </summary>
	void Attack();
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
	//�e
	std::list<std::unique_ptr<PlayerBullet>> bullets_;

	void Rotate();
	
};

