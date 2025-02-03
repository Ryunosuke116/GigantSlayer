#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include <vector>
#include <math.h>    
#include "Calculation.h"

void Calculation::UpdateAngle(const VECTOR& direction, float& angle, int& modelHandle)
{
    // プレイヤーの移動方向にモデルの方向を近づける
    float targetAngle;			// 目標角度
    float difference;			// 目標角度と現在の角度との差
    float nowAngle = angle;

    // 目標の方向ベクトルから角度値を算出する
    if (VSize(direction) != 0)
    {
        targetAngle = atan2f(-direction.x, -direction.z);
    }

    // 目標の角度と現在の角度との差を割り出す
    // 最初は単純に引き算
    difference = targetAngle - nowAngle;


    // ある方向からある方向の差が１８０度以上になることは無いので
    // 差の値が１８０度以上になっていたら修正する
    if (difference < -DX_PI_F)
    {
        difference += DX_TWO_PI_F;
    }
    else if (difference > DX_PI_F)
    {
        difference -= DX_TWO_PI_F;
    }
    //-DX_PI_F>difference>DX_PI_F

    // 角度の差が０に近づける
    if (difference > 0.0f)
    {
        // 差がプラスの場合は引く
        difference -= AngleSpeed;
        if (difference < 0.0f)
        {
            difference = 0.0f;
        }
    }
    else
    {
        // 差がマイナスの場合は足す
        difference += AngleSpeed;
        if (difference > 0.0f)
        {
            difference = 0.0f;
        }
    }


    // モデルの角度を更新
    nowAngle = targetAngle - difference;
    angle = nowAngle;
    MV1SetRotationXYZ(modelHandle, VGet(0.0f, nowAngle, 0.0f));
}

/// <summary>
/// 球と球の当たり判定
/// </summary>
/// <param name="position_1"></param>
/// <param name="position_2"></param>
/// <param name="radius_1"></param>
/// <param name="radius_2"></param>
/// <returns></returns>
bool Calculation::HitConfirmation(VECTOR position_1, VECTOR position_2,const float radius_1,const float radius_2)
{

    VECTOR positionSub = VSub(position_1, position_2);
    
    //球と球の中心点との距離
    float positionRange = VSize(positionSub);

    //半径の合計
    float radiusAdd = radius_1 + radius_2;

    // 1と2の半径よりも球と球の中心点との距離が近ければ当たっている
    if (radiusAdd > positionRange)
    {
        return true;
    }
    return false;
}

/// <summary>
/// カプセルから最も近い球を計算
/// </summary>
/// <param name="capsulePosition_1"></param>
/// <param name="capsulePosition_2"></param>
/// <param name="position"></param>
/// <param name="radius_1"></param>
/// <param name="radius_2"></param>
/// <returns></returns>
VECTOR Calculation::CapsuleHitConfirmation(VECTOR capsulePosition_1, VECTOR capsulePosition_2, VECTOR position, const float radius_1, const float radius_2)
{
    VECTOR AB = VSub(capsulePosition_2, capsulePosition_1); 
    VECTOR AP = VSub(position, capsulePosition_1);

    //ベクトルの長さ
    float vectorLength = pow((AB.x * AB.x) + (AB.y * AB.y) + (AB.z * AB.z), 0.5f);
    
    //単位ベクトル
    VECTOR unitVector = VGet(0, 0, 0);
    unitVector.x = AB.x / vectorLength;
    unitVector.y = AB.y / vectorLength;
    unitVector.z = AB.z / vectorLength;
    float productionVector = (unitVector.x * AP.x) + (unitVector.y * AP.y) + (unitVector.z * AP.z);
    
    VECTOR AX;
    AX.x = capsulePosition_1.x + (unitVector.x * productionVector);
    AX.y = capsulePosition_1.y + (unitVector.y * productionVector);
    AX.z = capsulePosition_1.z + (unitVector.z * productionVector);
    
    if (AX.y <= capsulePosition_2.y)
    {
        AX.y = capsulePosition_2.y;
    }
    if (AX.y >= capsulePosition_1.y)
    {
        AX.y = capsulePosition_1.y;
    }
   
    return AX;

}

