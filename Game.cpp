#include "Game.h"
#include <iostream>
#include <array>

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
        common = new Common();
        gameUI = new GameUI();
        objectManager = new ObjectManager();
        blackOut = new BlackOut();
    }
}

/// <summary>
/// デストラクタ
/// </summary>
Game::~Game()
{
    delete(input);
    delete(player);
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

    enemy->bullet->SetIsEmerge(false);

    if (!camera->GetIsChange())
    {
        enemy->StartUpdate();
        player->StartUpdate();
        camera->StartUpdate(*enemy);
    }
    else
    {
        enemy->Update();
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
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawBox(0, 0, 1600, 900, GetColor(255, 255, 255), TRUE); //箱の描画
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    clsDx();

}

void Game::SceneChanger(Player& player, Enemy& enemy, Camera& camera, GameUI& gameUI)
{
    if (enemy.GetHP() <= 0)
    {
        camera.EndUpdate(enemy.GetTopPosition());
        if (camera.GetTime() >= 240)
        {
            alpha += 2;
            if (alpha >= 350)
            {
                ChangeScene("Result");
            }
        }
    }
    else
    {
      
    }

    if (gameUI.GetAlpha_bright() >= 500)
    {
        ChangeScene("Result");
    }

}