#include <vector>
#include <time.h>
#include "DxLib.h"
#include "EnemyBullet.h"
#include "EnemyCircleAttack.h"
#include "EnemyBreath.h"
#include "Calculation.h"
#include "Enemy.h"

/// <summary>
/// インスタンス化
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
/// 初期化
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
        //モデル読み込み
        modelHandle = MV1LoadModel("material/mv1/mutant_1031.mv1");
        //モデルの大きさ調整
        MV1SetScale(modelHandle, VGet(0.4f, 0.4f, 0.4f));
    }

    // プレイヤーのモデルの座標を更新する
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

    //待機モーション読み込み
    ChangeMotion(stand);
    
}

/// <summary>
/// 更新
/// </summary>
void Enemy::Update(Calculation& calculation)
{
    //向く方向
    UpdateDirection();

    //通常時は正面を向く
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

    //攻撃の更新
    for (auto& bullets : bullet)
    {
        bullets->Update(bottomPosition, *circleAttack);
    }
    circleAttack->Update();
    breath->Update();

    //行動の流れを制御
    ActionFlow(*bullet, *circleAttack, *breath, calculation);

    if (bullet[0]->GetIsAttack())
    {
        isBootBullet = true;
    }
    else
    {
        isBootBullet = false;
    }

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

    //HPが一定以下になると行動変化
    if (HP < 50)
    {
        isAnger = true;
    }
}

/// <summary>
/// 描画
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
/// 方向計算
/// </summary>
void Enemy::UpdateDirection()
{
    //ブレス攻撃ではないときは正面を向く
    if (motionNum != breathAttack)
    {
        direction = VSub(VGet(0, 0, 0), bottomPosition);
    }
    //ブレス攻撃時、プレイヤーの方向を向く
    else
    {
        direction = VSub(playerPos, bottomPosition);
    }
    direction.y = 0;

    //正規化
    if (VSize(direction) != 0)
    {
        direction = VNorm(direction);
    }
    
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
            playTime += 0.02f;
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
void Enemy::ActionFlow(EnemyBullet bullet[], EnemyCircleAttack& circleAttack,
                       EnemyBreath& breath, Calculation& calculation)
{   
    //待機中50fごとに行動する
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

    //弾攻撃
    if (motionNum == bulletAttack)
    {
        //攻撃を放つモーションに入った時攻撃する
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
    //のけぞり
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
    //ブレス攻撃
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

/// <summary>
/// 開始時
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