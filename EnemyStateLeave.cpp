#include "EnemyStateLeave.h"
#include "Enemy.h"

void EnemyStateLeave::Action(Enemy* enemy)
{
	//移動(ベクトルを加算)
	Vector3 vec = { 4,1,3 };
	enemy->Move(vec);
}
