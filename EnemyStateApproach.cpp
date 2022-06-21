#include "EnemyStateApproach.h"
#include "Enemy.h"
#include "EnemyStateLeave.h"

void EnemyStateApproach::Action(Enemy* enemy){
	Vector3 vec = { 0,0,-0.1 };
	enemy->Move(vec);
	//‹K’è‚ÌˆÊ’u‚É“ž’B‚µ‚½‚ç—£’E
	if (enemy->Tramsform().z < -10.0f) {
		enemy->TimeListReset();
		enemy->ChangeState(new EnemyStateLeave);
	}
}
