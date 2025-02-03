#pragma once



class Game : public BaseScene
{
public:

    Game(SceneManager& manager);
    ~Game();

    void Initialize();
    void Update();
    void Draw();
    void SceneChanger(Player& player, Enemy& enemy, Camera& camera,GameUI& gameUI);
private:
    static constexpr int objectNumber = 4;      //�I�u�W�F�N�g�̐�
    int alpha;
    //��`
    Input* input = NULL;
    Effect* effect = NULL;
    Player* player = NULL;
    Camera* camera = NULL;
    Map* map = NULL;
    Calculation* calculation = NULL;
    EnemyManager* enemyManager = NULL;
    std::array<Object*, objectNumber> object = {
       NULL,
       NULL,
       NULL,
       NULL
    };
    Enemy* enemy = NULL;
    Common* common = NULL;
    GameUI* gameUI = NULL;
    ObjectManager* objectManager = NULL;
    BlackOut* blackOut = NULL;
};

