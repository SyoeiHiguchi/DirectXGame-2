#pragma once
#include "BaseEnemyState.h"

class EnemyStateApproach :
    public BaseEnemyState
{
    void Action(Enemy* enemy);
};

