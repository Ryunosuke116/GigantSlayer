#include "Include.h"

/// <summary>
/// インスタンス化
/// </summary>
Game::Game(SceneManager& manager) : BaseScene{ manager }
{
    if (player == NULL)
    {
        // インスタンス化
        input = new Input();
        effect = new Effect();
        player = new Player();
        camera = new Camera();
        map = new Map();
        calculation = new Calculation();
        enemyManager = new EnemyManager();
        for (auto& objects : object)
        {
            objects = new Object();
        }
        enemy = new Enemy();
        common = new Common("material/Shadow.tga");
        gameUI = new GameUI();
        objectManager = new ObjectManager();
        blackOut = new BlackOut();
        BGM = LoadSoundMem("material/BGM/maou_game_lastboss03.mp3");
        wind_SE = LoadSoundMem("material/SE/wind-artificial-18750.mp3");
        shine_SE = LoadSoundMem("material/SE/shine.mp3");
        ChangeVolumeSoundMem(255, wind_SE);
        ChangeVolumeSoundMem(125, BGM);
    }
}

/// <summary>
/// デストラクタ
/// </summary>
Game::~Game()
{
    delete(input);
    delete(player);
    delete(effect);
    delete(camera);
    delete(map);
    delete(calculation);
    delete(enemyManager);
    delete(enemy);
    delete(common);
    delete(gameUI);
    delete(objectManager);
    delete(blackOut);
    for (auto& objects : object)
    {
        delete(objects);
    }
    DeleteSoundMem(BGM);
    DeleteSoundMem(wind_SE);
    DeleteSoundMem(shine_SE);
}

/// <summary>
/// 初期化
/// </summary>
void Game::Initialize()
{
    map->Initialize();
    camera->Initialize();
    player->Initialize();
    enemy->Initialize();
    gameUI->Initialize(*enemy,*player);
    blackOut->Initialize();
    blackOut->SetAlpha(255);

    for (auto& objects : object)
    {
        (*objects).Initialize(*enemy);
    }
    alpha = 0;
    isPlayBGM = false;
    isPlaySE = false;
    isPlaySE_shine = false;
}

/// <summary>
/// 更新
/// </summary>
void Game::Update()
{
    //アップデート
    map->Update();
    input->Update();
    enemyManager->Update(*player, *enemy);

    for (auto& objects : object)
    {
        (*objects).Update(*enemy, *calculation, *input);
    }

    for (auto& bullet : enemy->bullet)
    {
       bullet->SetIsEmerge(false);
    }

    if (!camera->GetIsChange())
    {
        if (!isPlaySE)
        {
            PlaySoundMem(wind_SE, DX_PLAYTYPE_BACK);
            isPlaySE = true;
        }
        enemy->StartUpdate();
        player->StartUpdate();
        camera->StartUpdate(*enemy);
    }
    else
    {
        if (!isPlayBGM)
        {
            StopSoundMem(wind_SE);
            PlaySoundMem(BGM, DX_PLAYTYPE_LOOP);    
            isPlayBGM = true;
        }
        enemy->Update(*calculation);
        player->Update(*calculation, object, *input, *enemy);
        camera->Update(player->GetPosition(), enemy->GetTopPosition());
    }

    objectManager->Update(object, *player,*calculation);
    gameUI->Update(*enemy,*player, camera->GetIsChange());
    common->Update(*player, object);
    effect->PlayEffectUpdate();

    blackOut->LightChangeUpdate(4.5f);
    SceneChanger(*player, *enemy, *camera, *gameUI);
}

/// <summary>
/// 描画
/// </summary>
void Game::Draw()
{

    //描画
    clsDx();
    map->Draw();
    for (int i = 0; i < objectNumber; i++)
    {
        object[i]->Draw();
    }
    enemy->Draw();
    player->Draw(*map);
    camera->Draw();
    effect->Draw();
    common->Draw(*map,player->GetPosition(),*enemy);
    gameUI->Draw();
    blackOut->Draw();
    clsDx();

    //箱の描画
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawBox(0, 0, 1600, 900, GetColor(255, 255, 255), TRUE); 
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void Game::SceneChanger(Player& player, Enemy& enemy, Camera& camera, GameUI& gameUI)
{
    if (enemy.GetHP() <= 0)
    {
        if (!isPlaySE_shine)
        {
            PlaySoundMem(shine_SE, DX_PLAYTYPE_BACK);
            isPlaySE_shine = true;
        }
        camera.EndUpdate(enemy.GetTopPosition());
        if (camera.GetTime() >= 240)
        {
            StopSoundMem(BGM);
            alpha += 2;
            if (alpha >= 350)
            {
                ChangeScene("GameClear");
            }
        }
    }

    if (gameUI.GetAlpha_bright() >= 500)
    {
        StopSoundMem(BGM);
        ChangeScene("GameOver");
    }

}