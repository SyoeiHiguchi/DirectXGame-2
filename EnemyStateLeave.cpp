#include "EnemyStateLeave.h"
#include "Enemy.h"

void EnemyStateLeave::Action(Enemy* enemy)
{
	//ˆÚ“®(ƒxƒNƒgƒ‹‚ð‰ÁŽZ)
	Vector3 vec = { 4,1,3 };
	enemy->Move(vec);
}
