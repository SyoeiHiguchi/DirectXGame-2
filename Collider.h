#pragma once
/// <summary>
/// 衝突判定オブジェクト
/// </summary>
class Collider{
public:
	/// <summary>
	/// 衝突時に呼ばれる関数
	/// </summary>
	virtual void OnCollision(){};
	/// <summary>
	/// ワールド座標を取得する
	/// </summary>
	virtual Vector3 GetWorldPosition() = 0;
	/// <summary>
	/// 半径を設定
	/// </summary>
	/// <param name="radius">半径</param>
	void SetRadius(float radius) { this->radius_ = radius; }
	/// <summary>
	/// 半径を取得
	/// </summary>
	/// <returns>float</returns>
	float GetRadius() { return radius_; }
private:
	//衝突半径
	float radius_ = 1;
};