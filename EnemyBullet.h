#pragma once

class EnemyCircleAttack;
class Effect;

class EnemyBullet
{
private:
    VECTOR position;            //�G�̍��W
    VECTOR bulletSpeed;         //�e��
    VECTOR playerPos;           //�v���C���[�̍��W
    VECTOR futurePosition;      //�v���C���[�̖������W
    VECTOR effectPosition;      //�G�t�F�N�g�̃|�W
    VECTOR fellPosition;        //�������|�W�V����
    VECTOR velocity;         //���x
    int effectPlayStack;        //�G�t�F�N�g�Đ�����
    int positionStack;    //�ړ������
    bool isAttack;
    bool isEffect;          //�G�t�F�N�g���o����
    bool isEmerge;          //�o�������邩
    bool isCircleBullet;    //�T�[�N���U�������邩
    bool isSetUpMotion;     //�U�����[�V�����ɓ�������
    float bulletSpeed_Y;  
    float scale;
    Effect* effect = NULL;
    Effect* bulletColor = NULL;
    static constexpr float theta    = 30;               //����p�x�̏��
    static constexpr float speed    = 2.0f;             //���x
    static constexpr float radius   = 5.0f;             //���a
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
    // �Q�b�^�[
    ///////////////////////////////////
    VECTOR GetPosition() { return position; }
    VECTOR GetFellPosition() { return fellPosition; }
    bool GetIsEmerge() { return isEmerge; }
    bool GetIsAttack() { return isAttack; }
    float GetRadius(){ return radius;}
    
};

