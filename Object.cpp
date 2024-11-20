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
    isHitPlayer = false;
    isHit = false;
    isGetPosition = false;
    isCanCatch = false;
    isHitBreath = false;
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
    effect = new Effect();
    effect->Initialize("material/TouhouStrategy/miko_hihou_effect.efkefc",
        1.2f, position);
    enemy.GetPosition(position);
    addPosition = VGet(1, 0, 1);
    isObject = false;
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
        enemy.bullet->SetIsEmerge(false);
        isObject = true;
    }

    if (isObject)
    {
        //オブジェクトとプレイヤーが当たった場合消す
        if (isHitPlayer && isCanCatch && CheckHitKey(KEY_INPUT_5))
        {
            enemy.GetPosition(position);
            isHitPlayer = false;
            isCanCatch = false;
            isHitBreath = false;
            isObject = false;
            addPosition = VGet(1, 0, 1);
        }

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
                        DirectionCalculation(breath.position);

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
        enemy.GetPosition(position);
    }

    
}

/// <summary>
/// どのオブジェクトを起動するか
/// </summary>
/// <param name="enemy"></param>
void Object::WhichOnObject(Enemy& enemy)
{
    if (enemy.bullet->GetIsEmerge() && !isObject)
    {
        isObject = true;
        enemy.bullet->SetIsEmerge(false);
    }
}

void Object::WhichOffObject(const bool& isEmerge)
{
    isObject = false;
}

/// <summary>
/// 描画
/// </summary>
void Object::Draw()
{
    if (isObject)
    {
        //DrawSphere3D(position, radius, 16, GetColor(0, 0, 0), GetColor(255, 255, 255), false);
    }
        printfDx("object.x %f\n", position.x);
        printfDx("object.z %f\n", position.z);

}

/// <summary>
/// プレイヤーが当たっているかどうか
/// </summary>
/// <param name="isHit"></param>
void Object::PlayerIsHit(const bool& isHit)
{
   isHitPlayer = isHit;
}

/// <summary>
/// つかめるか
/// </summary>
/// <param name="value"></param>
void Object::SetIsCanCatch(const bool& value)
{
    isCanCatch = value;
}

/// <summary>
/// 方向計算
/// </summary>
/// <param name="position"></param>
/// <param name="comparisonPosition"></param>
void Object::DirectionCalculation(const VECTOR comparisonPosition)
{
    addPosition = VGet(0, 0, 0);
    //飛んでいく方向を計算
    float r = atan2((comparisonPosition.x - position.x),
        (comparisonPosition.z - position.z));
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