#include "EnemyStateLeave.h"
#include "Enemy.h"

void EnemyStateLeave::Action(Enemy* enemy)
{
	//移動(ベクトルを加算)
	Vector3 vec = { 0.1,0.1,0.1 };
	enemy->Move(vec);
}
