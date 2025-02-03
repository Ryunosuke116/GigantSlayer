#pragma once

class Object;
class Enemy;
class Calculation;
class Effect;
class Input;
class Map;

class Player
{
private:
    static constexpr float  radius      = 2;        //半径    
    static constexpr float  AttackSpeed = 0.65f;     //弾の速度
    static constexpr float	MoveSpeed   = 0.4f;	    // 移動速度
    static constexpr float  slowMoveSpeed = 0.3f;   //移動速度
    static constexpr float	JumpPower   = 1.1f;	    // ジャンプ力
    static constexpr float	Gravity     = 0.06f;	// 重力
    static constexpr float  AttackGravity = 0.15f;  //攻撃の重力
    static constexpr float	AngleSpeed  = 0.2f;	    // 角度変化速度
    static constexpr float  maxRange    = 33.0f;    //最大範囲
    static constexpr float	ShadowSize = 3.0f;	// 影の大きさ
    static constexpr float	ShadowHeight = 10.0f;	// 影が落ちる高さ
    static constexpr int objectNumber = 4;      //オブジェクトの数

    static constexpr int    die = 0;            //倒れる
    static constexpr int    down = 7;           //ダウンする
    static constexpr int    standUp = 16;        //立ち上がる
    static constexpr int    stand = 14;          //待機
    static constexpr int    run = 12;           //歩く
    static constexpr int    jump = 8;           //ジャンプ
    static constexpr int    stop = 17;           //止まる
    static constexpr int    pickUp = 10;         //拾う

    static constexpr int    stand_Hold = 15;
    static constexpr int    run_Hold = 13;
    static constexpr int    jump_Hold = 9;
    static constexpr int    stop_Hold = 18;
    static constexpr int    pickUp_Hold = 11;

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

    int shadowHandle;
    int effectResourceHandle;
    int modelHandle;
    int attachIndex;            //再生中のモーション番号
    int motionNum;
    int stock;
    int attackEffectTime;
    int playingEffectHandle;
    int motionNumber;           //モーション番号
    int HpHandle;      
    int HP;

    float currentJumpPower;		// Ｙ軸方向の速度
    float totalTime;            //モーションの総再生時間
    float playTime;             //現在の再生時間
    float angle;					// モデルが向いている方向の角度
    float attackSpeedY;         //攻撃重力
    float invincibleTime;       //無敵時間

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
    bool isAttackHold;              //攻撃を保持しているか
    bool isInvincible;              //無敵か
    bool isDisplay;                 //表示するか


public:

    Player();
    ~Player();

    void Initialize();                                       //初期化
    void Update(Calculation& calculation,                   //更新
        std::array<Object*, 4> object,
        const Input& input, Enemy& enemy);
    void StartUpdate();
    void Draw(const Map& map);
    void UpdateAngle();
    void Attack(const Input& input);
    void AttackHitCheck(Enemy& enemy, Calculation& calculation);
    void Move(const Input& input, VECTOR& moveVec);
    void Jump(const Input& input, VECTOR& moveVec);

    void EnemyHitCheck(Enemy& enemy, Calculation& calculation);
    bool ObjectHitCheck(const VECTOR objectPosition,
        const float radius, Calculation& calculation);
    void Down();
    void PickUpObject(Object& object, const Input& input);
    ///////////////////////////////////////////////
    //モーション関連
    ///////////////////////////////////////////////
    void MotionUpdate();
    void ChangeMotion(int motionNum);
    void Motion_HoldorUnHold(int motionNum,int holdMotionNum);

    ////////////////////////////////////////////////
    // ゲッター
    ///////////////////////////////////////////////
    int GetHP() { return HP; }
    int GetMotionNum() { return motionNum; }
    float GetMoveSpeed() { return MoveSpeed; }
    bool GetIsMove() { return isMove; }
    bool GetIsPushKey() { return isPushKey; }
    VECTOR GetTargetMoveDirection_Norm() { return VNorm(targetMoveDirection); }
    VECTOR GetPosition() const { return position; }
    VECTOR GetTopPosition()const { return topSpherePosition; }

    //-------------------------------------------//
    // セッター
    //-------------------------------------------//
    void SetPosition(VECTOR newPosition) { position = newPosition; }
    void SetIsPushKey(bool newIsPushKey) { isPushKey = newIsPushKey; }

};
