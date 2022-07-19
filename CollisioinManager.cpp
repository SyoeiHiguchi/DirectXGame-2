#include "CollisioinManager.h"
#include "Enemy.h"
#include "Player.h" 
#include "Vector3.h"
#include "Collider.h"

void CollisioinManager::CheckAllCollisions(){
	//リスト内のペアを総当たり
	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA) {
		//イテレーターAからコライダーAを取得する
		Collider* a = *itrA;
		//イテレーターBはイテレーターAの次の要素から回す(重複判定を回避)
		std::list<Collider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != colliders_.end(); ++itrB) {
			//イテレーターBからコライダーBを取得
			Collider* b = *itrB;
			//ペアの当たり判定
			CheckOnCollisions(a, b);

		}
	}
}

void CollisioinManager::PushBack(Collider* collider){
	colliders_.push_back(collider);
}

void CollisioinManager::CheckOnCollisions(Collider* A, Collider* B){
	//座標Aと座標Bの距離を求める
	if ((A->collisionConfig_.GetcollisionAttribute() & B->collisionConfig_.GetCollisionMask())
		|| (B->collisionConfig_.GetcollisionAttribute() & A->collisionConfig_.GetCollisionMask())) {
		return;
	}
	Vector3 Dir = A->GetWorldPosition() - B->GetWorldPosition();
	float rad = A->GetRadius() + B->GetRadius();
	bool collision = Dir.x * Dir.x + Dir.y * Dir.y + Dir.z * Dir.z <= rad * rad;
	if (collision) {
		//自弾の衝突時コールバックを呼び出す
		A->OnCollision();
		//敵弾の衝突時コールバックを呼び出す
		B->OnCollision();
	}
}
