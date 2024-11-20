#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include <vector>
#include "Camera.h"

/// <summary>
/// インスタンス化
/// </summary>
Camera::Camera()
{
	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	//奥行0.1～1000までをカメラの描画範囲とする
	SetCameraNearFar(0.1f, 10000.0f);

	AimPosition = VGet(0, 20, -40);
	LookPosition = VGet(0, 0, 0);
	x = 0;
	y = 20;
	z = -40;


}

/// <summary>
/// 
/// </summary>
Camera::~Camera()
{

}

/// <summary>
/// 初期化
/// </summary>
void Camera::Initialize()
{
	SetCameraPositionAndTarget_UpVecY(AimPosition, LookPosition);

	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
}

/// <summary>
/// 更新
/// </summary>
void Camera::Update(const VECTOR& playerPosition,const VECTOR& enemyPosition)
{
	//ラープを使ってカメラを移動
	Leap(playerPosition,enemyPosition);
	if (CheckHitKey(KEY_INPUT_2))
	{
		AimPosition.y = 90;
	}
	else
	{
		y = 20;
	}

	SetCameraPositionAndTarget_UpVecY(AimPosition,LookPosition);

}

/// <summary>
/// 描画
/// </summary>
void Camera::Draw()
{
}

/// <summary>
/// ラープ
/// </summary>
/// <param name="playerPosition"></param>
void Camera::Leap(const VECTOR& playerPosition, const VECTOR& enemyPosition)
{
	VECTOR AimPosition = VGet(0, 0, 0);		//視点
	VECTOR LookPosition = VGet(0, 0, 0);	//見る座標

	AimPosition = VGet(playerPosition.x, 20, playerPosition.z - 30);
	LookPosition = VGet(playerPosition.x, 0, enemyPosition.z);

	VECTOR SubAimPosition = VSub(AimPosition, this->AimPosition);
	VECTOR SubLookPosition = VSub(LookPosition, this->LookPosition);
	VECTOR scaleAimPosition = VGet(0, 0, 0);
	VECTOR scaleLookPosition = VGet(0, 0, 0);

	scaleAimPosition = VScale(SubAimPosition, 0.1f);
	scaleLookPosition = VScale(SubLookPosition, 0.1f);
	this->AimPosition = VAdd(this->AimPosition, scaleAimPosition);
	this->LookPosition = VAdd(this->LookPosition, scaleLookPosition);
}