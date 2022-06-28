#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <input/Input.h>
#include <2d/DebugText.h>
#include <assert.h>
#include "Collider.h"

class EnemyBullet : public Collider {
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name = "model">���f��</pram>
	/// <param name = "position">�������W</pram>
	void Initialize(Model* model, const Vector3& position, const Vector3 velocity);
	/// <summary>
	///  �X�V
	/// </summary>
	void Update();
	/// <summary>
	///  �`��
	/// </summary>
	void Draw(const ViewProjection& viewProjection);
	/// <summary>
	/// ���W�̃Q�b�^�[
	/// </summary>
	/// <returns></returns>
	Vector3 GetWorldPosition();
	/// <summary>
	/// �Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	/// </summary>
	void OnCollision();

	bool IsDead() const { return isDead_; }
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
	//���x
	Vector3 velocity_;
	//����
	static const int32_t kLifeTime = 60 * 5;
	//�f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;
	//�f�X�t���O
	bool isDead_ = false;
};

