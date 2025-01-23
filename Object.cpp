#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include <vector>
#include "EnemyBullet.h"
#include "Input.h"
#include <cmath>
#include "Object.h"

/// <summary>
/// インスタンス化
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
/// 初期化
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
/// 更新
/// </summary>
/// <param name="enemy"></param>
void Object::Update(Enemy& enemy, Calculation& calculation, const Input& input)
{
    //敵の弾が落ちた時オブジェクトを生成
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

        //ブレスが当たったらつかめるようにする
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
        //      エフェクト関連
        //----------------------------//
        effect->StopEffect();
        effect->PlayEffect();
        effect->PositionUpdate(position);

    }
    //生成されていないときは固定ポジへ
    else
    {
        position = enemy.GetBottomPosition();
    }

    Throw(enemy);
}

/// <summary>
/// 描画
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
    //行動不能状態ではなければ攻撃可能
    if (isThrow)
    {
        if (!isPushKey)
        {
   
            keepTargetMoveDirection.y = 0;
            //速度
            keepTargetMoveDirection = VScale(keepTargetMoveDirection, AttackSpeed);

            attackSpeedY = JumpPower;
            isPushKey = true;
            isPlayerHold = false;
        }
    }

    //攻撃の流れ
    if (isPushKey)
    {
        position = VAdd(position, keepTargetMoveDirection);
        position.y += attackSpeedY;
        attackSpeedY -= Gravity;

        float maxRange = 33.0f;

        //中心からの距離を測る
        float r = VSize(VSub(position, VGet(0, 0, 0)));

        //一定の距離に達したらそれ以上いけないようにする
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
    //カプセルと球
    VECTOR closePosition = calculation.CapsuleHitConfirmation(enemy.GetTopPosition(), enemy.GetBottomPosition(),
        position, enemy.GetRadius(), radius);

   
    if (isPushKey)
    {

        isObjectHitEnemy = calculation.HitConfirmation(position, closePosition, radius, enemy.GetRadius());
        //当たったら消す
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
     
        //時間経過
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
/// 方向計算
/// </summary>
/// <param name="position"></param>
/// <param name="comparisonPosition"></param>
float Object::DirectionCalculation(const VECTOR comparisonPosition)
{
    //飛んでいく方向を計算
    float r = atan2((comparisonPosition.x - position.x),
        (comparisonPosition.z - position.z));

    return r;
}

/// <summary>
/// 加算計算
/// </summary>
/// <param name="comparisonPosition"></param>
void Object::AddPositionCalculation(const VECTOR comparisonPosition)
{
    float r = DirectionCalculation(comparisonPosition);
    addPosition = VGet(0, 0, 0);
    addPosition.x = cos(r);
    addPosition.z = sin(r);

    //正規化する
    addPosition = VNorm(addPosition);
    if (addPosition.z > 0)
    {
        addPosition.z *= -1.0f;
    }

    addPosition = VScale(addPosition, speed);
    subPosition = VScale(addPosition, 0.2f);
}

/// <summary>
/// のけぞった時に後ろに投げられる
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

        //方向を正規化
        VECTOR addPosition = VNorm(GetKeepTargetMoveDirection());

        //方向に移動速度を乗算
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