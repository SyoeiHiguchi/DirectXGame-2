#include "BulletManager.h"
#include "GameScene.h"


void BulletManager::AddEnemyBullet(std::unique_ptr<EnemyBullet>& enemyBullet){
	bullets_.push_back(std::move(enemyBullet));
}

void BulletManager::Update(){
	//�f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		return bullet->IsDead();
		});
	//�e�̍X�V����
	for (auto& bullet : bullets_) {
		bullet->Update();
	}

}

void BulletManager::Draw(const ViewProjection& viewProjection){
	for (auto& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

BulletManager* BulletManager::GetInstance()
{
	static BulletManager instance;
	return &instance;
}


