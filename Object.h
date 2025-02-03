#pragma once

class Enemy;
class Calculation;
class Input;
class Effect;

class Object
{
private:
    VECTOR position;
    VECTOR addPosition;
    VECTOR subPosition;
    VECTOR keepTargetMoveDirection;
    float radius;
    float attackSpeedY;         //攻撃重力
    float DropSpeed;
    int attackEffectTime;
    int time;
    int graphHandle;
    bool isHitPlayer;
    bool isHit;
    bool isGetPosition;
    bool isObject;      //出現中かどうか
    bool isHitBreath;   //ブレスに当たったか
    bool isCanCatch;    //つかめるか
    bool isReset;
    bool isPlayerHold;  //プレイヤーが持っているか
    bool isThrow;
    bool isPushKey;
    bool isObjectHitEnemy;
    bool isDrop;            //落としたか
    bool isLeanBack;
    Effect* effect;
    Effect* attackEffect;

    static constexpr float speed = 3.0f;        //速さ
    static constexpr int objectNumber = 4;      //オブジェクトの数
    static constexpr float  AttackSpeed = 0.75f;     //弾の速度
    static constexpr float	JumpPower = 1.5f;	    // ジャンプ力
    static constexpr float	Gravity = 0.08f;	// 重力

    static constexpr float  backSpeed = 0.65f;     //弾の速度
    static constexpr float	GravityPower = 0.75f;	    // ジャンプ力

public:

    Object();
    ~Object();

    void Initialize(Enemy& enemy);
    void Update(Enemy& enemy, Calculation& calculation, const Input& input);
    void Draw();
    void Reset(Enemy& enemy);
    void Throw(Enemy& enemy);
    void AttackHitCheck(Enemy& enemy, Calculation& calculation);
    float DirectionCalculation(const VECTOR comparisonPosition);
    void AddPositionCalculation(const VECTOR comparisonPosition);
    void LetGoCalculation(const VECTOR objectPosition);
    void LeanBackObject();

    ///////////////////////////////////////////
    // ゲッター
    ///////////////////////////////////////////
    VECTOR GetPosition() { return position; }
    VECTOR GetKeepTargetMoveDirection() { return keepTargetMoveDirection; }
    float GetRadius() { return radius; }
    bool GetIsThrow() { return isThrow; }
    bool GetIsPlayerHold() { return isPlayerHold; }
    bool GetIsObject() { return isObject; }
    bool GetIsCanCatch() { return isCanCatch; }
    bool GetIsHitPlayer() { return isHitPlayer; }
    bool GetIsDrop() { return isDrop; }
    bool GetIsLeanBack() { return isLeanBack; }

    /////////////////////////
    // セッター
    /////////////////////////
    void SetPlayerIsHit(const bool& isHit) { isHitPlayer = isHit; }
    void SetIsCanCatch(const bool& value) { isCanCatch = value; }
    void SetIsThrow(bool flg) { isThrow = flg; }
    void SetAngle(VECTOR newAngle) { keepTargetMoveDirection = newAngle; }
    void SetPosition(VECTOR newPosition) { position = newPosition; }
    void SetIsReset(bool flg) { isReset = flg; }
    void SetisPlayerHold(bool flg) { isPlayerHold = flg; }
    void SetIsDrop(bool flg) { isDrop = flg; }
    void SetIsLeanBack(bool flg) { isLeanBack = flg; }
};

