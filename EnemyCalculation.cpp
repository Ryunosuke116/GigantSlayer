#include "DxLib.h"
#include <vector>
#include <cmath>
#include "EnemyCalculation.h"

/// <summary>
/// �~����̓_�v�Z
/// </summary>
/// <param name="x"></param>
/// <param name="z"></param>
void EnemyCalculation::CircumferenceCalculation(VECTOR& position, const float& x, const float& z, const int& angle, const float& speed)
{
    float cos�� = (2 * DX_PI_F) * angle / 360;
    float sin�� = (2 * DX_PI_F) * angle / 360;
    position.x = x + 1 * cos(cos��);
    position.z = z + 1 * sin(sin��);

    position.x *= speed;
    position.z *= speed;

}