#include "EnemyManager.h"

/// <summary>
/// �v���C���[�̍��W��ۑ�
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
/// �v���C���[�̈ړ����x��ۑ�
/// </summary>
/// <param name="player"></param>
/// <param name="enemy"></param>
void EnemyManager::GetPlayerMoveSpeed(Player& player,Enemy& enemy)
{
    enemy.bullet->SetPlayerMoveSpeed(player.GetMoveSpeed());
}

/// <summary>
/// �v���C���[���ړ����Ă��邩�ǂ���
/// </summary>
/// <param name="player"></param>
/// <param name="enemy"></param>
void EnemyManager::GetIsMove(Player& player, Enemy& enemy)
{
    enemy.bullet->SetIsPlayerMove(player.GetIsMove());
    enemy.bullet->SetIsPlayerMoveDirection(player.isTopMove, player.isBottomMove, player.isRightMove, player.isLeftMove);
}

/// <summary>
/// �X�V
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
/// �~����̓_�v�Z
/// </summary>
/// <param name="x"></param>
/// <param name="z"></param>
void EnemyManager::CircumferenceCalculation(float& x, float& z, const float& stack, const float& speed)
{
    float circleRadio = 3.14f;
    float cos�� = (2 * circleRadio) * stack / 360;
    float sin�� = (2 * circleRadio) * stack / 360;
    x = x + 1 * cos(cos��);
    z = z + 1 * sin(sin��);

    x *= speed;
    z *= speed;

}