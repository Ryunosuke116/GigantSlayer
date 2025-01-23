#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include <vector>
#include "EnemyBullet.h"
#include "EnemyCircleAttack.h"
#include "EnemyBreath.h"
#include "Enemy.h"

/// <summary>
/// �C���X�^���X��
/// </summary>
Enemy::Enemy()
{
    bottomPosition = VGet(0, -15, 20);
    topPosition = VGet(0, 0, 0);
    AttackSpherePosition = VGet(0, 0, 0);
    bulletSpeed = VGet(0, 0, 0);
    bulletPosition = VGet(0, 0, 0);
    playerPos = VGet(0, 0, 0);
    bulletMotionPosition = VGet(0, 0, 0);
    modelHandle = -1;
    bulletPositionStack = 0;
    addPlayTime = 0;
    standTime = 0;
    playerMoveSpeed = 0;
    HP = 0;
    bulletSpeed_Y = 0.95;
    motionNum = 0;
    isAttack = false;
    isKnockback = false;
}

Enemy::~Enemy()
{

}

/// <summary>
/// ������
/// </summary>
void Enemy::Initialize()
{
    HP = 100;
    bottomPosition = VGet(0, -30, 60);
    topPosition = VGet(bottomPosition.x, bottomPosition.y + 50.0f, bottomPosition.z);
    bulletPosition = VGet(bottomPosition.x, bottomPosition.y + 20, bottomPosition.z);
    addPlayTime = 0.4f;
    //���f���ǂݍ���
    modelHandle = MV1LoadModel("material/mv1/mutant_1031.mv1");

    //���f���̑傫������
    MV1SetScale(modelHandle, VGet(0.4f, 0.4f, 0.4f));

    // �v���C���[�̃��f���̍��W���X�V����
    MV1SetPosition(modelHandle, bottomPosition);
    bullet->Initialize(bottomPosition);
    circleAttack->SetPosition(bullet->GetPosition());
    breath->SetPosition(bullet->GetPosition());
    circleAttack->Initialize();
    breath->Initialize();

    //�ҋ@���[�V�����ǂݍ���
    ChangeMotion(stand);

}

/// <summary>
/// �X�V
/// </summary>
void Enemy::Update()
{
    topPosition = VGet(bottomPosition.x, bottomPosition.y + 50.0f, bottomPosition.z);

   
    if (CheckHitKey(KEY_INPUT_1))
    {
        breath->isAttack = true;
    }
    if (CheckHitKey(KEY_INPUT_2))
    {
        HP = 0;
        ChangeMotion(knockback);
    }

    //�U���̍X�V
    bullet->Update(bottomPosition, *circleAttack);
    circleAttack->Update();
    breath->Update();

    if (CheckHitKey(KEY_INPUT_3) && motionNum != bulletAttack)
    {
        ChangeMotion(bulletAttack);
    }
    if (CheckHitKey(KEY_INPUT_4))
    {
        breath->Rotation(playerPos, bottomPosition);
        ChangeMotion(breathAttack);
    }

    ActionFlow(*bullet, *circleAttack, *breath);
    //���[�V�����X�V
    MotionUpdate();

    //�e�U���̃��[�V�������͕ʂŃ|�W�V������p��
    if (motionNum != bulletAttack)
    {
        MV1SetPosition(modelHandle, bottomPosition);
    }
    else
    {
        bulletMotionPosition = VGet(bottomPosition.x + 8.5f,
            bottomPosition.y + 3.5f, bottomPosition.z);

        MV1SetPosition(modelHandle, bulletMotionPosition);
    }
}

/// <summary>
/// �`��
/// </summary>
void Enemy::Draw()
{
    MV1DrawModel(modelHandle);

    DrawCapsule3D(bottomPosition, topPosition, 15, 16, GetColor(0, 0, 0), GetColor(255, 255, 255), false);
    bullet->Draw();
    circleAttack->Draw();
    breath->Draw();

    printfDx("enemy.HP %d\n", HP);

}

/// <summary>
/// �e�𗎂Ƃ����W�����߂�
/// </summary>
void Enemy::AttackDesignation()
{
    bulletSpeed = VGet(0, 0, 0);

    //�e�̒e���̏�����
    bulletSpeed = VNorm(bulletSpeed);

    //�e�𗎂Ƃ��ʒu�����߂�
    bulletSpeed = VSub(playerPos, bulletPosition);
   
    bulletSpeed = VScale(bulletSpeed, 0.025);

}

/// <summary>
/// ���[�V�����؂�ւ�
/// </summary>
/// <param name="motionNum"></param>
void Enemy::ChangeMotion(int motionNum)
{
    MV1DetachAnim(modelHandle, attachIndex);
    // �Đ����Ԃ̏�����
    playTime = 0;
    // �Đ����Ԃ��Z�b�g����
    MV1SetAttachAnimTime(modelHandle, attachIndex, playTime);
    this->motionNum = motionNum;
    isAttack = false;

    // �R�c���f���̂O�Ԗڂ̃A�j���[�V�������A�^�b�`����
    attachIndex = MV1AttachAnim(modelHandle, motionNum, -1, FALSE);
    // �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
    totalTime = MV1GetAttachAnimTotalTime(modelHandle, attachIndex);
}

