#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include <vector>
#include "EnemyBullet.h"
#include "EnemyCircleAttack.h"
#include "EnemyBreath.h"
#include "Enemy.h"

/// <summary>
/// インスタンス化
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
/// 初期化
/// </summary>
void Enemy::Initialize()
{
    HP = 100;
    bottomPosition = VGet(0, -30, 60);
    topPosition = VGet(bottomPosition.x, bottomPosition.y + 50.0f, bottomPosition.z);
    bulletPosition = VGet(bottomPosition.x, bottomPosition.y + 20, bottomPosition.z);
    addPlayTime = 0.4f;
    //モデル読み込み
    modelHandle = MV1LoadModel("material/mv1/mutant_1031.mv1");

    //モデルの大きさ調整
    MV1SetScale(modelHandle, VGet(0.4f, 0.4f, 0.4f));

    // プレイヤーのモデルの座標を更新する
    MV1SetPosition(modelHandle, bottomPosition);
    bullet->Initialize(bottomPosition);
    circleAttack->SetPosition(bullet->GetPosition());
    breath->SetPosition(bullet->GetPosition());
    circleAttack->Initialize();
    breath->Initialize();

    //待機モーション読み込み
    ChangeMotion(stand);

}

/// <summary>
/// 更新
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

    //攻撃の更新
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
    //モーション更新
    MotionUpdate();

    //弾攻撃のモーション中は別でポジションを用意
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
/// 描画
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
/// 弾を落とす座標を決める
/// </summary>
void Enemy::AttackDesignation()
{
    bulletSpeed = VGet(0, 0, 0);

    //弾の弾道の初期化
    bulletSpeed = VNorm(bulletSpeed);

    //弾を落とす位置を決める
    bulletSpeed = VSub(playerPos, bulletPosition);
   
    bulletSpeed = VScale(bulletSpeed, 0.025);

}

/// <summary>
/// モーション切り替え
/// </summary>
/// <param name="motionNum"></param>
void Enemy::ChangeMotion(int motionNum)
{
    MV1DetachAnim(modelHandle, attachIndex);
    // 再生時間の初期化
    playTime = 0;
    // 再生時間をセットする
    MV1SetAttachAnimTime(modelHandle, attachIndex, playTime);
    this->motionNum = motionNum;
    isAttack = false;

    // ３Ｄモデルの０番目のアニメーションをアタッチする
    attachIndex = MV1AttachAnim(modelHandle, motionNum, -1, FALSE);
    // アタッチしたアニメーションの総再生時間を取得する
    totalTime = MV1GetAttachAnimTotalTime(modelHandle, attachIndex);
}

/// <summary>
/// モーション更新
/// </summary>
void Enemy::MotionUpdate()
{
    //待機時
    if (motionNum == stand)
    {
      playTime += 0.8f;
    }
    //弾攻撃
    else if(motionNum == bulletAttack)
    {
        playTime += 0.55f;
    }
    //ブレス攻撃
    else if(motionNum == breathAttack)
    {
        playTime += 0.8f;
    }
    //のけぞり
    else if (motionNum == knockback)
    {
        if (HP > 0)
        {
            playTime += addPlayTime;

            //一定数を超えると逆再生
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

    //止まるモーションの時モーション終了した場合待機モーションに変更
    if (motionNum != stand)
    {
        //弾を出すときのモーション
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

    

    //playTimeがtotalTimeを超えたらリセットする
    if (playTime >= totalTime)
    {
        playTime = 0;
    }

    // 再生時間をセットする
    MV1SetAttachAnimTime(modelHandle, attachIndex, playTime);
}

/// <summary>
/// 行動の流れ
/// </summary>
void Enemy::ActionFlow(EnemyBullet& bullet, EnemyCircleAttack& circleAttack,
                       EnemyBreath& breath)
{   
    //待機中50fごとに行動する
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


    //弾攻撃
    if (motionNum == bulletAttack)
    {
        //攻撃を放つモーションに入った時攻撃する
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
    //のけぞり
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
    //ブレス攻撃
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
/// 敵の行動順
/// </summary>
void Enemy::Order(EnemyBullet& bullet,EnemyBreath& breath)
{
    //弾攻撃
    if (orderNumber == 0)
    {
        //何回攻撃するか
        if (!isBulletNumber)
        {
            //弾の種類切り替え
            bullet.SetIsCircleBullet(false);
            srand((unsigned int)time(NULL));
            maxBulletNumber = rand() % 2 + 2;
            isBulletNumber = true;
        }
        //最大回数分攻撃する
        if (maxBulletNumber > bulletNumber)
        {
            bulletNumber++;
            ChangeMotion(bulletAttack);
        }
        //攻撃し終えたら次の攻撃に
        else
        {
            orderNumber++;
            bulletNumber = 0;
            isBulletNumber = false;
        
        }
        
    }
    //ブレス攻撃
    else if (orderNumber == 1)
    {
        orderNumber++;
        ChangeMotion(breathAttack);
        breath.Rotation(playerPos, bottomPosition);
    }
    //サークル攻撃
    else if (orderNumber == 2)
    {
        //弾の種類切り替え
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