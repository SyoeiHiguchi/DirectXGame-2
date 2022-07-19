#include "CollisioinManager.h"
#include "Enemy.h"
#include "Player.h" 
#include "Vector3.h"
#include "Collider.h"

void CollisioinManager::CheckAllCollisions(){
	//���X�g���̃y�A�𑍓�����
	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA) {
		//�C�e���[�^�[A����R���C�_�[A���擾����
		Collider* a = *itrA;
		//�C�e���[�^�[B�̓C�e���[�^�[A�̎��̗v�f�����(�d����������)
		std::list<Collider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != colliders_.end(); ++itrB) {
			//�C�e���[�^�[B����R���C�_�[B���擾
			Collider* b = *itrB;
			//�y�A�̓����蔻��
			CheckOnCollisions(a, b);

		}
	}
}

void CollisioinManager::PushBack(Collider* collider){
	colliders_.push_back(collider);
}

void CollisioinManager::CheckOnCollisions(Collider* A, Collider* B){
	//���WA�ƍ��WB�̋��������߂�
	if ((A->collisionConfig_.GetcollisionAttribute() & B->collisionConfig_.GetCollisionMask())
		|| (B->collisionConfig_.GetcollisionAttribute() & A->collisionConfig_.GetCollisionMask())) {
		return;
	}
	Vector3 Dir = A->GetWorldPosition() - B->GetWorldPosition();
	float rad = A->GetRadius() + B->GetRadius();
	bool collision = Dir.x * Dir.x + Dir.y * Dir.y + Dir.z * Dir.z <= rad * rad;
	if (collision) {
		//���e�̏Փˎ��R�[���o�b�N���Ăяo��
		A->OnCollision();
		//�G�e�̏Փˎ��R�[���o�b�N���Ăяo��
		B->OnCollision();
	}
}
