#pragma once
#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include <vector>
#include "Calculation.h"
#include "Object.h"
#include "Input.h"
#include "Effect.h"


class Player
{
private:
    static constexpr float  radius      = 2;        //半径    
    static constexpr float  AttackSpeed = 0.55f;     //弾の速度
    static constexpr float	MoveSpeed   = 0.5f;	    // 移動速度
    static constexpr float  slowMoveSpeed = 0.3f;   //移動速度
    static constexpr float	JumpPower   = 1.5f;	    // ジャンプ力
    static constexpr float	Gravity     = 0.08f;	// 重力
    static constexpr float  AttackGravity = 0.15f;  //攻撃の重力
    static constexpr float	AngleSpeed  = 0.4f;	    // 角度変化速度
    static constexpr float  maxRange    = 33.0f;    //最大範囲
    static constexpr int objectNumber = 4;      //オブジェクトの数

    static constexpr int    down = 0;           //ダウンする
    static constexpr int    standUp = 1;        //立ち上がる
    static constexpr int    jump = 3;           //ジャンプ
    static constexpr int    stop = 12;           //止まる
    static constexpr int    stand = 2;          //待機
    static constexpr int    run = 9;           //歩く

    VECTOR position;
    VECTOR targetMoveDirection;	// モデルが向くべき方向のベクトル
    VECTOR objectPosition;
    VECTOR keepTargetMoveDirection;
    VECTOR effectPosition;
    VECTOR topSpherePosition;
    VECTOR bottomSpherePosition;
    VECTOR closePosition;          //プレイヤーと球の最も近い点
    VECTOR testPosition;
    VECTOR attackPosition;         //攻撃の球

    Effect* effect;
    Effect* attackEffect;

    int effectResourceHandle;
    int modelHandle;
    int attachIndex;            //再生中のモーション番号
    int motionNum;
    int stock;
    int attackEffectTime;
    int playingEffectHandle;
    int motionNumber;           //モーション番号
    int HpHandle;               

    float currentJumpPower;		// Ｙ軸方向の速度
    float totalTime;            //モーションの総再生時間
    float playTime;             //現在の再生時間
    float angle;					// モデルが向いている方向の角度
    float attackSpeedY;         //攻撃重力

    bool isMove;                    //動いたか
    bool isHitEnemyAttack;          //Enemyの攻撃に当たっているか
    bool isJump;                    //ジャンプしたか
    bool isOnGround;                //接地しているか
    bool isPushKey;                 //キーを押しているか
    bool isEffect;                  //エフェクトがでているか
    bool isHitObject[objectNumber];               //オブジェクトが当たっているか
    bool isObjectHitEnemy;          //攻撃がenemyに当たったか
    bool isChangeMotion;            //モーション変更するか
    bool isPlayTime;
    


public:

    Player();
    ~Player();

    void Initialize();                                       //初期化
    void Update(Calculation& calculation,                   //更新
        std::array<Object*, 4> object,
        const Input& input, Enemy& enemy);
    void Draw();
    void ChangeMotion(int motionNum);
    void UpdateAngle();
    void Attack(const Input& input);
    void AttackHitCheck(Enemy& enemy, Calculation& calculation);
    void Move(const Input& input, VECTOR& moveVec);
    void Jump(const Input& input, VECTOR& moveVec);
    void GetPosition(VECTOR& setPosition);
    void EnemyHitCheck(Enemy& enemy, Calculation& calculation);
    bool ObjectHitCheck(const VECTOR objectPosition,
        const float radius, Calculation& calculation);
    void Down();
    void MotionUpdate();
    void PickUpObject(Object& object, const Input& input);
  
    float GetMoveSpeed() { return MoveSpeed; }
    bool GetIsMove() { return isMove; }
    VECTOR GetPosition() { return position; }
    bool isLeftMove;
    bool isRightMove;
    bool isTopMove;
    bool isBottomMove;
};
