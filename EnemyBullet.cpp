#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include <vector>
#include <cmath>
#include "Enemy.h"
#include "EnemyCircleAttack.h"
#include "EnemyBullet.h"

/// <summary>
/// �C���X�^���X��
/// </summary>
EnemyBullet::EnemyBullet()
{
    bulletSpeed = VGet(0, 0, 0);
    position = VGet(0, 0, 0);
    playerPos = VGet(0, 0, 0);
    futurePosition = VGet(0, 0, 0);
    effectPosition = VGet(0, 0, 0);
    fellPosition = VGet(0, 0, 0);
    positionStack = 0;
    playerMoveSpeed = 0;
    scale = 0;
    bulletSpeed_Y = 2.5f;
    isAttack = false;
    isPlayerMove = false;
    isEffect = false;
    isEmerge = false;
    isCircleBullet = false;
    isSetUpMotion = false;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyBullet::~EnemyBullet()
{

}

/// <summary>
/// ������
/// </summary>
void EnemyBullet::Initialize(const VECTOR EnemyPosition)
{
    //�|�W�V����������
    position = VGet(EnemyPosition.x, EnemyPosition.y + 35, EnemyPosition.z);
    //�C���X�^���X��
    effect = new Effect;
    bulletColor = new Effect;
    //������
    effect->Initialize("material/TouhouStrategy/patch_stElmo_area.efkefc", 1.2f,position);
    bulletColor->Initialize("material/TouhouStrategy/enemyBullet.efkefc", 1.6f, position);
}

/// <summary>
/// �X�V
/// </summary>
void EnemyBullet::Update(const VECTOR EnemyPosition, 
    EnemyCircleAttack& circleAttack)
{

    AttackDesignation(EnemyPosition);
  
    //�e�̗���
    Move(EnemyPosition, circleAttack);

    //�G�t�F�N�g���Đ�
    if (isEffect)
    {
        //�������Ă���60f�̊ԍĐ�
        if (effectPlayStack <= 120)
        {
            effectPlayStack++;
            //�G�t�F�N�g���Đ�
            effect->PositionUpdate(effectPosition);
        }
        else
        {
            //�G�t�F�N�g���~
            effect->StopEffect();
            effectPosition = VGet(EnemyPosition.x, EnemyPosition.y + 15, EnemyPosition.z);
            effectPlayStack = 0;
            isEffect = false;
        }
    }
    if (circleAttack.Count >= 50)
    {
        circleAttack.SetPosition(position);
       // breath.SetPosition(position);
    }
    
}

void EnemyBullet::Draw()
{
   // DrawSphere3D(position, radius, 16, GetColor(0, 0, 0), GetColor(255, 0, 255), false);
    printfDx("bulletSpeed.x %f\n", bulletSpeed.x);
    printfDx("bulletSpeed.y %f\n", bulletSpeed.y);
    printfDx("bulletSpeed.z %f\n", bulletSpeed.z);
    printfDx("fellPosition.x %f\n", fellPosition.x);
    printfDx("fellPosition.y %f\n", fellPosition.y);
    printfDx("fellPosition.z %f\n", fellPosition.z);

}

/// <summary>
/// ����
/// </summary>
void EnemyBullet::Move(const VECTOR enemyPosition,EnemyCircleAttack& circleAttack)
{
    if (CheckHitKey(KEY_INPUT_9))
    {
        isCircleBullet = true;
    }
    if (CheckHitKey(KEY_INPUT_8))
    {
        isCircleBullet = false;
    }

    if (isSetUpMotion)
    {
        bulletColor->StopEffect();
        bulletColor->PlayEffect();
        bulletColor->PositionUpdate(position);
        if (!isAttack)
        {
            scale += 0.02f;
        }
        bulletColor->SetScale(VGet(scale, scale, scale));
    }



    if (isAttack)
    {
        BulletMove();

        bulletSpeed_Y -= 0.08f;
        //�@0�ɂȂ�܂ŗ���������@
        if (position.y > 0.0f)
        {
            position.y += bulletSpeed_Y;
        }
        //�@ 0�܂ŗ��������Ƃ�
        else
        {
            //�T�[�N���U���̏ꍇ�A�I�u�W�F�N�g�͔������Ȃ�
            if (isCircleBullet)
            {
                circleAttack.isAttack = true;
            }
            else
            {
                isEmerge = true;
            }

            //�e�����Z�b�g
            ResetAttack(enemyPosition);

            
            //bullet�����������W��circleAttack�ɓn��
            if (circleAttack.isAttack)
            {
                circleAttack.SetPosition(fellPosition);
            }

            //�T�[�N���U�������Ȃ���΍Đ�
            if (!isCircleBullet)
            {
                //�G�t�F�N�g�Đ��J�n
                effect->PlayEffect();
                effect->SetSpeed(2.0f);
            }
        }

    }
}

void EnemyBullet::ResetAttack(const VECTOR& enemyPosition)
{
    isAttack = false;
    isEffect = true;
    isSetUpMotion = false;

    //�����n�_��ۑ�
    fellPosition = GetPosition();
    effectPosition = VGet(fellPosition.x, fellPosition.y, fellPosition.z);

    //bullet�̍��W�����Z�b�g����
    position = VGet(enemyPosition.x, enemyPosition.y + 35, enemyPosition.z);
    bulletColor->PositionUpdate(position);
    bulletColor->StopEffect();
    positionStack = 0;
    scale = 0;
    bulletSpeed_Y = 2.5f;
}

/// <summary>
/// �e�𗎂Ƃ����W�����߂�
/// </summary>
void EnemyBullet::AttackDesignation(const VECTOR EnemyPosition)
{

    //�e�𗎂Ƃ��ʒu�����߂�
    bulletSpeed = VSub(playerPos, position);
    bulletSpeed.y = 0;
    //�e�̒e���̐��K��
    bulletSpeed = VNorm(bulletSpeed);
    //�X�s�[�h�𒲐�
    bulletSpeed = VScale(bulletSpeed, speed);


}

void EnemyBullet::BulletMove()
{  
    //�T�[�N���U���̏ꍇ
    if (isCircleBullet)
    {
        position.z -= circleAttackBulletSpeed;

    }
    //�T�[�N���U������Ȃ��ꍇ
    else
    {
        //25f�܂Ńv���C���[��Ǐ]����
        if (positionStack < maxPositionStack)
        {
            position.z += bulletSpeed.z;
            position.x += bulletSpeed.x;

            positionStack++;
        }
    }
  
}


/// <summary>
/// �v���C���[���W���X�V
/// </summary>
/// <param name="getPosition"></param>
void EnemyBullet::SetPlayerPosition(VECTOR& getPosition)
{
    playerPos = VGet(getPosition.x, getPosition.y, getPosition.z);
}

/// <summary>
/// ���W���X�V
/// </summary>
/// <param name="getPosition"></param>
void EnemyBullet::SetPosition(VECTOR& getPosition)
{
    position = VGet(getPosition.x, getPosition.y + 15.0f, getPosition.z);
}

/// <summary>
/// �t���O�؂�ւ�
/// </summary>
void EnemyBullet::SwitchingIsCircleBullet()
{
    if (isCircleBullet)
    {
        isCircleBullet = false;
    }
    else
    {
        isCircleBullet = true;
    }
}