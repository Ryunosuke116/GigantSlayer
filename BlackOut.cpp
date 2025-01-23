#include "BlackOut.h"
#include "DxLib.h"

/// <summary>
/// �C���X�g���N�^
/// </summary>
BlackOut::BlackOut()
{
    alpha = 0;
    isLightChange = false;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BlackOut::~BlackOut()
{

}

/// <summary>
/// ������
/// </summary>
void BlackOut::Initialize()
{
    alpha = 0;
    isLightChange = false;
}

/// <summary>
/// �Ó]
/// </summary>
void BlackOut::BlackOutUpdate(float addAlpha)
{

    if (!(alpha >= 300))
    {
        alpha += addAlpha;
    }
}

/// <summary>
/// ���]
/// </summary>
void BlackOut::LightChangeUpdate(float addAlpha)
{

    if (!(alpha <= 0))
    {   
       alpha -= addAlpha;
    }
}

/// <summary>
/// �`��
/// </summary>
void BlackOut::Draw()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

