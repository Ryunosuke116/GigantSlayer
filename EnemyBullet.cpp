#include <iostream>
#include <vector>
#include <cmath>
#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include "Effect.h"
#include "EnemyCircleAttack.h"
#include "EnemyBullet.h"


/// <summary>
/// インスタンス化
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
    scale = 0;
    effectPlayStack = 0;

    bulletSpeed_Y = 2.0f;
    isAttack = false;
    isEffect = false;
    isEmerge = false;
    isCircleBullet = false;
    isSetUpMotion = false;

    if (effect == NULL)
    {
        effect = new Effect();
        bulletColor = new Effect();

    }
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyBullet::~EnemyBullet()
{

}

/// <summary>
/// 初期化
/// </summary>
void EnemyBullet::Initialize(const VECTOR EnemyPosition)
{
    //ポジション初期化
    position = VGet(EnemyPosition.x, EnemyPosition.y + 35, EnemyPosition.z);
    //初期化
    effect->Initialize("material/TouhouStrategy/patch_stElmo_area.efkefc", 1.2f, position);
    bulletColor->Initialize("material/TouhouStrategy/enemyBullet.efkefc", 1.6f, position);
    effect->StopEffect();
    bulletColor->StopEffect();
    isAttack = false;
    isEffect = false;
    isEmerge = false;
    isCircleBullet = false;
    isSetUpMotion = false;

}

/// <summary>
/// 更新
/// </summary>
void EnemyBullet::Update(const VECTOR EnemyPosition, 
    EnemyCircleAttack& circleAttack)
{

    AttackDesignation(EnemyPosition);
  
    //弾の流れ
    Move(EnemyPosition, circleAttack);

    //エフェクトを再生
    if (isEffect)
    {
        //発動してから60fの間再生
        if (effectPlayStack <= 120)
        {
            effectPlayStack++;
            //エフェクトを再生
            effect->PositionUpdate(effectPosition);
        }
        else
        {
            //エフェクトを停止
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
/// 動き
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
            if (scale >= 1.0f)
            {
                scale = 1.0f;
            }
        }
        bulletColor->SetScale(VGet(scale, scale, scale));
    }



    if (isAttack)
    {
        BulletMove();

        bulletSpeed_Y -= 0.05f;
        //　0になるまで落下させる　
        if (position.y > 0.0f)
        {
            position.y += bulletSpeed_Y;
        }
        //　 0まで落下したとき
        else
        {
            //サークル攻撃の場合、オブジェクトは発生しない
            if (isCircleBullet)
            {
                circleAttack.isAttack = true;
            }
            else
            {
                isEmerge = true;
            }

            //弾をリセット
            ResetAttack(enemyPosition);

            
            //bulletが落ちた座標をcircleAttackに渡す
            if (circleAttack.isAttack)
            {
                circleAttack.SetPosition(fellPosition);
            }

            //サークル攻撃をしなければ再生
            if (!isCircleBullet)
            {
                //エフェクト再生開始
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

    //落下地点を保存
    fellPosition = GetPosition();
    effectPosition = VGet(fellPosition.x, fellPosition.y, fellPosition.z);

    //bulletの座標をリセットする
    position = VGet(enemyPosition.x, enemyPosition.y + 35, enemyPosition.z);
    bulletColor->PositionUpdate(position);
    bulletColor->StopEffect();
    positionStack = 0;
    scale = 0;
    bulletSpeed_Y = 2.5f;
}

/// <summary>
/// 弾を落とす座標を決める
/// </summary>
void EnemyBullet::AttackDesignation(const VECTOR EnemyPosition)
{

    //弾を落とす位置を決める
    bulletSpeed = VSub(playerPos, position);
    bulletSpeed.y = 0;
    //弾の弾道の正規化
    bulletSpeed = VNorm(bulletSpeed);
    //スピードを調整
    bulletSpeed = VScale(bulletSpeed, speed);
}

void EnemyBullet::BulletMove()
{  
    //サークル攻撃の場合
    if (isCircleBullet)
    {
        position.z -= circleAttackBulletSpeed;
    }
    //サークル攻撃じゃない場合
    else
    {
        //25fまでプレイヤーを追従する
        if (positionStack < maxPositionStack)
        {
            position.z += bulletSpeed.z;
            position.x += bulletSpeed.x;

            positionStack++;
        }
    }
  
}


/// <summary>
/// プレイヤー座標を更新
/// </summary>
/// <param name="getPosition"></param>
void EnemyBullet::SetPlayerPosition(VECTOR& getPosition)
{
    playerPos = VGet(getPosition.x, getPosition.y, getPosition.z);
}

/// <summary>
/// 座標を更新
/// </summary>
/// <param name="getPosition"></param>
void EnemyBullet::SetPosition(VECTOR& getPosition)
{
    position = VGet(getPosition.x, getPosition.y + 15.0f, getPosition.z);
}

/// <summary>
/// フラグ切り替え
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