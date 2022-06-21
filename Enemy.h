#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <input/Input.h>
#include <2d/DebugText.h>
#include <assert.h>
#include <memory>
#include "EnemyBullet.h"

enum class Phase {
	Approach,//�ڋ߂���
	Leave,//���E����
};

class Enemy
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	///	�`��
	/// </summary>
	void Draw(ViewProjection viewprojection);
	/// <summary>
	///	�ړ�������֐�
	/// </summary>
	void Move(Vector3 vec);
	/// <summary>
	///	���W��getter
	/// </summary>
	Vector3 Tramsform() { return worldTransform_.translation_; };
	/// <summary>
	///	�ʔ���
	/// </summary>
	void Fire();
	/// <summary>
	///	�ڋ߃t�F�[�Y������
	/// </summary>
	void ApproachPhaseInitialize();
	void ApproachPhaseUpdate();

	~Enemy();//�f�X�g���N�^
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//EnemyState* state_;
	// 
	//�e
	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	//���ˊ��o
	static const int kFireInterval = 60;
	//���˃^�C�}�[
	int32_t fireTimer_ = 0;

	//�t�F�[�Y
	Phase phase_ = Phase::Approach;

	static void(Enemy::*spFuncTable[])();
};

