#include "BulletCalculation.h"

/// <summary>
/// �v���C���[�̍��W��ۑ�
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
/// �v���C���[�̈ړ����x��ۑ�
/// </summary>
/// <param name="player"></param>
/// <param name="enemy"></param>
void BulletCalculation::GetPlayerMoveSpeed(Player& player,Enemy& enemy)
{
    enemy.bullet->SetPlayerMoveSpeed(player.GetMoveSpeed());
}

/// <summary>
/// �v���C���[���ړ����Ă��邩�ǂ���
/// </summary>
/// <param name="player"></param>
/// <param name="enemy"></param>
void BulletCalculation::GetIsMove(Player& player, Enemy& enemy)
{
    enemy.bullet->SetIsPlayerMove(player.GetIsMove());
    enemy.bullet->SetIsPlayerMoveDirection(player.isTopMove, player.isBottomMove, player.isRightMove, player.isLeftMove);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="player"></param>
/// <param name="enemy"></param>
void BulletCalculation::Update(Player& player, Enemy& enemy)
{
    GetPlayerMoveSpeed(player, enemy);
    GetPlayerPos(player, enemy);
    GetIsMove(player,enemy);
}



