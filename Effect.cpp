#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include <vector>
#include "Effect.h"

/// <summary>
/// インスタンス
/// </summary>
Effect::Effect()
{
    position = VGet(0, 0, 0);
    time = 0;
    playingEffectHandle = -1;
    resourceHandle = -1;
}

/// <summary>
/// デストラクタ
/// </summary>
Effect::~Effect()
{

}

/// <summary>
/// 初期化
/// </summary>
void Effect::Initialize(const char* path,float magnification,const VECTOR& objectPosition)
{
    resourceHandle = LoadEffekseerEffect(path, magnification);
    position = VGet(objectPosition.x, objectPosition.y, objectPosition.z);

}

/// <summary>
/// 更新
/// </summary>
/// <param name="objectPosition"></param>
void Effect::PositionUpdate(const VECTOR& objectPosition)
{
    position = VGet(objectPosition.x, objectPosition.y, objectPosition.z);


    // 再生中のエフェクトを移動する。
    SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y, position.z);

}

void Effect::PlayEffectUpdate()
{
  // Effekseerにより再生中のエフェクトを更新する。
  UpdateEffekseer3D();

}

/// <summary>
/// 描画
/// </summary>
void Effect::Draw()
{
    // Effekseerにより再生中のエフェクトを描画する。
    //DrawEffekseer3D_Draw(playingEffectHandle);
    DrawEffekseer3D();

}

/// <summary>
/// ポジションを保存
/// </summary>
/// <param name="setPosition"></param>
void Effect::SetPosition(const VECTOR setPosition)
{
    position = VGet(setPosition.x, setPosition.y, setPosition.z);
}

/// <summary>
/// 拡大率
/// </summary>
/// <param name="scale"></param>
void Effect::SetScale(VECTOR scale)
{
    SetScalePlayingEffekseer3DEffect(playingEffectHandle, scale.x, scale.y, scale.z);
}

/// <summary>
///  エフェクトを再生
/// </summary>
void Effect::PlayEffect()
{
    // エフェクトを再生する。
    playingEffectHandle = PlayEffekseer3DEffect(resourceHandle);
}

/// <summary>
/// 再生中のモーションを停止する
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
/// 角度
/// </summary>
/// <param name="setPosition"></param>
void Effect::SetRotation(VECTOR setPosition)
{
    SetRotationPlayingEffekseer3DEffect(playingEffectHandle, setPosition.x, setPosition.y, setPosition.z);
}