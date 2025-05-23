#pragma once

class Calculation
{
private:
    static constexpr float	AngleSpeed = 0.05f;	    // 角度変化速度

public:
    bool HitConfirmation(VECTOR position_1, VECTOR position_2, const float radius_1, const float radius_2);     //当たり判定
    VECTOR CapsuleHitConfirmation(VECTOR capsulePosition_1, VECTOR capsulePosition_2, VECTOR position, const float radius_1, const float radius_2);
    void UpdateAngle(const VECTOR& targetMoveDirection, float& angle, int& modelHandle);
  
};

