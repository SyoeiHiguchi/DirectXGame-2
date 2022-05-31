#include "WorldTransform.h"
#include "MathUtility.h"
#include <cmath>


namespace MyMatrix
{
	inline void MatrixScale(WorldTransform& wtf)
	{
		Matrix4 matScale;//�X�P�[�����O�s���錾
		matScale.m[0][0] = wtf.scale_.x;//�X�P�[�����O�{�����s��ɐݒ�
		matScale.m[1][1] = wtf.scale_.y;
		matScale.m[2][2] = wtf.scale_.z;
		matScale.m[3][3] = 1;
		wtf.matWorld_ = MathUtility::Matrix4Identity();//�P�ʍs�����
		wtf.matWorld_ *= matScale;
		//wtf.TransferMatrix();//�s��̓]��
	}
	inline void MatrixTranslation(WorldTransform& wtf)
	{
		Matrix4 matTrans = MathUtility::Matrix4Identity();//���s�ړ��s���ݒ�
		matTrans.m[3][0] = wtf.translation_.x;//�ړ��ʂ��s��ɑ��
		matTrans.m[3][1] = wtf.translation_.y;
		matTrans.m[3][2] = wtf.translation_.z;
		wtf.matWorld_ *= matTrans;

	}
	inline void RotationXMatrix(WorldTransform& wtf)
	{
		Matrix4 matRotX = MathUtility::Matrix4Identity();;//x����]�s���錾
		matRotX.m[1][1] = cosf(wtf.rotation_.x);//x����]�s��̊e�v�f��ݒ肷��
		matRotX.m[1][2] = sinf(wtf.rotation_.x);
		matRotX.m[2][1] = -sinf(wtf.rotation_.x);
		matRotX.m[2][2] = cosf(wtf.rotation_.x);
		wtf.matWorld_ *= matRotX;
	}
	inline void RotationYMatrix(WorldTransform& wtf)
	{
		Matrix4 matRotY = MathUtility::Matrix4Identity();//y����]�s���錾
		matRotY.m[0][0] = cosf(wtf.rotation_.y);//y����]�s��̊e�v�f��ݒ肷��
		matRotY.m[2][0] = sinf(wtf.rotation_.y);
		matRotY.m[0][2] = -sinf(wtf.rotation_.y);
		matRotY.m[2][2] = cosf(wtf.rotation_.y);
		wtf.matWorld_ *= matRotY;
	}
	inline void RotationZMatrix(WorldTransform& wtf)
	{
		Matrix4 matRotZ = MathUtility::Matrix4Identity();;//z����]�s���錾
		matRotZ.m[0][0] = cosf(wtf.rotation_.z);//z����]�s��̊e�v�f��ݒ肷��
		matRotZ.m[0][1] = sinf(wtf.rotation_.z);
		matRotZ.m[1][0] = -sinf(wtf.rotation_.z);
		matRotZ.m[1][1] = cosf(wtf.rotation_.z);
		wtf.matWorld_ *= matRotZ;
	}
	inline void MatrixRotation(WorldTransform& wtf)
	{
		RotationZMatrix(wtf);
		RotationXMatrix(wtf);
		RotationYMatrix(wtf);
	}
	inline void MatrixUpdate(WorldTransform& wtf)
	{
		MatrixScale(wtf);
		MatrixRotation(wtf);
		MatrixTranslation(wtf);
		wtf.TransferMatrix();//�s��̓]��
	}
}

