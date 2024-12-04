#pragma once
#include "EnemyBullet.h"
#include "EnemyCircleAttack.h"
#include"EnemyBreath.h"


class Enemy
{
public:
    Enemy();
    ~Enemy();

    void Initialize();
    void Update();
    void Draw();
    VECTOR GetBulletPosition() { return bulletPosition; }
    VECTOR GetTopPosition() { return topPosition; }
    VECTOR GetBottomPosition() { return bottomPosition; }
    
    void SetIsPlayerAttackHit(const bool value) { isPlayerAttackHit = value; }
    void ActionFlow(EnemyBullet& bullet, EnemyCircleAttack& circleAttack,
        EnemyBreath& breath);
    void GetPosition(VECTOR& setPosition);
    void SetPosition(const VECTOR& getPosition);
    void SetPlayerMoveSpeed(float moveSpeed);
    void SetIsPlayerMove(bool isMove);
    void SetIsPlayerMoveDirection(bool isTopMove, bool isBottomMove, bool isRightMove, bool isLeftMove);
    
    void AttackDesignation();
    void PlayerMovementPrediction();
    void Order(EnemyBullet& bullet, EnemyBreath& breath);
    //モーション関連
    void ChangeMotion(int numberNum);
    void MotionUpdate();

    //ゲッター
    int GetHP() { return HP; }
    float GetRadius() { return radius; }

    // インスタンス化
    EnemyBullet* bullet = new EnemyBullet();
    EnemyCircleAttack* circleAttack = new EnemyCircleAttack();
    EnemyBreath* breath = new EnemyBreath();
    
private:
    
    //モーション関連
    int modelHandle;                    //モデル
    int motionNum;
    int attachIndex;                    //再生中のモーション番号
    int orderNumber;                    //行動する順
    int bulletNumber;                   //現在の攻撃回数
    int maxBulletNumber;                //最大攻撃回数
    int HP;
    float totalTime;                    //モーションの総再生時間
    
    
    float standTime;                    //待機時間
    float playTime;                     //現在の再生時間
    float addPlayTime;
    bool isAttack;                      //攻撃するか
    bool isPlayerAttackHit;              //攻撃を当てられたか
    bool isKnockback;                   //のけぞったか
    bool isPlayerMove;                  //プレイヤーが動くか
    bool isLeftMove;                    //左に動いたか
    bool isRightMove;                   //右に動いたか
    bool isTopMove;                     //上に動いたか
    bool isBottomMove;                  //下に動いたか
    bool isBulletNumber;                //何回攻撃するか
    VECTOR topPosition;                    //Enemyのポジション
    VECTOR bottomPosition;           //球のポジション
    VECTOR AttackSpherePosition;        //攻撃のポジション
    VECTOR bulletSpeed;                 //弾の速度
    VECTOR bulletPosition;              //弾のポジション
    VECTOR bulletMotionPosition;        //弾攻撃時のモデルポジション
    VECTOR playerPos;                   //プレイヤーのポジション
    VECTOR futurePosition;              //未来のポジション
    float bulletPositionStack;          
    float radius;                       //球の半径
    float playerMoveSpeed;              //プレイヤーの速度
    float bulletSpeed_Y;                //弾の縦に動く速度

    static constexpr int knockback = 1;         //のけぞり
    static constexpr int jump = 4;              //ジャンプ  
    static constexpr int turn = 5;              //回る
    static constexpr int breathAttack = 6;      //ブレス
    static constexpr int bulletAttack = 7;      //弾攻撃
    static constexpr int stand = 16;             //待機
};

