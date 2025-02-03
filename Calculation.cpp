#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include <vector>
#include <math.h>    
#include "Calculation.h"

void Calculation::UpdateAngle(const VECTOR& direction, float& angle, int& modelHandle)
{
    // �v���C���[�̈ړ������Ƀ��f���̕������߂Â���
    float targetAngle;			// �ڕW�p�x
    float difference;			// �ڕW�p�x�ƌ��݂̊p�x�Ƃ̍�
    float nowAngle = angle;

    // �ڕW�̕����x�N�g������p�x�l���Z�o����
    if (VSize(direction) != 0)
    {
        targetAngle = atan2f(-direction.x, -direction.z);
    }

    // �ڕW�̊p�x�ƌ��݂̊p�x�Ƃ̍�������o��
    // �ŏ��͒P���Ɉ����Z
    difference = targetAngle - nowAngle;


    // ����������炠������̍����P�W�O�x�ȏ�ɂȂ邱�Ƃ͖����̂�
    // ���̒l���P�W�O�x�ȏ�ɂȂ��Ă�����C������
    if (difference < -DX_PI_F)
    {
        difference += DX_TWO_PI_F;
    }
    else if (difference > DX_PI_F)
    {
        difference -= DX_TWO_PI_F;
    }
    //-DX_PI_F>difference>DX_PI_F

    // �p�x�̍����O�ɋ߂Â���
    if (difference > 0.0f)
    {
        // �����v���X�̏ꍇ�͈���
        difference -= AngleSpeed;
        if (difference < 0.0f)
        {
            difference = 0.0f;
        }
    }
    else
    {
        // �����}�C�i�X�̏ꍇ�͑���
        difference += AngleSpeed;
        if (difference > 0.0f)
        {
            difference = 0.0f;
        }
    }


    // ���f���̊p�x���X�V
    nowAngle = targetAngle - difference;
    angle = nowAngle;
    MV1SetRotationXYZ(modelHandle, VGet(0.0f, nowAngle, 0.0f));
}

/// <summary>
/// ���Ƌ��̓����蔻��
/// </summary>
/// <param name="position_1"></param>
/// <param name="position_2"></param>
/// <param name="radius_1"></param>
/// <param name="radius_2"></param>
/// <returns></returns>
bool Calculation::HitConfirmation(VECTOR position_1, VECTOR position_2,const float radius_1,const float radius_2)
{

    VECTOR positionSub = VSub(position_1, position_2);
    
    //���Ƌ��̒��S�_�Ƃ̋���
    float positionRange = VSize(positionSub);

    //���a�̍��v
    float radiusAdd = radius_1 + radius_2;

    // 1��2�̔��a�������Ƌ��̒��S�_�Ƃ̋������߂���Γ������Ă���
    if (radiusAdd > positionRange)
    {
        return true;
    }
    return false;
}

/// <summary>
/// �J�v�Z������ł��߂������v�Z
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

    //�x�N�g���̒���
    float vectorLength = pow((AB.x * AB.x) + (AB.y * AB.y) + (AB.z * AB.z), 0.5f);
    
    //�P�ʃx�N�g��
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

