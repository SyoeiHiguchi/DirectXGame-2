#include "EnemyStateLeave.h"
#include "Enemy.h"

void EnemyStateLeave::Action(Enemy* enemy)
{
	//�ړ�(�x�N�g�������Z)
	Vector3 vec = { 4,1,3 };
	enemy->Move(vec);
}
