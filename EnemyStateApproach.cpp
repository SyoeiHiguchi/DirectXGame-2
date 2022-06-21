#include "EnemyStateApproach.h"
#include "Enemy.h"
#include "EnemyStateLeave.h"

void EnemyStateApproach::Action(Enemy* enemy){
	Vector3 vec = { 0,0,-0.1 };
	enemy->Move(vec);
	//�K��̈ʒu�ɓ��B�����痣�E
	if (enemy->Tramsform().z < -10.0f) {
		enemy->TimeListReset();
		enemy->ChangeState(new EnemyStateLeave);
	}
}
