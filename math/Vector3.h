#pragma once
class Vector3
{
public:
	float x;//x成分
	float y;//y成分
	float z;//z成分
public:
	//コンストラクタ
	Vector3();//ゼロベクトルとして生成
	Vector3(float x, float y,float z);//x成分とy成分を指定して生成

	//メンバ関数
	
	/// <summary>
	/// ノルムの長さを求める
	/// </summary>
	/// <returns>float</returns>
	float length() const;
	/// <summary>
	/// 正規化する
	/// </summary>
	/// <returns>Vector3</returns>
	Vector3& normalize();
	/// <summary>
	/// 内積を求める
	/// </summary>
	/// <returns>float</returns>
	float dot(const Vector3& v) const;
	/// <summary>
	/// 外積を求める
	/// </summary>
	/// <returns>Vector3</returns>
	Vector3 cross(const Vector3& v) const;
	/// <summary>
	/// 球面線形保管
	/// </summary>
	/// <returns></returns>
	Vector3 Slerp(const Vector3& v, const Vector3& v2, float t);

	//単項演算子オーバーロード
	Vector3 operator+() const;
	Vector3 operator-() const;
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);
};

//２項演算子オーバーロード
//*いろんな引数（引数の型と順序）のパターンに対応するため、以下の様に準備している
const Vector3 operator+(const Vector3& v1, const Vector3& v2);
const Vector3 operator-(const Vector3& v1, const Vector3& v2);
const Vector3 operator*(const Vector3& v, float s);
const Vector3 operator*(float s, const Vector3& v);
const Vector3 operator/(const Vector3& v, float s);