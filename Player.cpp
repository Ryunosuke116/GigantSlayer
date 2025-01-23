#include "Input.h"
#include "Player.h" 
#include"Map.h"
#include <iostream>
#include <array>

/// <summary>
/// �C���X�^���X��
/// </summary>
Player::Player()
{
    modelHandle = -1;
    effectResourceHandle = -1;
    position = VGet(0, 0, 0);
    targetMoveDirection = VGet(0, 0, 0);
    objectPosition = VGet(0, 5, 0);
    keepTargetMoveDirection = VGet(0, 0, 0);
    effectPosition = VGet(0, 0, 0);
    topSpherePosition = VGet(0, 0, 0);
    bottomSpherePosition = VGet(0, 0, 0);
    testPosition = VGet(0, 0, 0);
    
    angle = 0;
    stock = 0;
    HP = 0;
    invincibleTime = 0;

    attackEffectTime = 0;
    isHitEnemyAttack = false;
    isMove = false;
    isJump = false;
    isOnGround = false;
    isPushKey = false;
    isEffect = false;
    isChangeMotion = false;
    isPlayTime = false;
    isHitObject[4] = {false};
    isObjectHitEnemy = false;
    isAttackHold = false;
    isDisplay = false;
    currentJumpPower = 0;
    playingEffectHandle = -1;
    motionNumber = 0;

    //���f���̓ǂݍ���
    modelHandle = MV1LoadModel("material/mv1/maria_0123.mv1");
    shadowHandle = LoadGraph("material/Shadow.tga");

    MV1SetScale(modelHandle, VGet(0.04f, 0.04f, 0.04f));
    //�G�t�F�N�g�̃C���X�^���X���A������
    effect = new Effect();
    attackEffect = new Effect();
}

/// <summary>
/// 
/// </summary>
Player::~Player()
{

}

