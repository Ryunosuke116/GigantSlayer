#include <vector>
#include <time.h>
#include "DxLib.h"
#include "EnemyBullet.h"
#include "EnemyCircleAttack.h"
#include "EnemyBreath.h"
#include "Calculation.h"
#include "Enemy.h"

/// <summary>
/// �C���X�^���X��
/// </summary>
Enemy::Enemy()
{
    if (breath == NULL)
    {
        for (auto& bullets : bullet)
        {
            bullets = new EnemyBullet();
        }
        circleAttack = new EnemyCircleAttack();
        breath = new EnemyBreath();
        bottomPosition = VGet(0, -15, 20);
        topPosition = VGet(0, 0, 0);
        AttackSpherePosition = VGet(0, 0, 0);
        bulletSpeed = VGet(0, 0, 0);
        bulletPosition = VGet(0, 0, 0);
        playerPos = VGet(0, 0, 0);
        bulletMotionPosition = VGet(0, 0, 0);
        direction = VGet(0, 0, 0);
        modelHandle = -1;
        addPlayTime = 0;
        standTime_now = 0;
        HP = 0;
        motionNum = 0;
        angle = 0;
        totalTime = 0;
        playTime = 0;
        maxBulletNumber = 0;
        isPlayerAttackHit = 0;
        isBulletNumber = 0;
        bulletNumber = 0;
        attachIndex = 0;

        orderNumber = 0;
        isAttack = false;
        isKnockback = false;
        isAnger = false;
        isBootBullet = false;
    }

}

Enemy::~Enemy()
{
    MV1DeleteModel(modelHandle);
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
    standTime_now = 0;
    orderNumber = 0;
    angle = 0;
    isAttack = false;
    isKnockback = false;
    isAnger = false;
    isBootBullet = false;
    

    if (modelHandle == -1)
    {
        voiceHandle = LoadSoundMem("material/SE/monster-roar-6985.mp3");
        //���f���ǂݍ���
        modelHandle = MV1LoadModel("material/mv1/mutant_1031.mv1");
        //���f���̑傫������
        MV1SetScale(modelHandle, VGet(0.4f, 0.4f, 0.4f));
    }

    // �v���C���[�̃��f���̍��W���X�V����
    MV1SetPosition(modelHandle, bottomPosition);
    for (auto& bullets : bullet)
    {
        bullets->Initialize(bottomPosition);
    }
    circleAttack->SetPosition(bottomPosition);
    breath->SetPosition(bullet[0]->GetPosition());
    circleAttack->Initialize();
    breath->Initialize();

    MV1SetRotationXYZ(modelHandle, VGet(0, 0, 0));

    //�ҋ@���[�V�����ǂݍ���
    ChangeMotion(stand);
    
}

/// <summary>
/// �X�V
/// </summary>
void Enemy::Update(Calculation& calculation)
{
    //��������
    UpdateDirection();

    //�ʏ펞�͐��ʂ�����
    if (motionNum != breathAttack)
    {
        calculation.UpdateAngle(direction, angle, modelHandle);
    }
   
    if (CheckHitKey(KEY_INPUT_1))
    {
        ChangeMotion(breathAttack);
    }
    if (CheckHitKey(KEY_INPUT_2))
    {
        HP = 0;
        ChangeMotion(knockback);
    }

    if (CheckHitKey(KEY_INPUT_3) && (motionNum != bulletAttack))
    {
        ChangeMotion(bulletAttack);
    }
    if (CheckHitKey(KEY_INPUT_4))
    {
        breath->Rotation(playerPos, bottomPosition);
        ChangeMotion(breathAttack);
    }

    //�U���̍X�V
    for (auto& bullets : bullet)
    {
        bullets->Update(bottomPosition, *circleAttack);
    }
    circleAttack->Update();
    breath->Update();

    //�s���̗���𐧌�
    ActionFlow(*bullet, *circleAttack, *breath, calculation);

    if (bullet[0]->GetIsAttack())
    {
        isBootBullet = true;
    }
    else
    {
        isBootBullet = false;
    }

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

    //HP�����ȉ��ɂȂ�ƍs���ω�
    if (HP < 50)
    {
        isAnger = true;
    }
}

