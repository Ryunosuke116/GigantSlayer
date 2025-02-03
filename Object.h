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
    float attackSpeedY;         //�U���d��
    float DropSpeed;
    int attackEffectTime;
    int time;
    int graphHandle;
    bool isHitPlayer;
    bool isHit;
    bool isGetPosition;
    bool isObject;      //�o�������ǂ���
    bool isHitBreath;   //�u���X�ɓ���������
    bool isCanCatch;    //���߂邩
    bool isReset;
    bool isPlayerHold;  //�v���C���[�������Ă��邩
    bool isThrow;
    bool isPushKey;
    bool isObjectHitEnemy;
    bool isDrop;            //���Ƃ�����
    bool isLeanBack;
    Effect* effect;
    Effect* attackEffect;

    static constexpr float speed = 3.0f;        //����
    static constexpr int objectNumber = 4;      //�I�u�W�F�N�g�̐�
    static constexpr float  AttackSpeed = 0.75f;     //�e�̑��x
    static constexpr float	JumpPower = 1.5f;	    // �W�����v��
    static constexpr float	Gravity = 0.08f;	// �d��

    static constexpr float  backSpeed = 0.65f;     //�e�̑��x
    static constexpr float	GravityPower = 0.75f;	    // �W�����v��

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
    // �Q�b�^�[
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
    // �Z�b�^�[
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

