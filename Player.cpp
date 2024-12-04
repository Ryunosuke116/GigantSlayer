#include "Input.h"
#include "Player.h" 
#include <iostream>
#include <array>

/// <summary>
/// インスタンス化
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
    currentJumpPower = 0;
    playingEffectHandle = -1;
    motionNumber = 0;
    //モデルの読み込み
    modelHandle = MV1LoadModel("material/mv1/maria_1204.mv1");

    MV1SetScale(modelHandle, VGet(0.04f, 0.04f, 0.04f));
    //エフェクトのインスタンス化、初期化
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
/// 初期化
/// </summary>
void Player::Initialize()
{
    HP = 3;
    position = VGet(0, 0, 0);
    targetMoveDirection = VGet(0, 0, 0);
    objectPosition = VGet(0, 5, 0);
    keepTargetMoveDirection = VGet(0, 0, 0);
    effectPosition = VGet(0, 0, 0);
    topSpherePosition = VGet(0, 0, 0);
    bottomSpherePosition = VGet(0, 0, 0);
    testPosition = VGet(0, 0, 0);


    //待機モーション読み込み
    ChangeMotion(stand);

    effectPosition = VGet(objectPosition.x, objectPosition.y, objectPosition.z);
    
    effect->Initialize("material/TouhouStrategy/miko_hihou_effect.efkefc",1.2f, effectPosition);
    attackEffect->Initialize("material/TouhouStrategy/explosion.efkefc", 0.5f, effectPosition);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="calculation"></param>
/// <param name="object"></param>
/// <param name="input"></param>
/// <param name="enemy"></param>
void Player::Update(Calculation& calculation,
    std::array<Object*, 4> object,
    const Input& input, Enemy& enemy)
{

    VECTOR	moveVec = VGet(0, 0, 0);

    //playerの向き調整
    UpdateAngle();

    //攻撃をされたときは動かせない
    if (!(motionNum == down || motionNum == standUp))
    {
        //移動
        Move(input, moveVec);

        //移動ボタンが押されたとき正規化
        if (isMove)
        {
            targetMoveDirection = VNorm(moveVec);

            moveVec = VScale(targetMoveDirection, MoveSpeed);
            if (stock)
            {
                moveVec = VScale(targetMoveDirection, slowMoveSpeed);
            }

            //動いていてジャンプ中でなければモーション切り替え
            if (!isChangeMotion && !isJump)
            {
                //走るモーションに変更
                ChangeMotion(run);
                isChangeMotion = true;
            }

        }
        //移動していないとき
        else
        {
            if (isChangeMotion)
            {
                //待機モーションに変更
                ChangeMotion(stop);
                isChangeMotion = false;
            }
        }

        int number = 0;

        //オブジェクトと接触しているか
        for (auto& objects : object)
        {
            isHitObject[number] = ObjectHitCheck(objects->GetPosition(), objects->GetRadius(), calculation);
            
            if (isHitObject[number] && objects->GetIsCanCatch())
            {
                //オブジェクトを拾うか
                PickUpObject(*object[number], input);
            }
            number++;
        }


        //敵の攻撃の当たり判定
        EnemyHitCheck(enemy, calculation);
   
        Down();
    }
   
    Jump(input, moveVec);

    //ジャンプ力を加える
    moveVec.y = currentJumpPower;

    //ポジション更新
    position = VAdd(position, moveVec);

    // プレイヤーのモデルの座標を更新する
    MV1SetPosition(modelHandle, position);

    //プレイヤーの当たり判定の更新
    topSpherePosition = VGet(position.x, position.y + 4.0f, position.z);
    bottomSpherePosition = VGet(position.x, position.y + 1.0f, position.z);

    //攻撃
    Attack(input);
    AttackHitCheck(enemy, calculation);
    

    ///////////////////////////////////////
    //  モーション
    //////////////////////////////////////

    MotionUpdate();

    //中心からプレイヤーの距離を測る
    float r = VSize(VSub(position,VGet(0,0,0)) );

    //一定の距離に達したらそれ以上いけないようにする
    if (r >= maxRange || r <= -maxRange)
    {
        //中心座標からプレイヤー座標の距離
        VECTOR distance = VSub(VGet(0, 0, 0), position);
        //正規化
        distance = VNorm(distance);
        //戻す量を計算、加算する
        VECTOR returnPosition = VScale(distance, (r - maxRange));
        position = VAdd(position, returnPosition);
    }

    ////////////////////////
    //エフェクト
    ////////////////////////

    effectPosition = VGet(objectPosition.x, objectPosition.y, objectPosition.z);
    
    effect->PositionUpdate(effectPosition);
}

/// <summary>
///  描画
/// </summary>
void Player::Draw()
{
    
    //DrawSphere3D(topSpherePosition, radius, 16, GetColor(0, 0, 0), GetColor(255, 255, 255), false);
    if (!isHitObject)
    {
      //  DrawCapsule3D(topSpherePosition, bottomSpherePosition, radius, 16, GetColor(0, 0, 0), GetColor(255, 255, 255), false);
    }
    else
    {
       // DrawCapsule3D(topSpherePosition, bottomSpherePosition, radius, 16, GetColor(0, 0, 0), GetColor(0, 0, 255), false);
    }
    DrawSphere3D(objectPosition, 1.5f, 16, GetColor(0, 0, 0), GetColor(255, 0, 0), false);
    DrawLine3D(testPosition, closePosition, GetColor(255, 0, 0));

    if (isHitEnemyAttack)
    {
      //  clsDx();
        printfDx("Hitしてます\n");
    }
    else
    {
       // clsDx();
    }
    //デバック表示
    printfDx("player.HP %d\n",HP);
    printfDx("x.%f\n",position.x);
    printfDx("y.%f\n", position.y);
    printfDx("z.%f\n", position.z);
    printfDx("stock.%d\n",stock);


    MV1DrawModel(modelHandle);

}

/// <summary>
/// プレイヤーの回転制御
/// </summary>
void Player::UpdateAngle()
{
    // プレイヤーの移動方向にモデルの方向を近づける
    float targetAngle;			// 目標角度
    float difference;			// 目標角度と現在の角度との差

    // 目標の方向ベクトルから角度値を算出する
    targetAngle = static_cast<float>(atan2(targetMoveDirection.x, targetMoveDirection.z));

    // 目標の角度と現在の角度との差を割り出す
    // 最初は単純に引き算
    difference = targetAngle - angle;

    // ある方向からある方向の差が１８０度以上になることは無いので
    // 差の値が１８０度以上になっていたら修正する
    if (difference < -DX_PI_F)
    {
        difference += DX_TWO_PI_F;
    }
    else if (difference > DX_PI_F)
    {
        difference -= DX_TWO_PI_F;
    }

    // 角度の差が０に近づける
    if (difference > 0.0f)
    {
        // 差がプラスの場合は引く
        difference -= AngleSpeed;
        if (difference < 0.0f)
        {
            difference = 0.0f;
        }
    }
    else
    {
        // 差がマイナスの場合は足す
        difference += AngleSpeed;
        if (difference > 0.0f)
        {
            difference = 0.0f;
        }
    }

    // モデルの角度を更新
    angle = targetAngle - difference;
    MV1SetRotationXYZ(modelHandle, VGet(0.0f, angle + DX_PI_F, 0.0f));
}

/// <summary>
/// 移動処理
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

    //ジャンプしていないときにジャンプボタンが押されたときジャンプ力を加える
    if (input.GetNowFrameNewInput() & PAD_INPUT_A && !isJump)
    {
        // Ｙ軸方向の速度をセット
        currentJumpPower = JumpPower;
        isJump = true;
        ChangeMotion(jump);
    }

}

