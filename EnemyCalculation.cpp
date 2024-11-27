#include "DxLib.h"
#include <vector>
#include <cmath>
#include "EnemyCalculation.h"

/// <summary>
/// â~é¸è„ÇÃì_åvéZ
/// </summary>
/// <param name="x"></param>
/// <param name="z"></param>
void EnemyCalculation::CircumferenceCalculation(VECTOR& position, const float& x, const float& z, const int& angle, const float& speed)
{
    float cosÉ¶ = (2 * DX_PI_F) * angle / 360;
    float sinÉ¶ = (2 * DX_PI_F) * angle / 360;
    position.x = x + 1 * cos(cosÉ¶);
    position.z = z + 1 * sin(sinÉ¶);

    position.x *= speed;
    position.z *= speed;

}