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
    //���[�V�����֘A
    void ChangeMotion(int numberNum);
    void MotionUpdate();

    //////////////////////////////////////
    // �Q�b�^�[
    //////////////////////////////////////
    int GetHP() { return HP; }
    float GetRadius() { return radius; }
    VECTOR GetBulletPosition() { return bulletPosition; }
    VECTOR GetTopPosition() { return topPosition; }
    VECTOR GetBottomPosition() const { return bottomPosition; }

    //////////////////////////////////////////
    // �Z�b�^�[
    //////////////////////////////////////////
    void SetPosition(const VECTOR& getPosition) { playerPos = getPosition; }  

    
    EnemyBullet* bullet[2] = { NULL };
    EnemyCircleAttack* circleAttack = NULL;
    EnemyBreath* breath = NULL;
    
private:
    
    //���[�V�����֘A
    int modelHandle;                    //���f��
    int motionNum;
    int attachIndex;                    //�Đ����̃��[�V�����ԍ�
    int orderNumber;                    //�s�����鏇
    int bulletNumber;                   //���݂̍U����
    int maxBulletNumber;                //�ő�U����
    int HP;
    int voiceHandle;
    
    float angle;
    float totalTime;                    //���[�V�����̑��Đ�����
    float standTime_now;                    //�ҋ@����
    float playTime;                     //���݂̍Đ�����
    float addPlayTime;                    
    bool isAttack;                      //�U�����邩
    bool isPlayerAttackHit;              //�U���𓖂Ă�ꂽ��
    bool isKnockback;                   //�̂���������
    bool isBulletNumber;                //����U�����邩
    bool isBootBullet;
    bool isAnger;       
    VECTOR topPosition;                    //Enemy�̃|�W�V����
    VECTOR bottomPosition;           //���̃|�W�V����
    VECTOR AttackSpherePosition;        //�U���̃|�W�V����
    VECTOR bulletSpeed;                 //�e�̑��x
    VECTOR bulletPosition;              //�e�̃|�W�V����
    VECTOR bulletMotionPosition;        //�e�U�����̃��f���|�W�V����
    VECTOR playerPos;                   //�v���C���[�̃|�W�V����      
    VECTOR direction;                   //����

    static constexpr int knockback = 1;         //�̂�����
    static constexpr int jump = 4;              //�W�����v  
    static constexpr int turn = 5;              //���
    static constexpr int breathAttack = 6;      //�u���X
    static constexpr int bulletAttack = 7;      //�e�U��
    static constexpr int stand = 16;             //�ҋ@
    static constexpr float radius = 25;   //���̔��a
    static constexpr float standTime = 50.0f;
    static constexpr float standTime_anger = 30.0f;
};

