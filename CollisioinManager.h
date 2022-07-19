#pragma once
#include <list>


class Collider;

class CollisioinManager{
public:
	/// <summary>
	/// �Փ˔���Ɖ���
	/// </summary>
	void CheckAllCollisions();

	void PushBack(Collider* collider);

private:
	std::list<Collider*> colliders_;
private:
	/// <summary>
	/// �R���C�_�[��̏Փ˔���Ɖ���
	/// </summary>
	/// <param name="A">�R���C�_�[A</param>
	/// <param name="B">�R���C�_�[B</param>
	void CheckOnCollisions(Collider* A, Collider* B);
};

