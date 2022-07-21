#pragma once
#include <memory>
#include "EnemyBullet.h"


class EnemyBullet;
class GameScene;

class BulletManager{
public:
	

	/// <summary>
	/// �G�e��ǉ�����
	/// </summary>
	/// <param name="enemyBullet"></param>
	void AddEnemyBullet(std::unique_ptr<EnemyBullet>& enemyBullet);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	///	�`�揈��
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// �e���X�g���擾����
	/// </summary>
	/// <returns></returns>
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; };
private:
	GameScene* gameScene_ = nullptr;
	std::list<std::unique_ptr<EnemyBullet>> bullets_;



public://�V���O���g��
	BulletManager(const BulletManager& obj) = delete;
	BulletManager& operator=(const BulletManager& obj) = delete;
	static BulletManager* GetInstance();
private:
	BulletManager(){};
	~BulletManager(){};


};