/// <summary>
/// ������
/// </summary>
void Player::Initialize()
{
    HP = 4;
    invincibleTime = 0;
    position = VGet(0, 0, -50);
    targetMoveDirection = VGet(0, 0, 0);
    objectPosition = VGet(0, 5, 0);
    keepTargetMoveDirection = VGet(0, 0, 0);
    effectPosition = VGet(0, 0, 0);
    topSpherePosition = VGet(0, 0, 0);
    bottomSpherePosition = VGet(0, 0, 0);
    testPosition = VGet(0, 0, 0);
    isAttackHold = false;
    isDisplay = true;

    //�ҋ@���[�V�����ǂݍ���
    ChangeMotion(stand);

    effectPosition = VGet(objectPosition.x, objectPosition.y, objectPosition.z);
    
    effect->Initialize("material/TouhouStrategy/miko_hihou_effect.efkefc",1.2f, effectPosition);
    attackEffect->Initialize("material/TouhouStrategy/explosion.efkefc", 0.5f, effectPosition);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="calculation"></param>
/// <param name="object"></param>
/// <param name="input"></param>
/// <param name="enemy"></param>
void Player::Update(Calculation& calculation,
    std::array<Object*, 4> object,
    const Input& input, Enemy& enemy)
{
    if (CheckHitKey(KEY_INPUT_8))
    {
        HP = 0;
    }
    VECTOR	moveVec = VGet(0, 0, 0);

    //player�̌�������
    UpdateAngle();

    //�U�������ꂽ�Ƃ��͓������Ȃ�
    if (!(motionNum == down || motionNum == standUp || motionNum == pickUp || motionNum == pickUp_Hold))
    {
        //�ړ�
        Move(input, moveVec);

        //�ړ��{�^���������ꂽ�Ƃ����K��
        if (isMove)
        {
            targetMoveDirection = VNorm(moveVec);

            moveVec = VScale(targetMoveDirection, MoveSpeed);
            if (stock)
            {
                moveVec = VScale(targetMoveDirection, slowMoveSpeed);
            }

            //�����Ă��ăW�����v���łȂ���΃��[�V�����؂�ւ�
            if (!isChangeMotion && !isJump)
            {
                //���郂�[�V�����ɕύX
                Motion_HoldorUnHold(run, run_Hold);
            }

        }
        //�ړ����Ă��Ȃ��Ƃ�
        else
        {
            if (isChangeMotion && !isJump)
            {
                //�ҋ@���[�V�����ɕύX
                Motion_HoldorUnHold(stop, stop_Hold);
            }
        }

        int number = 0;

        //�I�u�W�F�N�g�ƐڐG���Ă��邩
        for (auto& objects : object)
        {
            isHitObject[number] = ObjectHitCheck(objects->GetPosition(), objects->GetRadius(), calculation);
            
            if (isHitObject[number] && objects->GetIsCanCatch())
            {
                //�I�u�W�F�N�g���E����
                PickUpObject(*object[number], input);
            }
            number++;
        }

        if (!isInvincible)
        {
            //�G�̍U���̓����蔻��
            EnemyHitCheck(enemy, calculation);
        }
   
        Down();
    }
   
    Jump(input, moveVec);

    //�W�����v�͂�������
    moveVec.y = currentJumpPower;

    //�|�W�V�����X�V
    position = VAdd(position, moveVec);

    // �v���C���[�̃��f���̍��W���X�V����
    MV1SetPosition(modelHandle, position);

    //�v���C���[�̓����蔻��̍X�V
    topSpherePosition = VGet(position.x, position.y + 4.0f, position.z);
    bottomSpherePosition = VGet(position.x, position.y + 1.0f, position.z);

    //�U��
    if (input.GetNowFrameInput() & PAD_INPUT_C && stock >= 1 &&
        !(motionNum == down || motionNum == standUp || motionNum == pickUp_Hold ||
            motionNum == pickUp) && isAttackHold)
    {
        //�v���C���[�̌�����ۑ�
        //���K������
        keepTargetMoveDirection = VNorm(targetMoveDirection);
        keepTargetMoveDirection.y = 0;

        for (auto& objects : object)
        {
            if (objects->GetIsPlayerHold())
            {
                objects->SetIsThrow(true);
                stock--;
                if (stock <= 0)
                {
                    isAttackHold = false;
                    
                }
            }
        }
    }
    Attack(input);
    AttackHitCheck(enemy, calculation);

    //���G����
    if (isInvincible)
    {
        invincibleTime++;
        if (isDisplay)
        {
            isDisplay = false;
        }
        else
        {
            isDisplay = true;
        }

        if (invincibleTime >= 120.0f)
        {
            isInvincible = false;
            isDisplay = true;
            invincibleTime = 0;
        }
    }
    

    ///////////////////////////////////////
    //  ���[�V����
    //////////////////////////////////////

    MotionUpdate();

    ////////////////////////
    //�G�t�F�N�g
    ////////////////////////

    effectPosition = VGet(objectPosition.x, objectPosition.y, objectPosition.z);
    
    effect->PositionUpdate(effectPosition);
}

/// <summary>
///  �`��
/// </summary>
void Player::Draw(const Map& map)
{

    if (isDisplay)
    {
        MV1DrawModel(modelHandle);
    }

    //DrawSphere3D(topSpherePosition, radius, 16, GetColor(0, 0, 0), GetColor(255, 255, 255), false);
    if (!isHitObject)
    {
      //  DrawCapsule3D(topSpherePosition, bottomSpherePosition, radius, 16, GetColor(0, 0, 0), GetColor(255, 255, 255), false);
    }
    else
    {
       // DrawCapsule3D(topSpherePosition, bottomSpherePosition, radius, 16, GetColor(0, 0, 0), GetColor(0, 0, 255), false);
    }

    //DrawSphere3D(objectPosition, 1.5f, 16, GetColor(0, 0, 0), GetColor(255, 0, 0), false);
    //DrawLine3D(testPosition, closePosition, GetColor(255, 0, 0));

    if (isHitEnemyAttack)
    {
      //  clsDx();
        printfDx("Hit���Ă܂�\n");
    }
    else
    {
       // clsDx();
    }
    //�f�o�b�N�\��
    printfDx("player.HP %d\n",HP);
    printfDx("x.%f\n",position.x);
    printfDx("y.%f\n", position.y);
    printfDx("z.%f\n", position.z);
    printfDx("stock.%d\n",stock);

}

/// <summary>
/// �v���C���[�̉�]����
/// </summary>
void Player::UpdateAngle()
{
    // �v���C���[�̈ړ������Ƀ��f���̕������߂Â���
    float targetAngle;			// �ڕW�p�x
    float difference;			// �ڕW�p�x�ƌ��݂̊p�x�Ƃ̍�

    // �ڕW�̕����x�N�g������p�x�l���Z�o����
    targetAngle = static_cast<float>(atan2(targetMoveDirection.x, targetMoveDirection.z));

    // �ڕW�̊p�x�ƌ��݂̊p�x�Ƃ̍�������o��
    // �ŏ��͒P���Ɉ����Z
    difference = targetAngle - angle;

    // ����������炠������̍����P�W�O�x�ȏ�ɂȂ邱�Ƃ͖����̂�
    // ���̒l���P�W�O�x�ȏ�ɂȂ��Ă�����C������
    if (difference < -DX_PI_F)
    {
        difference += DX_TWO_PI_F;
    }
    else if (difference > DX_PI_F)
    {
        difference -= DX_TWO_PI_F;
    }

    // �p�x�̍����O�ɋ߂Â���
    if (difference > 0.0f)
    {
        // �����v���X�̏ꍇ�͈���
        difference -= AngleSpeed;
        if (difference < 0.0f)
        {
            difference = 0.0f;
        }
    }
    else
    {
        // �����}�C�i�X�̏ꍇ�͑���
        difference += AngleSpeed;
        if (difference > 0.0f)
        {
            difference = 0.0f;
        }
    }

    // ���f���̊p�x���X�V
    angle = targetAngle - difference;
    MV1SetRotationXYZ(modelHandle, VGet(0.0f, angle + DX_PI_F, 0.0f));
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="input"></param>
/// <param name="moveVec"></param>
void Player::Move(const Input& input, VECTOR& moveVec)
{

    isMove = false;

    if (input.GetNowFrameInput() & PAD_INPUT_UP)
    {
        moveVec = VAdd(moveVec, VGet(0, 0, 1));
        isMove = true;
    }
   
    if (input.GetNowFrameInput() & PAD_INPUT_DOWN)
    {
        moveVec = VAdd(moveVec, VGet(0, 0, -1));
        isMove = true;  
    }

    if (input.GetNowFrameInput() & PAD_INPUT_LEFT)
    {
        moveVec = VAdd(moveVec, VGet(-1, 0, 0));
        isMove = true;
    }
 
    if (input.GetNowFrameInput() & PAD_INPUT_RIGHT)
    {
        moveVec = VAdd(moveVec, VGet(1, 0, 0));
        isMove = true;
    }

    //�W�����v���Ă��Ȃ��Ƃ��ɃW�����v�{�^���������ꂽ�Ƃ��W�����v�͂�������
    if (input.GetNowFrameNewInput() & PAD_INPUT_A && !isJump)
    {
        // �x�������̑��x���Z�b�g
        currentJumpPower = JumpPower;
        isJump = true;
        Motion_HoldorUnHold(jump, jump_Hold);
    }

}

/// <summary>
/// �W�����v����
/// </summary>
/// <param name="input"></param>
/// <param name="moveVec"></param>
void Player::Jump(const Input& input, VECTOR& moveVec)
{
   
    if (isJump)
    {
        currentJumpPower -= Gravity;
    }

    if (isJump)
    {
        //pos.y��0����������ꍇ0�ɖ߂�
        if (position.y < 0.0f)
        {
            position.y = 0.0f;
            currentJumpPower = 0;
            isJump = false;
            //�󋵂ɉ����ă��[�V�����؂�ւ�
            if (isMove && !(motionNum == down || motionNum == standUp))
            {
                Motion_HoldorUnHold(run,run_Hold);
            }
            else if(!(motionNum == down || motionNum == standUp))
            {
                Motion_HoldorUnHold(stop,stop_Hold);
            }
        }
    }
}

/// <summary>
/// �I�u�W�F�N�g���E�����ǂ���
/// </summary>
/// <param name="object"></param>
/// <param name="input"></param>
void Player::PickUpObject(Object& object, const Input& input)
{

    //�I�u�W�F�N�g�ƃv���C���[�����������ꍇ����
    if (input.GetNowFrameInput() & PAD_INPUT_C || CheckHitKey(KEY_INPUT_5))
    {
        isAttackHold = true;
        ChangeMotion(pickUp_Hold);
        object.SetPlayerIsHit(true);
        //���ɐG�ꂽ�Ƃ��X�g�b�N�𑝂₷
        stock++;
    }
}

/// <summary>
/// �U��
/// </summary>
/// <param name="input"></param>
void Player::Attack(const Input& input)
{
    //�s���s�\��Ԃł͂Ȃ���΍U���\
    //if (input.GetNowFrameInput() & PAD_INPUT_C && stock >= 1 && 
    //    !(motionNum == down || motionNum == standUp || motionNum == pickUp_Hold ||
    //        motionNum == pickUp) && isAttackHold)
    //{
    //    if (!isPushKey)
    //    {
    //        //�v���C���[�̌�����ۑ�
    //        //���K������
    //        keepTargetMoveDirection = VNorm(targetMoveDirection);
    //        keepTargetMoveDirection.y = 0;

    //        //���x
    //        keepTargetMoveDirection = VScale(keepTargetMoveDirection, AttackSpeed);
    //        //�v���C���[�̈ʒu���猂�悤��
    //        objectPosition = VGet(topSpherePosition.x, topSpherePosition.y, topSpherePosition.z);

    //        attackSpeedY = JumpPower;
    //        isPushKey = true;
    //   
    //    }
    //}

}

void Player::AttackHitCheck(Enemy& enemy,Calculation& calculation)
{
    //�J�v�Z���Ƌ�
    VECTOR closePosition = calculation.CapsuleHitConfirmation(enemy.GetTopPosition(), enemy.GetBottomPosition(),
        objectPosition, enemy.GetRadius(), radius);
    testPosition = VGet(objectPosition.x, objectPosition.y, objectPosition.z);

    this->closePosition = VGet(closePosition.x, closePosition.y, closePosition.z);

    if (isPushKey)
    {
        isObjectHitEnemy = calculation.HitConfirmation(objectPosition, closePosition, radius, enemy.GetRadius());
        //�������������
        if (isObjectHitEnemy)
        {
            attackPosition = VGet(objectPosition.x, objectPosition.y, objectPosition.z);
            attackEffect->PositionUpdate(attackPosition);
            objectPosition = VGet(position.x, position.y, position.z);
            isPushKey = false;
            enemy.SetIsPlayerAttackHit(true);
        }
    }
  
    
}

/// <summary>
/// �I�u�W�F�N�g�ɓ������Ă��邩
/// </summary>
/// <param name="enemy"></param>
bool Player::ObjectHitCheck(const VECTOR objectPosition, 
    const float radius, Calculation& calculation)
{
    //�v���C���[�Ƌ��̍ł��߂��_
    VECTOR closePosition;       

    //�J�v�Z���Ƌ�
    closePosition = calculation.CapsuleHitConfirmation(topSpherePosition, bottomSpherePosition,
    objectPosition, this->radius, radius);

    //�������Ă��邩
    if (calculation.HitConfirmation(closePosition, objectPosition, this->radius, radius))
    {
        return true;
    }

    return false;
}

/// <summary>
/// �U���ɓ������Ă��邩
/// </summary>
/// <param name="enemy"></param>
void Player::EnemyHitCheck(Enemy& enemy,Calculation& calculation)
{
    //�J�v�Z���Ƌ�
    VECTOR closePosition = calculation.CapsuleHitConfirmation(topSpherePosition, bottomSpherePosition,
        enemy.bullet->GetPosition(), radius, enemy.bullet->GetRadius());

    //�v���C���[�ƓG�̍U�����ڐG������
    isHitEnemyAttack = calculation.HitConfirmation(closePosition, enemy.bullet->GetPosition(), radius, enemy.bullet->GetRadius());

    //�T�[�N���U���̓����蔻��
    if (enemy.circleAttack->isAttack)
    {
        for (auto& CircleAttack : enemy.circleAttack->getCircleAttacks())
        {
            //�J�v�Z���Ƌ�
            closePosition = calculation.CapsuleHitConfirmation(topSpherePosition, bottomSpherePosition,
                CircleAttack.position, radius, enemy.circleAttack->GetRadius());

            isHitEnemyAttack = calculation.HitConfirmation(closePosition, CircleAttack.position, radius, enemy.circleAttack->GetRadius());
            if (isHitEnemyAttack)
            {
                break;
            }
        }
    }

    //�u���X�Ƃ̓����蔻��
    if (enemy.breath->isAttack)
    {
        for (auto& breath : enemy.breath->getBreath())
        {
            isHitEnemyAttack = calculation.HitConfirmation(closePosition, breath.position, radius, enemy.circleAttack->GetRadius());

            if (isHitEnemyAttack)
            {
                break;
            }
        }
    }

}

/// <summary>
/// �U���ɂ������Ă���΍s���s�\�ɂȂ�
/// </summary>
void Player::Down()
{
    //�U���ɓ��������ꍇ�A�����̊ԍs���s�\�ɂ���@
    if (isHitEnemyAttack)
    {
        stock = 0;
        isAttackHold = false;
        HP--;
        ChangeMotion(down);
    }
}

/// <summary>
/// ���[�V�����؂�ւ�
/// </summary>
/// <param name="motionNum"></param>
void Player::ChangeMotion(int motionNum)
{
    //������
    MV1DetachAnim(modelHandle, attachIndex);
    // �Đ����Ԃ̏�����
    playTime = 0;
    // �Đ����Ԃ��Z�b�g����
    MV1SetAttachAnimTime(modelHandle, attachIndex, playTime);

    this->motionNum = motionNum;

    // �R�c���f���̂O�Ԗڂ̃A�j���[�V�������A�^�b�`����
    attachIndex = MV1AttachAnim(modelHandle, this->motionNum, -1, FALSE);

    // �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
    totalTime = MV1GetAttachAnimTotalTime(modelHandle, attachIndex);
}

void Player::Motion_HoldorUnHold(int motionNum, int holdMotionNum)
{
    if (!isAttackHold)
    {
        ChangeMotion(motionNum);
    }
    else if (isAttackHold)
    {
        ChangeMotion(holdMotionNum);
    }

    if (!isChangeMotion && !isJump)
    {
        isChangeMotion = true;
    }
    if (motionNum == stop)
    {
        isChangeMotion = false;
    }

}

/// <summary>
/// ���[�V�����X�V
/// </summary>
void Player::MotionUpdate()
{
    //down���[�V������
    if (motionNum == down)
    {
        playTime++;

        //playTime��totalTime�𒴂����烊�Z�b�g����
        if (playTime >= totalTime)
        {
            playTime = 0;
            ChangeMotion(standUp);
        }
    }
    else if (motionNum == standUp)
    {
        playTime += 1.2f;
    }

    //pickUp���[�V������
    else if (motionNum == pickUp || motionNum == pickUp_Hold)
    {
        playTime += 1.2f;
        if (playTime >= 53.0f)
        {
            Motion_HoldorUnHold(stand,stand_Hold);
            isChangeMotion = false;
        }
    }
    //�ҋ@���[�V����
    else if (motionNum == stand)
    {
        playTime += 0.6f;
        if (playTime >= 64.0f)
        {
            playTime = 0;
        }
    }
    else if (motionNum == stand_Hold)
    {
        playTime += 0.6f;
        if (playTime >= 59.0f)
        {
            playTime = 0;
        }
    }
    else
    {
        //���[�V������1f��������
        playTime += 0.6f;
    }

    
    //�~�܂郂�[�V�����̎����[�V�����I�������ꍇ�ҋ@���[�V�����ɕύX
    if (motionNum == stop || motionNum == stop_Hold 
        || motionNum == standUp)
    {
        if (playTime >= totalTime)
        {
            if (motionNum == standUp)
            {
                isInvincible = true;
            }
            Motion_HoldorUnHold(stand,stand_Hold);
            isChangeMotion = false;
            isHitEnemyAttack = false;

        }

    }

    if (motionNum == run_Hold && !isAttackHold)
    {
        ChangeMotion(run);
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
/// ���W�̎擾
/// </summary>
/// <param name="setPosition"></param>
void Player::GetPosition(VECTOR& setPosition)
{
    setPosition = VGet(position.x, position.y, position.z);
}


void Player::StartUpdate()
{
    VECTOR	moveVec = VGet(0, 0, 0);

    //player�̌�������
    UpdateAngle();

    if (position.z >= 0)
    {
        isMove = false;
    }
    else
    {
        moveVec = VAdd(moveVec, VGet(0, 0, 1));
        isMove = true;
    }

    //�ړ��{�^���������ꂽ�Ƃ����K��
    if (isMove)
    {
        targetMoveDirection = VNorm(moveVec);

        moveVec = VScale(targetMoveDirection, MoveSpeed);
        if (stock)
        {
            moveVec = VScale(targetMoveDirection, slowMoveSpeed);
        }

        //�����Ă��ăW�����v���łȂ���΃��[�V�����؂�ւ�
        if (!isChangeMotion && !isJump)
        {
            //���郂�[�V�����ɕύX
            Motion_HoldorUnHold(run, run_Hold);
        }

    }
    //�ړ����Ă��Ȃ��Ƃ�
    else
    {
        if (isChangeMotion && !isJump)
        {
            //�ҋ@���[�V�����ɕύX
            Motion_HoldorUnHold(stop, stop_Hold);
        }
    }

    //�|�W�V�����X�V
    position = VAdd(position, moveVec);

    // �v���C���[�̃��f���̍��W���X�V����
    MV1SetPosition(modelHandle, position);


    ///////////////////////////////////////
    //  ���[�V����
    //////////////////////////////////////

    MotionUpdate();
}