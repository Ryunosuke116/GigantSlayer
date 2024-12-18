#include "Game.h"
#include <iostream>
#include <array>

/// <summary>
/// �C���X�^���X��
/// </summary>
Game::Game(SceneManager& manager) : BaseScene{ manager }
{
    if (player == NULL)
    {
        // �C���X�^���X��
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
    }
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Game::~Game()
{
    delete(input);
    delete(player);
}

/// <summary>
/// ������
/// </summary>
void Game::Initialize()
{
    map->Initialize();
    camera->Initialize();
    player->Initialize();
    enemy->Initialize();
    gameUI->Initialize(*enemy);

    for (auto& objects : object)
    {
        (*objects).Initialize(*enemy);
    }
    alpha = 0;
}

/// <summary>
/// �X�V
/// </summary>
void Game::Update()
{
    //�A�b�v�f�[�g
    map->Update();
    input->Update();
    enemyManager->Update(*player, *enemy);
    enemy->Update();
    for (auto& objects : object)
    {
        (*objects).Update(*enemy, *calculation, *input);
    }
    enemy->bullet->SetIsEmerge(false);
    player->Update(*calculation, object, *input, *enemy);
    effect->PlayEffectUpdate();
    gameUI->Update(*enemy);
    common->Update(*player, object);

    if (enemy->GetHP() <= 0)
    {
        camera->EndUpdate(enemy->GetTopPosition());
        if (camera->GetTime() >= 240)
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
        if (!camera->GetIsChange())
        {
            camera->StartUpdate();
        }
        else
        {
            camera->Update(player->GetPosition(), enemy->GetTopPosition());
        }
    }
}

/// <summary>
/// �`��
/// </summary>
void Game::Draw()
{
    //�`��
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
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawBox(0, 0, 1600, 900, GetColor(255, 255, 255), TRUE); //���̕`��
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}