#pragma once
#include "BaseEnemyState.h"
class EnemyStateLeave :
    public BaseEnemyState
{
    void Action(Enemy* enemy);
};

