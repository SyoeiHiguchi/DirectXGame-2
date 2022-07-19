#include "RailCamera.h"
#include "Matrix.h"

void RailCamera::Initialize(Vector3 worldtranslation,Vector3 radian, ViewProjection* viewprojection){
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = worldtranslation;
	worldTransform_.rotation_ = radian;
	worldTransform_.scale_ = Vector3(1, 1, 1);

	//ビュープロジェクションの初期化
	viewProjection_ = viewprojection;
	viewProjection_->Initialize();


	//デバッグテキスト
	debugText_ = DebugText::GetInstance();
}

void RailCamera::Update(){
	worldTransform_.translation_ += Vector3(0, 0, 0.1f);
	//行列更新
	MyMatrix::MatrixUpdate(worldTransform_);

	//ビュープロジェクションの処理
	viewProjection_->eye.x = worldTransform_.matWorld_.m[3][0];
	viewProjection_->eye.y = worldTransform_.matWorld_.m[3][1];
	viewProjection_->eye.z = worldTransform_.matWorld_.m[3][2];

	//ワールド前方ベクトル
	Vector3 forward(0, 0, 1.0f);
	//レールカメラの回転を反映
	forward = MyMatrix::VectorProduct(forward, worldTransform_);
	//視点から前方に適当な距離進んだ位置が注視点
	viewProjection_->target = viewProjection_->eye + forward;

	Vector3 up(0, 1.0f, 0);
	//レールカメラの回転を反映(レールカメラの上方ベクトル
	viewProjection_->up = MyMatrix::VectorProduct(up, worldTransform_);
	//ビュープロジェクションを更新
    viewProjection_->UpdateMatrix();
	viewProjection_->TransferMatrix();

	debugText_->SetPos(120, 0);
	debugText_->Printf(
		"RailCamera:(%f,%f,%f)", viewProjection_->eye.x,viewProjection_->eye.y,viewProjection_->eye.z);
}