/// <summary>
/// ジャンプ処理
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
        //pos.yが0を下回った場合0に戻す
        if (position.y < 0.0f)
        {
            position.y = 0.0f;
            currentJumpPower = 0;
            isJump = false;
            //状況に応じてモーション切り替え
            if (isMove && !(motionNum == down || motionNum == standUp))
            {
                ChangeMotion(run);
            }
            else if(!(motionNum == down || motionNum == standUp))
            {
                ChangeMotion(stop);
            }
        }
    }
}

/// <summary>
/// オブジェクトを拾うかどうか
/// </summary>
/// <param name="object"></param>
/// <param name="input"></param>
void Player::PickUpObject(Object& object, const Input& input)
{

    //オブジェクトとプレイヤーが当たった場合消す
    if (input.GetNowFrameInput() & PAD_INPUT_X || CheckHitKey(KEY_INPUT_5))
    {
        ChangeMotion(pickUp);
        object.PlayerIsHit(true);
        //球に触れたときストックを増やす
        stock++;
    }
}

/// <summary>
/// 攻撃
/// </summary>
/// <param name="input"></param>
void Player::Attack(const Input& input)
{
    //行動不能状態ではなければ攻撃可能
    if (input.GetNowFrameInput() & PAD_INPUT_B && stock >= 1 && 
        !(motionNum == down || motionNum == standUp))
    {
        if (!isPushKey)
        {
            //プレイヤーの向きを保存
            //正規化する
            keepTargetMoveDirection = VNorm(targetMoveDirection);
            keepTargetMoveDirection.y = 0;
            //速度
            keepTargetMoveDirection = VScale(keepTargetMoveDirection, AttackSpeed);
            //プレイヤーの位置から撃つように
            objectPosition = VGet(position.x, position.y, position.z);

            attackSpeedY = JumpPower;
            isPushKey = true;
            stock--;
        }
    }

    //攻撃の流れ
    if (isPushKey)
    {
        objectPosition = VAdd(objectPosition, keepTargetMoveDirection);
        objectPosition.y += attackSpeedY;
        attackSpeedY -= Gravity;

        if (objectPosition.y <= 0)
        {
            isPushKey = false;
        }
    }
    else
    {
        objectPosition = VGet(position.x, position.y, position.z);
    }

    if (isObjectHitEnemy)
    {
        if (attackEffectTime == 0)
        {
            attackEffect->PlayEffect();
            attackEffect->PositionUpdate(attackPosition);
            attackEffect->SetSpeed(2.0f);
        }
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

void Player::AttackHitCheck(Enemy& enemy,Calculation& calculation)
{
    //カプセルと球
    VECTOR closePosition = calculation.CapsuleHitConfirmation(enemy.GetTopPosition(), enemy.GetBottomPosition(),
        objectPosition, enemy.GetRadius(), radius);
    testPosition = VGet(objectPosition.x, objectPosition.y, objectPosition.z);

    this->closePosition = VGet(closePosition.x, closePosition.y, closePosition.z);

    if (isPushKey)
    {
        isObjectHitEnemy = calculation.HitConfirmation(objectPosition, closePosition, radius, enemy.GetRadius());
        //当たったら消す
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
/// オブジェクトに当たっているか
/// </summary>
/// <param name="enemy"></param>
bool Player::ObjectHitCheck(const VECTOR objectPosition, 
    const float radius, Calculation& calculation)
{
    //プレイヤーと球の最も近い点
    VECTOR closePosition;       

    //カプセルと球
    closePosition = calculation.CapsuleHitConfirmation(topSpherePosition, bottomSpherePosition,
    objectPosition, this->radius, radius);

    //当たっているか
    if (calculation.HitConfirmation(closePosition, objectPosition, this->radius, radius))
    {
        return true;
    }

    return false;
}

/// <summary>
/// 攻撃に当たっているか
/// </summary>
/// <param name="enemy"></param>
void Player::EnemyHitCheck(Enemy& enemy,Calculation& calculation)
{
    //カプセルと球
    VECTOR closePosition = calculation.CapsuleHitConfirmation(topSpherePosition, bottomSpherePosition,
        enemy.bullet->GetPosition(), radius, enemy.bullet->GetRadius());

    //プレイヤーと敵の攻撃が接触したか
    isHitEnemyAttack = calculation.HitConfirmation(closePosition, enemy.bullet->GetPosition(), radius, enemy.bullet->GetRadius());

    //testPosition = VGet(enemy.bullet->GetPosition().x, enemy.bullet->GetPosition().y, enemy.bullet->GetPosition().z);

    //サークル攻撃の当たり判定
    if (enemy.circleAttack->isAttack)
    {
        for (auto& CircleAttack : enemy.circleAttack->getCircleAttacks())
        {
            //カプセルと球
            closePosition = calculation.CapsuleHitConfirmation(topSpherePosition, bottomSpherePosition,
                CircleAttack.position, radius, enemy.circleAttack->GetRadius());

            isHitEnemyAttack = calculation.HitConfirmation(closePosition, CircleAttack.position, radius, enemy.circleAttack->GetRadius());
            if (isHitEnemyAttack)
            {
                break;
            }
        }
    }

    //ブレスとの当たり判定
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
/// 攻撃にあたっていれば行動不能になる
/// </summary>
void Player::Down()
{
    //攻撃に当たった場合、少しの間行動不能にする　
    if (isHitEnemyAttack)
    {
        //HP--;
        ChangeMotion(down);
    }
}

/// <summary>
/// モーション切り替え
/// </summary>
/// <param name="motionNum"></param>
void Player::ChangeMotion(int motionNum)
{
    MV1DetachAnim(modelHandle, attachIndex);
    // 再生時間の初期化
    playTime = 0;
    // 再生時間をセットする
    MV1SetAttachAnimTime(modelHandle, attachIndex, playTime);

    this->motionNum = motionNum;
    // ３Ｄモデルの０番目のアニメーションをアタッチする
    attachIndex = MV1AttachAnim(modelHandle, this->motionNum, -1, FALSE);
    // アタッチしたアニメーションの総再生時間を取得する
    totalTime = MV1GetAttachAnimTotalTime(modelHandle, attachIndex);
}

/// <summary>
/// モーション更新
/// </summary>
void Player::MotionUpdate()
{
   
    //downモーション時
    if (motionNum == down)
    {
        playTime++;

        //playTimeがtotalTimeを超えたらリセットする
        if (playTime >= totalTime)
        {
            playTime = 0;
            ChangeMotion(standUp);
        }
    }
    else
    {
        //モーションを1fずつ動かす
        playTime += 0.8f;
    }

    //止まるモーションの時モーション終了した場合待機モーションに変更
    if (motionNum == stop || motionNum == standUp)
    {
        if (playTime >= totalTime)
        {
            ChangeMotion(stand);
            isChangeMotion = false;
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
/// 座標の取得
/// </summary>
/// <param name="setPosition"></param>
void Player::GetPosition(VECTOR& setPosition)
{
    setPosition = VGet(position.x, position.y, position.z);
}