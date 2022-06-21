#pragma once
#include <functional>

/// <summary>
/// ��������
/// </summary>
class TimedCall{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TimedCall(std::function<void(void)> f, uint32_t time);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �����Ȃ�true��Ԃ�
	/// </summary>
	bool IsFinished() { return finishdFlag_; };
private:
	//�R�[���o�b�N
	std::function<void(void)> f_;
	//�c�莞��
	uint32_t time_;
	//�����t���O
	bool finishdFlag_ = false;

};

