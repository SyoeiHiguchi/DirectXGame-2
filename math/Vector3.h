#pragma once
class Vector3
{
public:
	float x;//x����
	float y;//y����
	float z;//z����
public:
	//�R���X�g���N�^
	Vector3();//�[���x�N�g���Ƃ��Đ���
	Vector3(float x, float y,float z);//x������y�������w�肵�Đ���

	//�����o�֐�
	
	/// <summary>
	/// �m�����̒��������߂�
	/// </summary>
	/// <returns>float</returns>
	float length() const;
	/// <summary>
	/// ���K������
	/// </summary>
	/// <returns>Vector3</returns>
	Vector3& normalize();
	/// <summary>
	/// ���ς����߂�
	/// </summary>
	/// <returns>float</returns>
	float dot(const Vector3& v) const;
	/// <summary>
	/// �O�ς����߂�
	/// </summary>
	/// <returns>Vector3</returns>
	Vector3 cross(const Vector3& v) const;
	/// <summary>
	/// ���ʐ��`�ۊ�
	/// </summary>
	/// <returns></returns>
	Vector3 Slerp(const Vector3& v, const Vector3& v2, float t);

	//�P�����Z�q�I�[�o�[���[�h
	Vector3 operator+() const;
	Vector3 operator-() const;
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);
};

//�Q�����Z�q�I�[�o�[���[�h
//*�����Ȉ����i�����̌^�Ə����j�̃p�^�[���ɑΉ����邽�߁A�ȉ��̗l�ɏ������Ă���
const Vector3 operator+(const Vector3& v1, const Vector3& v2);
const Vector3 operator-(const Vector3& v1, const Vector3& v2);
const Vector3 operator*(const Vector3& v, float s);
const Vector3 operator*(float s, const Vector3& v);
const Vector3 operator/(const Vector3& v, float s);