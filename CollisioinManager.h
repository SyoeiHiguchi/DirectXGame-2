#pragma once
#include <list>


class Collider;

class CollisioinManager{
public:
	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

	void PushBack(Collider* collider);

private:
	std::list<Collider*> colliders_;
private:
	/// <summary>
	/// コライダー二つの衝突判定と応答
	/// </summary>
	/// <param name="A">コライダーA</param>
	/// <param name="B">コライダーB</param>
	void CheckOnCollisions(Collider* A, Collider* B);
};

