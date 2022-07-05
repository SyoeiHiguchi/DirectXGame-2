#pragma once

#include<cstdint>

//ƒvƒŒƒCƒ„[w‰c
const uint32_t kCollisionAttributePlayer = 0b1;
//“Gw‰c
const uint32_t kCollisionAttributeEnemy = 0b1 << 1;

class CollsionConfig {
public:
	//Õ“Ë‘®«(©•ª)‚ğæ“¾
	uint32_t GetcollisionAttribute() { return collisionAttribute_; }
	//Õ“Ë‘®«(©•ª)‚ğİ’è
	void SetcollisionAttribute(uint32_t set) { collisionAttribute_ = set; }
	// Õ“Ë‘®«(‘Šè)‚ğæ“¾
	uint32_t GetCollisionMask() { return collisionAttribute_; }
	// Õ“Ë‘®«(‘Šè)‚ğİ’è
	void SetCollisionMask(uint32_t set) { CollisionMask_ = set; }
private:
	//Õ“Ë‘®«(©•ª)‚ğæ“¾
	uint32_t collisionAttribute_ = 0xffffffff;
	//Õ“Ë‘®«(‘Šè)‚ğæ“¾
	uint32_t CollisionMask_ = 0xffffffff;

};