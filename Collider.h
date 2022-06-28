#pragma once
/// <summary>
/// �Փ˔���I�u�W�F�N�g
/// </summary>
class Collider{
public:
	/// <summary>
	/// �Փˎ��ɌĂ΂��֐�
	/// </summary>
	virtual void OnCollision(){};
	/// <summary>
	/// ���[���h���W���擾����
	/// </summary>
	virtual Vector3 GetWorldPosition() = 0;
	/// <summary>
	/// ���a��ݒ�
	/// </summary>
	/// <param name="radius">���a</param>
	void SetRadius(float radius) { this->radius_ = radius; }
	/// <summary>
	/// ���a���擾
	/// </summary>
	/// <returns>float</returns>
	float GetRadius() { return radius_; }
private:
	//�Փ˔��a
	float radius_ = 1;
};