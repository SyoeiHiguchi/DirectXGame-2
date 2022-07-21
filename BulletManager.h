#pragma once
#include <memory>
#include "EnemyBullet.h"


class EnemyBullet;
class GameScene;

class BulletManager{
public:
	

	/// <summary>
	/// 敵弾を追加する
	/// </summary>
	/// <param name="enemyBullet"></param>
	void AddEnemyBullet(std::unique_ptr<EnemyBullet>& enemyBullet);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	///	描画処理
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// 弾リストを取得する
	/// </summary>
	/// <returns></returns>
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; };
private:
	GameScene* gameScene_ = nullptr;
	std::list<std::unique_ptr<EnemyBullet>> bullets_;



public://シングルトン
	BulletManager(const BulletManager& obj) = delete;
	BulletManager& operator=(const BulletManager& obj) = delete;
	static BulletManager* GetInstance();
private:
	BulletManager(){};
	~BulletManager(){};


};

