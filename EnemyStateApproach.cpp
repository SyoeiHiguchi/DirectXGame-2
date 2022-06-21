#include "EnemyStateApproach.h"
#include "Enemy.h"
#include "EnemyStateLeave.h"

void EnemyStateApproach::Action(Enemy* enemy){

	if (fastFlag_) {
		enemy->ApproachPhaseInitialize();
		fastFlag_ = false;
	}


	Vector3 vec = { 0,0,-0.1 };
	enemy->Move(vec);
	//�K��̈ʒu�ɓ��B�����痣�E
	if (enemy->GetTransform().z < -30.0f) {
		enemy->TimeListReset();
		enemy->ChangeState(new EnemyStateLeave);
	}
}
