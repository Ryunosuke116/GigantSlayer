#pragma once


class Object;

class ObjectManager
{
public:
    void Update(std::array<Object*, 4> object,Player& player, Calculation& calculation);
    bool Comparison(std::array<Object*, 4> object);
    void HoldObject(Object& object, VECTOR playerPosition, VECTOR angle);
    void LetGoObject(std::array<Object*, 4> object,Calculation& calculation);
    void LeanBackObject(std::array<Object*, 4> object, Player& player);
private:

    static constexpr float  backSpeed = 0.65f;     //�e�̑��x
    static constexpr float	JumpPower = 0.75f;	    // �W�����v��
    static constexpr float	Gravity = 0.08f;	// �d��


};

