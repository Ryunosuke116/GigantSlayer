#include "BulletCalculation.h"

/// <summary>
/// プレイヤーの座標を保存
/// </summary>
/// <param name="player"></param>
/// <param name="enemy"></param>
void BulletCalculation::GetPlayerPos(Player& player, Enemy& enemy)
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
void BulletCalculation::GetPlayerMoveSpeed(Player& player,Enemy& enemy)
{
    enemy.bullet->SetPlayerMoveSpeed(player.GetMoveSpeed());
}

/// <summary>
/// プレイヤーが移動しているかどうか
/// </summary>
/// <param name="player"></param>
/// <param name="enemy"></param>
void BulletCalculation::GetIsMove(Player& player, Enemy& enemy)
{
    enemy.bullet->SetIsPlayerMove(player.GetIsMove());
    enemy.bullet->SetIsPlayerMoveDirection(player.isTopMove, player.isBottomMove, player.isRightMove, player.isLeftMove);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="player"></param>
/// <param name="enemy"></param>
void BulletCalculation::Update(Player& player, Enemy& enemy)
{
    GetPlayerMoveSpeed(player, enemy);
    GetPlayerPos(player, enemy);
    GetIsMove(player,enemy);
}