/// <summary>
/// ���[�V�����X�V
/// </summary>
void Enemy::MotionUpdate()
{
    //�ҋ@��
    if (motionNum == stand)
    {
      playTime += 0.8f;
    }
    //�e�U��
    else if(motionNum == bulletAttack)
    {
        playTime += 0.55f;
    }
    //�u���X�U��
    else if(motionNum == breathAttack)
    {
        playTime += 0.8f;
    }
    //�̂�����
    else if (motionNum == knockback)
    {
        if (HP > 0)
        {
            playTime += addPlayTime;

            //��萔�𒴂���Ƌt�Đ�
            if (playTime >= 20.0f)
            {
                addPlayTime *= -1.0f;
            }
            else if (playTime <= 0)
            {
                ChangeMotion(stand);
                addPlayTime *= -1.0f;
            }
        }
        else
        {
            playTime += 0.1f;
        }
    }

    //�~�܂郂�[�V�����̎����[�V�����I�������ꍇ�ҋ@���[�V�����ɕύX
    if (motionNum != stand)
    {
        //�e���o���Ƃ��̃��[�V����
        if (motionNum == bulletAttack)
        {
            if (playTime >= totalTime)
            {
                ChangeMotion(stand);
            }
          
        }
        else
        {
            if (playTime >= totalTime)
            {
                ChangeMotion(stand);
            }
        }
    }

    

    //playTime��totalTime�𒴂����烊�Z�b�g����
    if (playTime >= totalTime)
    {
        playTime = 0;
    }

    // �Đ����Ԃ��Z�b�g����
    MV1SetAttachAnimTime(modelHandle, attachIndex, playTime);
}

/// <summary>
/// �s���̗���
/// </summary>
void Enemy::ActionFlow(EnemyBullet& bullet, EnemyCircleAttack& circleAttack,
                       EnemyBreath& breath)
{   
    //�ҋ@��50f���Ƃɍs������
    if (motionNum == stand)
    {
        standTime++;
        if (standTime >= 50.0f)
        {
            if (playTime == 0)
            {
                standTime = 0;
                Order(bullet,breath);

                if (isBulletNumber)
                {
                    standTime = 50.0f;
                }
            }
        }
    }


    //�e�U��
    if (motionNum == bulletAttack)
    {
        //�U��������[�V�����ɓ��������U������
        if (playTime >= 45.0f && !isAttack)
        {
            bullet.SetIsAttack(true);
            isAttack = true;
           
        }
        else if(!isAttack)
        {
            bullet.SetPosition(topPosition);
            bullet.SetIsSetUpMotion(true);
        }
    }
    //�̂�����
    if (isPlayerAttackHit)
    {
        HP -= 10;
        if (!bullet.GetIsAttack())
        {
            bullet.ResetAttack(bottomPosition);
        }
        ChangeMotion(knockback);
        playTime = 19.0f;
        isPlayerAttackHit = false;
    }
    //�u���X�U��
    if (motionNum == breathAttack)
    {
        if (playTime >= 52.0f && !isAttack)
        {
            breath.SetIsAttack(true);
            isAttack = true;
            
        }
    }
}

/// <summary>
/// �G�̍s����
/// </summary>
void Enemy::Order(EnemyBullet& bullet,EnemyBreath& breath)
{
    //�e�U��
    if (orderNumber == 0)
    {
        //����U�����邩
        if (!isBulletNumber)
        {
            //�e�̎�ސ؂�ւ�
            bullet.SetIsCircleBullet(false);
            srand((unsigned int)time(NULL));
            maxBulletNumber = rand() % 2 + 2;
            isBulletNumber = true;
        }
        //�ő�񐔕��U������
        if (maxBulletNumber > bulletNumber)
        {
            bulletNumber++;
            ChangeMotion(bulletAttack);
        }
        //�U�����I�����玟�̍U����
        else
        {
            orderNumber++;
            bulletNumber = 0;
            isBulletNumber = false;
        
        }
        
    }
    //�u���X�U��
    else if (orderNumber == 1)
    {
        orderNumber++;
        ChangeMotion(breathAttack);
        breath.Rotation(playerPos, bottomPosition);
    }
    //�T�[�N���U��
    else if (orderNumber == 2)
    {
        //�e�̎�ސ؂�ւ�
        bullet.SetIsCircleBullet(true);
        orderNumber = 0;
        ChangeMotion(bulletAttack);
    }
}

void Enemy::StartUpdate()
{
    MotionUpdate();

    standTime++;
    if (standTime == 190)
    {
        ChangeMotion(breathAttack);
    }
 
}