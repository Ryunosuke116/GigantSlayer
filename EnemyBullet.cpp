#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include <vector>
#include <cmath>
#include "Enemy.h"
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
    //インスタンス化
    effect = new Effect;
    bulletColor = new Effect;
    //初期化
    effect->Initialize("material/TouhouStrategy/patch_stElmo_area.efkefc", 1.2f,position);
    bulletColor->Initialize("material/TouhouStrategy/enemyBullet.efkefc", 1.6f, position);
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
void EnemyBullet::Move(const VECTOR EnemyPosition,EnemyCircleAttack& circleAttack)
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
        //　0になるまで落下させる　
        if (position.y > 0.0f)
        {
            position.y += bulletSpeed_Y;
        }
        //　 0まで落下したとき
        else
        {
            isAttack = false;
            isEffect = true;
            isSetUpMotion = false;
            
            //サークル攻撃の場合、オブジェクトは発生しない
            if (isCircleBullet)
            {
                circleAttack.isAttack = true;
            }
            else
            {
                isEmerge = true;
            }

            //bulletが落ちた座標をcircleAttackに渡す
            fellPosition = GetPosition();
            circleAttack.SetPosition(fellPosition);
            effectPosition = VGet(fellPosition.x, fellPosition.y, fellPosition.z);
            bulletSpeed_Y = 2.5f;

            //bulletの座標をリセットする
            position = VGet(EnemyPosition.x, EnemyPosition.y + 35, EnemyPosition.z);
            bulletColor->PositionUpdate(position);
            positionStack = 0;
            scale = 0;

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
/// プレイヤーの移動速度を保存する
/// </summary>
/// <param name="moveSpeed"></param>
void EnemyBullet::SetPlayerMoveSpeed(float moveSpeed)
{
    playerMoveSpeed = moveSpeed;
}

/// <summary>
/// プレイヤーが移動時に未来の座標を計算
/// </summary>
void EnemyBullet::PlayerMovementPrediction()
{
    //40フレーム先のプレイヤーのポジションを探る
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
/// プレイヤーが動いているかどうか
/// </summary>
/// <param name="isMove"></param>
void EnemyBullet::SetIsPlayerMove(bool isMove)
{
    isPlayerMove = isMove;
}

/// <summary>
/// プレイヤーがどの方向に動いているか
/// </summary>
/// <param name="isTopMove"></param>
/// <param name="isBottomMove"></param>
/// <param name="isRightMove"></param>
/// <param name="isLeftMove"></param>
void EnemyBullet::SetIsPlayerMoveDirection(bool isTopMove, bool isBottomMove, bool isRightMove, bool isLeftMove)
{
    this->isTopMove = isTopMove;
    this->isBottomMove = isBottomMove;
    this->isRightMove = isRightMove;
    this->isLeftMove = isLeftMove;
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