#pragma once

class EnemyBullet;
class EnemyCircleAttack;
class EnemyBreath;

class Enemy
{
public:
    Enemy();
    ~Enemy();

    void Initialize();
    void Update(Calculation& calculation);
    void Draw();
    
    void UpdateDirection();
    void SetIsPlayerAttackHit(const bool value) { isPlayerAttackHit = value; }
    void ActionFlow(EnemyBullet bullet[], EnemyCircleAttack& circleAttack,
        EnemyBreath& breath, Calculation& calculation);
    void StartUpdate();
    void ResetTime(){ standTime_now = 0; }
    
    void AttackDesignation();
    void PlayerMovementPrediction();
    void Order(EnemyBullet& bullet, EnemyBreath& breath);
    //モーション関連
    void ChangeMotion(int numberNum);
    void MotionUpdate();

    //////////////////////////////////////
    // ゲッター
    //////////////////////////////////////
    int GetHP() { return HP; }
    float GetRadius() { return radius; }
    VECTOR GetBulletPosition() { return bulletPosition; }
    VECTOR GetTopPosition() { return topPosition; }
    VECTOR GetBottomPosition() const { return bottomPosition; }

    //////////////////////////////////////////
    // セッター
    //////////////////////////////////////////
    void SetPosition(const VECTOR& getPosition) { playerPos = getPosition; }  

    
    EnemyBullet* bullet[2] = { NULL };
    EnemyCircleAttack* circleAttack = NULL;
    EnemyBreath* breath = NULL;
    
private:
    
    //モーション関連
    int modelHandle;                    //モデル
    int motionNum;
    int attachIndex;                    //再生中のモーション番号
    int orderNumber;                    //行動する順
    int bulletNumber;                   //現在の攻撃回数
    int maxBulletNumber;                //最大攻撃回数
    int HP;
    int voiceHandle;
    
    float angle;
    float totalTime;                    //モーションの総再生時間
    float standTime_now;                    //待機時間
    float playTime;                     //現在の再生時間
    float addPlayTime;                    
    bool isAttack;                      //攻撃するか
    bool isPlayerAttackHit;              //攻撃を当てられたか
    bool isKnockback;                   //のけぞったか
    bool isBulletNumber;                //何回攻撃するか
    bool isBootBullet;
    bool isAnger;       
    VECTOR topPosition;                    //Enemyのポジション
    VECTOR bottomPosition;           //球のポジション
    VECTOR AttackSpherePosition;        //攻撃のポジション
    VECTOR bulletSpeed;                 //弾の速度
    VECTOR bulletPosition;              //弾のポジション
    VECTOR bulletMotionPosition;        //弾攻撃時のモデルポジション
    VECTOR playerPos;                   //プレイヤーのポジション      
    VECTOR direction;                   //方向

    static constexpr int knockback = 1;         //のけぞり
    static constexpr int jump = 4;              //ジャンプ  
    static constexpr int turn = 5;              //回る
    static constexpr int breathAttack = 6;      //ブレス
    static constexpr int bulletAttack = 7;      //弾攻撃
    static constexpr int stand = 16;             //待機
    static constexpr float radius = 25;   //球の半径
    static constexpr float standTime = 50.0f;
    static constexpr float standTime_anger = 30.0f;
};

