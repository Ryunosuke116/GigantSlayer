#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include <vector>
#include "Effect.h"

/// <summary>
/// �C���X�^���X
/// </summary>
Effect::Effect()
{
    position = VGet(0, 0, 0);
    time = 0;
    playingEffectHandle = -1;
    resourceHandle = -1;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Effect::~Effect()
{

}

/// <summary>
/// ������
/// </summary>
void Effect::Initialize(const char* path,float magnification,const VECTOR& objectPosition)
{
    resourceHandle = LoadEffekseerEffect(path, magnification);
    position = VGet(objectPosition.x, objectPosition.y, objectPosition.z);

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="objectPosition"></param>
void Effect::PositionUpdate(const VECTOR& objectPosition)
{
    position = VGet(objectPosition.x, objectPosition.y, objectPosition.z);


    // �Đ����̃G�t�F�N�g���ړ�����B
    SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y, position.z);

}

void Effect::PlayEffectUpdate()
{
  // Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
  UpdateEffekseer3D();

}

/// <summary>
/// �`��
/// </summary>
void Effect::Draw()
{
    // Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
    //DrawEffekseer3D_Draw(playingEffectHandle);
    DrawEffekseer3D();

}

/// <summary>
/// �|�W�V������ۑ�
/// </summary>
/// <param name="setPosition"></param>
void Effect::SetPosition(const VECTOR setPosition)
{
    position = VGet(setPosition.x, setPosition.y, setPosition.z);
}

/// <summary>
/// �g�嗦
/// </summary>
/// <param name="scale"></param>
void Effect::SetScale(VECTOR scale)
{
    SetScalePlayingEffekseer3DEffect(playingEffectHandle, scale.x, scale.y, scale.z);
}

/// <summary>
///  �G�t�F�N�g���Đ�
/// </summary>
void Effect::PlayEffect()
{
    // �G�t�F�N�g���Đ�����B
    playingEffectHandle = PlayEffekseer3DEffect(resourceHandle);
}

/// <summary>
/// �Đ����̃��[�V�������~����
/// </summary>
void Effect::StopEffect()
{
    StopEffekseer3DEffect(playingEffectHandle);
}

void Effect::SetSpeed(float speed)
{
    SetSpeedPlayingEffekseer3DEffect(playingEffectHandle, speed);
}

/// <summary>
/// �p�x
/// </summary>
/// <param name="setPosition"></param>
void Effect::SetRotation(VECTOR setPosition)
{
    SetRotationPlayingEffekseer3DEffect(playingEffectHandle, setPosition.x, setPosition.y, setPosition.z);
}