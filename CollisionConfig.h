#pragma once

#include<cstdint>

//�v���C���[�w�c
const uint32_t kCollisionAttributePlayer = 0b1;
//�G�w�c
const uint32_t kCollisionAttributeEnemy = 0b1 << 1;

class CollsionConfig {
public:
	//�Փˑ���(����)���擾
	uint32_t GetcollisionAttribute() { return collisionAttribute_; }
	//�Փˑ���(����)��ݒ�
	void SetcollisionAttribute(uint32_t set) { collisionAttribute_ = set; }
	// �Փˑ���(����)���擾
	uint32_t GetCollisionMask() { return collisionAttribute_; }
	// �Փˑ���(����)��ݒ�
	void SetCollisionMask(uint32_t set) { CollisionMask_ = set; }
private:
	//�Փˑ���(����)���擾
	uint32_t collisionAttribute_ = 0xffffffff;
	//�Փˑ���(����)���擾
	uint32_t CollisionMask_ = 0xffffffff;

};