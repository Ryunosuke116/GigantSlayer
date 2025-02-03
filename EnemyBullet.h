#pragma once

class EnemyCircleAttack;
class Effect;

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
    bool isEffect;          //エフェクトを出すか
    bool isEmerge;          //出現させるか
    bool isCircleBullet;    //サークル攻撃をするか
    bool isSetUpMotion;     //攻撃モーションに入ったか
    float bulletSpeed_Y;  
    float scale;
    Effect* effect = NULL;
    Effect* bulletColor = NULL;
    static constexpr float theta    = 30;               //旋回角度の上限
    static constexpr float speed    = 2.0f;             //速度
    static constexpr float radius   = 5.0f;             //半径
    static constexpr float circleAttackBulletSpeed = 0.2f;

    static constexpr int maxPositionStack = 65;

public:

    EnemyBullet();
    ~EnemyBullet();

    void Initialize(const VECTOR EnemyPosition);
    void Update(const VECTOR EnemyPosition, 
        EnemyCircleAttack& circleAttack);
    void Draw();
    void Move(const VECTOR EnemyPosition,EnemyCircleAttack& circleAttack);
    void ResetAttack(const VECTOR& enemyPosition);
    void BulletMove();
    void AttackDesignation(const VECTOR EnemyPosition);
  
    void SetPlayerPosition(VECTOR& getPosition);
    void SetPosition(VECTOR& getPosition);
    void SwitchingIsCircleBullet();
    void SetIsEmerge(const bool value) { isEmerge = value; }
    void SetIsCircleBullet(const bool value) { isCircleBullet = value; }
    void SetIsAttack(const bool value) { isAttack = value; }
    void SetIsSetUpMotion(const bool value) { isSetUpMotion = value; }

    ////////////////////////////////////
    // ゲッター
    ///////////////////////////////////
    VECTOR GetPosition() { return position; }
    VECTOR GetFellPosition() { return fellPosition; }
    bool GetIsEmerge() { return isEmerge; }
    bool GetIsAttack() { return isAttack; }
    float GetRadius(){ return radius;}
    
};

