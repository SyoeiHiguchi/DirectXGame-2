#pragma once
#include <3d/WorldTransform.h>
#include <3d/ViewProjection.h>
#include <DebugText.h>
/// <summary>
/// ���[���J����
/// </summary>
class RailCamera{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Vector3 worldtransform, Vector3 radian, ViewProjection* viewprojection);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �Q�b�^�[
	/// </summary>
	/// <returns>Matrix4</returns>
	Matrix4 GetMatrix4() { return worldTransform_.matWorld_; }

	const WorldTransform& GetWorldTransform() { return worldTransform_; }
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//�r���[�v���W�F�N�V����
	ViewProjection* viewProjection_ = nullptr;
	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;
};

