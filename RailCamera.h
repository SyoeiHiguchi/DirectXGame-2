#pragma once
#include <3d/WorldTransform.h>
#include <3d/ViewProjection.h>
#include <DebugText.h>
/// <summary>
/// レールカメラ
/// </summary>
class RailCamera{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector3 worldtransform, Vector3 radian, ViewProjection* viewprojection);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// ゲッター
	/// </summary>
	/// <returns>Matrix4</returns>
	Matrix4 GetMatrix4() { return worldTransform_.matWorld_; }

	const WorldTransform& GetWorldTransform() { return worldTransform_; }
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	//デバッグテキスト
	DebugText* debugText_ = nullptr;
};

