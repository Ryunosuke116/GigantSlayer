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
/// プレイヤーの移動速度を保存
/// </summary>
/// <param name="player"></param>
/// <param name="enemy"></param>
void EnemyManager::GetPlayerMoveSpeed(Player& player,Enemy& enemy)
{
    enemy.bullet->SetPlayerMoveSpeed(player.GetMoveSpeed());
}

/// <summary>
/// プレイヤーが移動しているかどうか
/// </summary>
/// <param name="player"></param>
/// <param name="enemy"></param>
void EnemyManager::GetIsMove(Player& player, Enemy& enemy)
{
    enemy.bullet->SetIsPlayerMove(player.GetIsMove());
    enemy.bullet->SetIsPlayerMoveDirection(player.isTopMove, player.isBottomMove, player.isRightMove, player.isLeftMove);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="player"></param>
/// <param name="enemy"></param>
void EnemyManager::Update(Player& player, Enemy& enemy)
{
    GetPlayerMoveSpeed(player, enemy);
    GetPlayerPos(player, enemy);
    GetIsMove(player,enemy);
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