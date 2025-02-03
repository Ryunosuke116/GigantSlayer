#pragma once

class Calculation
{
private:
    static constexpr float	AngleSpeed = 0.05f;	    // �p�x�ω����x

public:
    bool HitConfirmation(VECTOR position_1, VECTOR position_2, const float radius_1, const float radius_2);     //�����蔻��
    VECTOR CapsuleHitConfirmation(VECTOR capsulePosition_1, VECTOR capsulePosition_2, VECTOR position, const float radius_1, const float radius_2);
    void UpdateAngle(const VECTOR& targetMoveDirection, float& angle, int& modelHandle);
  
};

