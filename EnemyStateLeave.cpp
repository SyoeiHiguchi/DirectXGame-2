#include "EnemyStateLeave.h"
#include "Enemy.h"

void EnemyStateLeave::Action(Enemy* enemy)
{
	//ˆÚ“®(ƒxƒNƒgƒ‹‚ð‰ÁŽZ)
	Vector3 vec = { 0.1,0.1,0.1 };
	enemy->Move(vec);
}
