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
	SetCameraNearFar(3.5f, 5000.0f);

	AimPosition = VGet(0, 20, -40);
	LookPosition = VGet(0, 0, 0);
	x = 0;
	y = 5;
	z = 0;
	addY = 1.0f;
	time = 0;
	isChangeUpdate = false;
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

	isChangeUpdate = false;
	AimPosition = VGet(2, 4, 5);
	
	LookPosition = VGet(0, 20, 0);
	x = 0;
	y = 5;
	z = 0;
	addY = 1.0f;
	time = 0;
	isChangeUpdate = false;
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

void Camera::StartUpdate(Enemy& enemy)
{

	time++;

	
	if (time >= 30 && time <= 80)
	{
		ChangeLightTypeDir(VGet(0, -1, 0));
		if (LookPosition.y >= 5)
		{
			LookPosition.y -= 0.5f;
		}
		if(LookPosition.y <= 5)
		{
			LookPosition.y = 5;
		}
	}
	else if (time >= 80 && time <= 130)
	{
		ChangeLightTypeDir(VGet(0, -1, 0));
		AimPosition = VGet(2, 4, 5);
		LookPosition = VGet(0, 5, 0);
	}
	else if (time >= 130 && time <= 420)
	{
		if (time == 140)
		{
			ChangeLightTypeDir(VGet(0.577350f, -0.577350f, 0.577350f));
		}

		y -= addY;
		addY -= 0.15f;
	
		z += 1.2f;

		if (y >= 20)
		{
			y = 20;
		}
		if (z >= 50)
		{
			z = 50;
		}

		LookPosition = VGet(0, y, z);
	}
	else if (time >= 420)
	{
		time = 0;
		isChangeUpdate = true;
		enemy.ResetTime();
	}

	SetCameraPositionAndTarget_UpVecY(AimPosition, LookPosition);
}

/// <summary>
/// ゲームクリア時のカメラ
/// </summary>
/// <param name="enemyPosition"></param>
void Camera::EndUpdate(const VECTOR& enemyPosition)
{
	LookPosition = VGet(enemyPosition.x, enemyPosition.y, enemyPosition.z);

	if (time <= 120)
	{
		AimPosition = VGet(36, 40, 16);
	}
	if (time > 120 && time <= 240)
	{
		AimPosition = VGet(-29, 40, 7);
	}

	time++;
	SetCameraPositionAndTarget_UpVecY(AimPosition, LookPosition);

}


/// <summary>
/// タイトルカメラ
/// </summary>
void Camera::TitleUpdate()
{

	if (CheckHitKey(KEY_INPUT_2))
	{
		AimPosition.y = 90;
	}
	else
	{
		y = 20;
	}

	SetCameraPositionAndTarget_UpVecY(AimPosition, LookPosition);
}



/// <summary>
/// 描画
/// </summary>
void Camera::Draw()
{
	printfDx("AimPosition.x %f\n", AimPosition.x);
	printfDx("AimPosition.y %f\n", AimPosition.y);
	printfDx("AimPosition.z %f\n", AimPosition.z);
	printfDx("LookPosition.x %f\n", LookPosition.x);
	printfDx("LookPosition.y %f\n", LookPosition.y);
	printfDx("LookPosition.z %f\n", LookPosition.z);
}

/// <summary>
/// ラープ
/// </summary>
/// <param name="playerPosition"></param>
void Camera::Leap(const VECTOR& playerPosition, const VECTOR& enemyPosition)
{
	VECTOR AimPosition = VGet(0, 0, 0);		//視点
	VECTOR LookPosition = VGet(0, 0, 0);	//見る座標
	float Aim_X = playerPosition.x / 2.5f;
	float Aim_Z = playerPosition.z / 2;

	AimPosition = VGet(Aim_X, 20, Aim_Z - 40);
	LookPosition = VGet(playerPosition.x, 0, enemyPosition.z - 20);

	VECTOR SubAimPosition = VSub(AimPosition, this->AimPosition);
	VECTOR SubLookPosition = VSub(LookPosition, this->LookPosition);
	VECTOR scaleAimPosition = VGet(0, 0, 0);
	VECTOR scaleLookPosition = VGet(0, 0, 0);

	scaleAimPosition = VScale(SubAimPosition, 0.1f);
	scaleLookPosition = VScale(SubLookPosition, 0.1f);
	this->AimPosition = VAdd(this->AimPosition, scaleAimPosition);
	this->LookPosition = VAdd(this->LookPosition, scaleLookPosition);
}