/// <summary>
/// �`��
/// </summary>
void Enemy::Draw()
{
    MV1DrawModel(modelHandle);

    for (auto& bullets : bullet)
    {
        bullets->Draw();
    }
    circleAttack->Draw();
    breath->Draw();

    printfDx("enemy.HP %d\n", HP);
    VECTOR a = MV1GetRotationXYZ(modelHandle);
    printfDx("enemy.angle.x %f\n", a.x);
    printfDx("enemy.angle.y %f\n", a.y);
    printfDx("enemy.angle.z %f\n", a.z);
}

/// <summary>
/// �����v�Z
/// </summary>
void Enemy::UpdateDirection()
{
    //�u���X�U���ł͂Ȃ��Ƃ��͐��ʂ�����
    if (motionNum != breathAttack)
    {
        direction = VSub(VGet(0, 0, 0), bottomPosition);
    }
    //�u���X�U�����A�v���C���[�̕���������
    else
    {
        direction = VSub(playerPos, bottomPosition);
    }
    direction.y = 0;

    //���K��
    if (VSize(direction) != 0)
    {
        direction = VNorm(direction);
    }
    
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
            playTime += 0.02f;
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
void Enemy::ActionFlow(EnemyBullet bullet[], EnemyCircleAttack& circleAttack,
                       EnemyBreath& breath, Calculation& calculation)
{   
    //�ҋ@��50f���Ƃɍs������
    // if (motionNum == stand)
    {
        standTime_now++;
        if (standTime_now >= standTime)
        {
            if (playTime == 0)
            {
                standTime_now = 0;
                Order(bullet[0], breath);

                if (isBulletNumber)
                {
                    standTime_now = standTime;
                }
            }
        }
    }
    //if (!isAnger)
    //{
    //    
    //}
    //else if (isAnger)
    //{
    //    if (motionNum == stand)
    //    {
    //        standTime_now++;
    //        if (standTime_now >= standTime_anger)
    //        {
    //            if (playTime == 0)
    //            {
    //                standTime_now = 0;
    //                Order(bullet[0], breath);

    //                if (isBulletNumber)
    //                {
    //                    standTime_now = standTime_anger;
    //                }
    //            }
    //        }
    //    }
    //}

    //�e�U��
    if (motionNum == bulletAttack)
    {
        //�U��������[�V�����ɓ��������U������
        if (playTime >= 45.0f && !isAttack)
        {
            if (!isBootBullet)
            {
                bullet[0].SetIsAttack(true);
            }
            else
            {
                bullet[1].SetIsAttack(true);
            }
            isAttack = true;
           
        }
        else if(!isAttack)
        {
            if (!isBootBullet)
            {
                bullet[0].SetPosition(topPosition);
                bullet[0].SetIsSetUpMotion(true);
            }
            else
            {
                bullet[1].SetPosition(topPosition);
                bullet[1].SetIsSetUpMotion(true);
            }
        }
    }
    //�̂�����
    if (isPlayerAttackHit)
    {
        HP -= 20;
        if (!bullet[0].GetIsAttack() && bullet[0].GetIsSetUpMotion())
        {
            bullet[0].ResetAttack(bottomPosition);
        }
        if (!bullet[1].GetIsAttack() && bullet[1].GetIsSetUpMotion())
        {
            bullet[1].ResetAttack(bottomPosition);
        }
        if (breath.GetIsAttack())
        {
            breath.EndBreath();
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
        else if(!isAttack)
        {
            calculation.UpdateAngle(direction, angle, modelHandle);
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

/// <summary>
/// �J�n��
/// </summary>
void Enemy::StartUpdate()
{
    MotionUpdate();

    standTime_now++;
    if (standTime_now == 190)
    {
        ChangeMotion(breathAttack);
    }
    if (standTime_now == 210)
    {
        PlaySoundMem(voiceHandle, DX_PLAYTYPE_BACK);
    }
 
}