#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <input/Input.h>
#include <2d/DebugText.h>
#include <assert.h>
#include <memory>
#include "EnemyBullet.h"
#include "TimedCall.h"

class BaseEnemyState;
//���L�����̑O���錾
class Player;


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
	///	�ڋ߃t�F�[�Y������
	/// </summary>
	void ApproachPhaseInitialize();
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
	///	��Ԃ�ύX����
	/// </summary>
	void ChangeState(BaseEnemyState* newState);
	/// <summary>
	/// �e�𔭎˂��A�^�C�}�[�����Z�b�g����֐�
	/// </summary>
	void BulettTimeReset();
	/// <summary>
	/// �^�C�}�[��list�����Z�b�g����֐�
	/// </summary>
	void TimeListReset();
	/// <summary>
	/// �v���C���[�̃Z�b�^�[
	/// </summary>
	void SetPlayer(Player* player) { player_ = player; }
	/// ���W�̃Q�b�^�[
	/// </summary>
	/// <returns></returns>
	Vector3 GetTransform();

	~Enemy();//�f�X�g���N�^
private:
	/// <summary>
	///	�ʔ���
	/// </summary>
	void Fire();
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//���L����
	Player* player_ = nullptr;
	
	//���
	BaseEnemyState* state_;
	
	//�e
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	//���ˊ��o
	static const int kFireInterval = 60;
	//���˃^�C�}�[
	int32_t fireTimer_ = 0;

	//�t�F�[�Y
	Phase phase_ = Phase::Approach;

	//���������̃��X�g
	std::list<std::unique_ptr<TimedCall>> timedCalls_;
};

