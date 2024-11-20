#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include <vector>
#include "Camera.h"

/// <summary>
/// �C���X�^���X��
/// </summary>
Camera::Camera()
{
	// �O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
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
/// ������
/// </summary>
void Camera::Initialize()
{
	SetCameraPositionAndTarget_UpVecY(AimPosition, LookPosition);

	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();
}

/// <summary>
/// �X�V
/// </summary>
void Camera::Update(const VECTOR& playerPosition,const VECTOR& enemyPosition)
{
	//���[�v���g���ăJ�������ړ�
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
/// �`��
/// </summary>
void Camera::Draw()
{
}

/// <summary>
/// ���[�v
/// </summary>
/// <param name="playerPosition"></param>
void Camera::Leap(const VECTOR& playerPosition, const VECTOR& enemyPosition)
{
	VECTOR AimPosition = VGet(0, 0, 0);		//���_
	VECTOR LookPosition = VGet(0, 0, 0);	//������W

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