#include "EnemyManager.h"

/// <summary>
/// プレイヤーの座標を保存
/// </summary>
/// <param name="player"></param>
/// <param name="enemy"></param>
void EnemyManager::GetPlayerPos(Player& player, Enemy& enemy)
{
    VECTOR pos = VGet(0, 0, 0);
    player.GetPosition(pos);
    enemy.bullet->SetPlayerPosition(pos);
}



/// <summary>
/// 更新
/// </summary>
/// <param name="player"></param>
/// <param name="enemy"></param>
void EnemyManager::Update(Player& player, Enemy& enemy)
{
    GetPlayerPos(player, enemy);
    enemy.SetPosition(player.GetPosition());
}



/// <summary>
/// 円周上の点計算
/// </summary>
/// <param name="x"></param>
/// <param name="z"></param>
void EnemyManager::CircumferenceCalculation(float& x, float& z, const float& stack, const float& speed)
{
    float circleRadio = 3.14f;
    float cosΘ = (2 * circleRadio) * stack / 360;
    float sinΘ = (2 * circleRadio) * stack / 360;
    x = x + 1 * cos(cosΘ);
    z = z + 1 * sin(sinΘ);

    x *= speed;
    z *= speed;

}