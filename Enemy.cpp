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
    futurePosition = VGet(0, 0, 0);
    bulletMotionPosition = VGet(0, 0, 0);
    modelHandle = -1;
    bulletPositionStack = 0;
    addPlayTime = 0;
    standTime = 0;
    playerMoveSpeed = 0;
    bulletSpeed_Y = 0.95;
    motionNum = 0;
    isAttack = false;
    isPlayerMove = false;
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

    bottomPosition = VGet(0, -30, 60);
    bulletPosition = VGet(bottomPosition.x, bottomPosition.y + 20, bottomPosition.z);
    radius = 18;
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

    bullet->Update(bottomPosition, *circleAttack);
    bullet[1].Update(bottomPosition, *circleAttack);
   
    if (CheckHitKey(KEY_INPUT_1))
    {
        breath->isAttack = true;
    }

    circleAttack->Update();
    breath->Update();

    if (CheckHitKey(KEY_INPUT_3) && motionNum != bulletAttack)
    {
        ChangeMotion(bulletAttack);
    }
    if (CheckHitKey(KEY_INPUT_4))
    {
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

    printfDx("x.%f\n", bulletPosition.x);
    printfDx("y.%f\n", bulletPosition.y);
    printfDx("z.%f\n", bulletPosition.z);
    if (isPlayerMove)
    {
        printfDx("�ړ���\n", isPlayerMove);
    }
}

/// <summary>
/// ���W�̎擾
/// </summary>
/// <param name="setPosition"></param>
void Enemy::GetPosition(VECTOR& setPosition)
{
    setPosition = VGet(bottomPosition.x, bottomPosition.y, bottomPosition.z);
}

/// <summary>
/// ���W��ύX
/// </summary>
/// <param name="getPosition"></param>
void Enemy::SetPosition(VECTOR& getPosition)
{
    playerPos = VGet(getPosition.x, getPosition.y, getPosition.z);
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
    if (isPlayerMove)
    {
        PlayerMovementPrediction();
    }
    bulletSpeed = VScale(bulletSpeed, 0.025);

}

/// <summary>
/// �v���C���[�̈ړ����x��ۑ�����
/// </summary>
/// <param name="moveSpeed"></param>
void Enemy::SetPlayerMoveSpeed(float moveSpeed)
{
    playerMoveSpeed = moveSpeed;
}

/// <summary>
/// �v���C���[���ړ����ɖ����̍��W���v�Z
/// </summary>
void Enemy::PlayerMovementPrediction()
{
    //40�t���[����̃v���C���[�̃|�W�V������T��
    playerMoveSpeed *= 40;

    futurePosition = VGet(0, 0, 0);
    
    if (isTopMove)
    {
        futurePosition = VAdd(futurePosition, VGet(0, 0, 1));
    }
    if (isBottomMove)
    {
        futurePosition = VAdd(futurePosition, VGet(0, 0, -1));
    }
    if (isRightMove)
    {
        futurePosition = VAdd(futurePosition, VGet(1, 0, 0));
    }
    if (isLeftMove)
    {
        futurePosition = VAdd(futurePosition, VGet(-1, 0, 0));
    }

    if (isPlayerMove)
    {
        futurePosition = VNorm(futurePosition);
        futurePosition = VScale(futurePosition, playerMoveSpeed);
    }

    bulletSpeed = VAdd(bulletSpeed, futurePosition);
  
  
}

/// <summary>
/// �v���C���[�������Ă��邩�ǂ���
/// </summary>
/// <param name="isMove"></param>
void Enemy::SetIsPlayerMove(bool isMove)
{
    isPlayerMove = isMove;
}

/// <summary>
/// �v���C���[���ǂ̕����ɓ����Ă��邩
/// </summary>
/// <param name="isTopMove"></param>
/// <param name="isBottomMove"></param>
/// <param name="isRightMove"></param>
/// <param name="isLeftMove"></param>
void Enemy::SetIsPlayerMoveDirection(bool isTopMove, bool isBottomMove, bool isRightMove, bool isLeftMove)
{
    this->isTopMove = isTopMove;
    this->isBottomMove = isBottomMove;
    this->isRightMove = isRightMove;
    this->isLeftMove = isLeftMove;
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

    //�~�܂郂�[�V�����̎����[�V�����I�������ꍇ�ҋ@���[�V�����ɕύX
    if (motionNum != stand)
    {
        //�e���o���Ƃ��̃��[�V����
        if (motionNum == bulletAttack)
        {
            if (playTime >= totalTime)
            {
                ChangeMotion(stand);
                //bottomPosition.x -= 8.5f;
               // bottomPosition.y -= 3.5f;
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
                Order();
            }
        }
    }


    //�e�U��
    if (motionNum == bulletAttack)
    {
        
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
void Enemy::Order()
{
    //�e�U��
    if (orderNumber == 0)
    {
        orderNumber++;
        ChangeMotion(bulletAttack);

    }
    //�u���X�U��
    else if (orderNumber == 1)
    {
        orderNumber++;
        ChangeMotion(breathAttack);
    }
    //�T�[�N���U��
    else if (orderNumber == 2)
    {
        orderNumber = 0;
        ChangeMotion(bulletAttack);
    }
}