#include "Game.h"
#include <iostream>
#include <array>

/// <summary>
/// インスタンス化
/// </summary>
Game::Game(SceneManager& manager) : BaseScene{ manager }
{
    // インスタンス化
    input = new Input();
    effect = new Effect();
    player = new Player();
    camera = new Camera();
    map = new Map();
    calculation = new Calculation();
    bulletCalculation = new BulletCalculation();
    for (auto& objects : object)
    {
        objects = new Object();
    }
    enemy = new Enemy();
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

    for (auto& objects : object)
    {
        (*objects).Initialize(*enemy);
    }
}

/// <summary>
/// 更新
/// </summary>
void Game::Update()
{
    //アップデート
    input->Update();
    camera->Update(player->GetPosition(), enemy->GetTopPosition());
    bulletCalculation->Update(*player, *enemy);
    enemy->Update();
    for (auto& objects : object)
    {
        (*objects).Update(*enemy, *calculation, *input);
    }
    enemy->bullet->SetIsEmerge(false);
    player->Update(*calculation, object, *input, *enemy);

    effect->PlayEffectUpdate();

    if (CheckHitKey(KEY_INPUT_LSHIFT))
    {
        ChangeScene("Title");
    }
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
    player->Draw();
    camera->Draw();
    effect->Draw();
}