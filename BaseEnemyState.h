#pragma once

class Enemy;

class BaseEnemyState{
public:
	virtual void Action(Enemy* enemy) = 0;
};

