#pragma once
#include "Effect.h"
#include "EnemyCircleAttack.h"
class EnemyBullet
{
private:
    VECTOR position;            //敵の座標
    VECTOR bulletSpeed;         //弾速
    VECTOR playerPos;           //プレイヤーの座標
    VECTOR futurePosition;      //プレイヤーの未来座標
    VECTOR effectPosition;      //エフェクトのポジ
    VECTOR fellPosition;        //落ちたポジション
    VECTOR velocity;         //速度
    int effectPlayStack;        //エフェクト再生時間
    int positionStack;    //移動する量
    bool isAttack;
    bool isPlayerMove;
    bool isLeftMove;
    bool isRightMove;
    bool isTopMove;
    bool isBottomMove;
    bool isEffect;          //エフェクトを出すか
    bool isEmerge;          //出現させるか
    bool isCircleBullet;    //サークル攻撃をするか
    bool isSetUpMotion;     //攻撃モーションに入ったか
    float playerMoveSpeed;
    float bulletSpeed_Y;  
    float scale;
    Effect* effect;
    Effect* bulletColor;
    static constexpr float theta    = 30;               //旋回角度の上限
    static constexpr float speed    = 4.0f;             //速度
    static constexpr float radius   = 5.0f;             //半径
    static constexpr float circleAttackBulletSpeed = 0.5f;

    static constexpr int maxPositionStack = 50;

public:

    EnemyBullet();
    ~EnemyBullet();

    void Initialize(const VECTOR EnemyPosition);
    void Update(const VECTOR EnemyPosition, 
        EnemyCircleAttack& circleAttack);
    void Draw();
    void Move(const VECTOR EnemyPosition,EnemyCircleAttack& circleAttack);
    void BulletMove();
    void AttackDesignation(const VECTOR EnemyPosition);
    void SetPlayerMoveSpeed(float moveSpeed);
    void PlayerMovementPrediction();
    void SetIsPlayerMove(bool isMove);
    void SetIsPlayerMoveDirection(bool isTopMove, bool isBottomMove, bool isRightMove, bool isLeftMove);
    void SetPlayerPosition(VECTOR& getPosition);
    void SetPosition(VECTOR& getPosition);
    void SwitchingIsCircleBullet();
    VECTOR GetPosition() { return position; }
    VECTOR GetFellPosition() { return fellPosition; }
    bool GetIsEmerge() { return isEmerge; }
    float GetRadius(){ return radius;}
    void SetIsEmerge(const bool value) { isEmerge = value; }
    void SetIsCircleBullet(const bool value) { isCircleBullet = value; }
    void SetIsAttack(const bool value) { isAttack = value; }
    void SetIsSetUpMotion(const bool value) { isSetUpMotion = value; }
};

