#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include <vector>
#include "EnemyBullet.h"
#include "Input.h"
#include <cmath>
#include "Object.h"

/// <summary>
/// �C���X�^���X��
/// </summary>
Object::Object()
{
    position = VGet(0, 0, 0);
    addPosition = VGet(0, 0, 0);
    radius = 3;
    graphHandle = LoadGraph("material/X.png");
    isHitPlayer = false;
    isHit = false;
    isGetPosition = false;
    isCanCatch = false;
    isHitBreath = false;
    isObjectHitEnemy = false;
    isDrop = false;
    effect = new Effect();
    attackEffect = new Effect();
    effect->Initialize("material/TouhouStrategy/black.efkefc", 1.2f, position);
    attackEffect->Initialize("material/TouhouStrategy/explosion.efkefc", 0.5f, VGet(0,0,0));
}

/// <summary>
/// 
/// </summary>
Object::~Object()
{

}

/// <summary>
/// ������
/// </summary>
void Object::Initialize(Enemy& enemy)
{
    position = VGet(0, 0, 0);
    addPosition = VGet(0, 0, 0);
    radius = 3;
    isHitPlayer = false;
    isHit = false;
    isGetPosition = false;
    isCanCatch = false;
    isHitBreath = false;
    isThrow = false;
    isPushKey = false;
    isObject = false;
    isObjectHitEnemy = false;
    isDrop = false;
    position = enemy.GetBottomPosition();
    addPosition = VGet(1, 0, 1);
    effect->StopEffect();
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="enemy"></param>
void Object::Update(Enemy& enemy, Calculation& calculation, const Input& input)
{
    //�G�̒e�����������I�u�W�F�N�g�𐶐�
    if (enemy.bullet->GetIsEmerge() && !isObject)
    {
        position = enemy.bullet->GetFellPosition();
        position.y += 5.0f;
        position.y = 3;
        enemy.bullet->SetIsEmerge(false);
        isObject = true;
    }


    if (isObject)
    {

        //�u���X��������������߂�悤�ɂ���
        if (enemy.breath->isAttack && !isHitBreath)
        {
            for (auto& breath : enemy.breath->getBreath())
            {
                if (!isCanCatch)
                {
                    isHitBreath = calculation.HitConfirmation(position, breath.position, radius, breath.radius);
                    if (isHitBreath)
                    {
                        isCanCatch = true;
                        AddPositionCalculation(breath.position);
                        effect->Initialize("material/TouhouStrategy/miko_hihou_effect.efkefc",1.2f, position);
                        break;
                    }
                }
            }
        }

        if (isCanCatch)
        {
            if (addPosition.z < -0.2f || addPosition.z > 0.2f)
            {
                position.x += addPosition.x;
                position.z += addPosition.z;
                addPosition = VSub(addPosition, subPosition);
            }
            else
            {
                addPosition = VGet(0, 0, 0);
            }
      
        }
        AttackHitCheck(enemy, calculation);

        //-----------------------------//
        //      �G�t�F�N�g�֘A
        //----------------------------//
        effect->StopEffect();
        effect->PlayEffect();
        effect->PositionUpdate(position);

    }
    //��������Ă��Ȃ��Ƃ��͌Œ�|�W��
    else
    {
        position = enemy.GetBottomPosition();
    }

    Throw(enemy);
}

/// <summary>
/// �`��
/// </summary>
void Object::Draw()
{
    if (isCanCatch)
    {
        VECTOR drawPosition = position;
        drawPosition.y = position.y + 4.0f;
        DrawBillboard3D(drawPosition, 0.5f, 0.5f, 1.5f, 0.0f, graphHandle, true);
    }
        printfDx("object.x %f\n", position.x);
        printfDx("object.z %f\n", position.z);

}

void Object::Throw(Enemy& enemy)
{
    //�s���s�\��Ԃł͂Ȃ���΍U���\
    if (isThrow)
    {
        if (!isPushKey)
        {
   
            keepTargetMoveDirection.y = 0;
            //���x
            keepTargetMoveDirection = VScale(keepTargetMoveDirection, AttackSpeed);

            attackSpeedY = JumpPower;
            isPushKey = true;
            isPlayerHold = false;
        }
    }

    //�U���̗���
    if (isPushKey)
    {
        position = VAdd(position, keepTargetMoveDirection);
        position.y += attackSpeedY;
        attackSpeedY -= Gravity;

        float maxRange = 33.0f;

        //���S����̋����𑪂�
        float r = VSize(VSub(position, VGet(0, 0, 0)));

        //���̋����ɒB�����炻��ȏア���Ȃ��悤�ɂ���
        if (r >= maxRange || r <= -maxRange)
        {
            if (position.y <= -50.0f)
            {
                isPushKey = false;
                isThrow = false;
                Reset(enemy);
            }
        }
        else
        {
            if (position.y <= 3.0f)
            {
                isHitPlayer = false;
                isPushKey = false;
                isThrow = false;
                isCanCatch = true;
                position.y = 3.0f;
            }
        }

    }
   
}


void Object::AttackHitCheck(Enemy& enemy, Calculation& calculation)
{
    //�J�v�Z���Ƌ�
    VECTOR closePosition = calculation.CapsuleHitConfirmation(enemy.GetTopPosition(), enemy.GetBottomPosition(),
        position, enemy.GetRadius(), radius);

   
    if (isPushKey)
    {

        isObjectHitEnemy = calculation.HitConfirmation(position, closePosition, radius, enemy.GetRadius());
        //�������������
        if (isObjectHitEnemy)
        {
            attackEffect->PlayEffect();
            attackEffect->PositionUpdate(position);
            attackEffect->SetSpeed(2.0f);
            position = enemy.GetBottomPosition();
            isPushKey = false;
            enemy.SetIsPlayerAttackHit(true);
            Reset(enemy);
        }
    }

    if (isObjectHitEnemy)
    {
     
        //���Ԍo��
        attackEffectTime++;

        if (attackEffectTime >= 105)
        {
            attackEffect->StopEffect();
            attackEffectTime = 0;
            isObjectHitEnemy = false;
        }

    }

}

/// <summary>
/// �����v�Z
/// </summary>
/// <param name="position"></param>
/// <param name="comparisonPosition"></param>
float Object::DirectionCalculation(const VECTOR comparisonPosition)
{
    //���ł����������v�Z
    float r = atan2((comparisonPosition.x - position.x),
        (comparisonPosition.z - position.z));

    return r;
}

/// <summary>
/// ���Z�v�Z
/// </summary>
/// <param name="comparisonPosition"></param>
void Object::AddPositionCalculation(const VECTOR comparisonPosition)
{
    float r = DirectionCalculation(comparisonPosition);
    addPosition = VGet(0, 0, 0);
    addPosition.x = cos(r);
    addPosition.z = sin(r);

    //���K������
    addPosition = VNorm(addPosition);
    if (addPosition.z > 0)
    {
        addPosition.z *= -1.0f;
    }

    addPosition = VScale(addPosition, speed);
    subPosition = VScale(addPosition, 0.2f);
}

/// <summary>
/// �̂����������Ɍ��ɓ�������
/// </summary>
void Object::LeanBackObject()
{
    if (isLeanBack)
    {
        DropSpeed = GravityPower;
        isDrop = true;
        isLeanBack = false;
        isPlayerHold = false;
        isHitPlayer = false;
        isPushKey = false;
        isThrow = false;
        isCanCatch = true;

        keepTargetMoveDirection.y = 0;
        keepTargetMoveDirection = VNorm(keepTargetMoveDirection);
        keepTargetMoveDirection = VScale(keepTargetMoveDirection,-backSpeed);

    }

    if (isDrop)
    {

        //�����𐳋K��
        VECTOR addPosition = VNorm(GetKeepTargetMoveDirection());

        //�����Ɉړ����x����Z
        addPosition = VScale(addPosition, backSpeed);

        position.y += DropSpeed;
        DropSpeed -= Gravity;

        position = VAdd(position, addPosition);

        if (position.y <= 3.0f)
        {
            position.y = 3.0f;
            isDrop = false;
        }
    }
}

/// <summary>
/// 
/// </summary>
void Object::LetGoCalculation(const VECTOR objectPosition)
{
    VECTOR addPosition = VGet(0, 0, 0);

    float r = DirectionCalculation(objectPosition);
    addPosition.x = cos(r);
    addPosition.z = sin(r);
    addPosition = VNorm(addPosition);

    addPosition = VScale(addPosition, 1.5f);
    position = VAdd(position,addPosition);

}

void Object::Reset(Enemy& enemy)
{
    effect->Initialize("material/TouhouStrategy/black.efkefc", 1.2f, position);
    position = enemy.GetBottomPosition();
    isHitPlayer = false;
    isCanCatch = false;
    isHitBreath = false;
    isObject = false;
    isThrow = false;
    isPushKey = false;
    addPosition = VGet(1, 0, 1);
    effect->StopEffect();
}