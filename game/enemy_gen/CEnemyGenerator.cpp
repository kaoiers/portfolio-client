//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/10/02
//
// File Name : CEnemyGenerator.cpp
//
// 적군 생성기
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include <time.h>
#include "CEnemyGenerator.h"
#include "../objects/CGameObjectManager.h"
#include "../objects/CGameRoomGod.h"
#include "../objects/CGameUnitEnemy.h"
#include "../interfaces/CMainGameGUI.h"
#include "../map/CGameMap.h"

/*======================================================*/
// 초기화
/*======================================================*/
void CEnemyGenerator::initialize()
{
}

/*======================================================*/
// 적군 생성하기
/*======================================================*/
CGameUnitEnemy* CEnemyGenerator::generateEnemy()
{
    s32 distance_offset = s32(m_enemy_generate_line.getLength());

    distance_offset = rand() % distance_offset;

    vector3df generate_pos = m_enemy_generate_line.start +
    (vector3df(1, 0, 0) * f32(distance_offset));

    generate_pos.Y = 0.0f;

    CGameUnitEnemy* p_enemy = m_game_map->getObjectManager()->addUnitEnemy(generate_pos, this);

    vector3df v_destination = vector3df(0, 0,
        m_game_map->getTopLeftUsablePos().Z);

    p_enemy->addGoalMoveToPosition(v_destination);

    m_enemy = p_enemy;

    return nullptr;
}

CEnemyGenerator::CEnemyGenerator(CGameMap * p_map, const u32 enemy_generate_period, const u32 enemy_appear_period, const u32 enemy_max_counts)
    : m_game_map(p_map)
{
    srand((s32)time(nullptr));

    vector3df tl = m_game_map->getTopLeftUsablePos();
    vector3df br = m_game_map->getBottomRightUsablePos();

    m_enemy_generate_line.start = vector3df(tl.X, 0.0f, br.Z);
    m_enemy_generate_line.end = vector3df(br.X, 0.0f, br.Z);
}

CEnemyGenerator::~CEnemyGenerator()
{
}

/*======================================================*/
// 적군 생성 중인지
/*======================================================*/
bool CEnemyGenerator::isInGenerate()
{
    return (!m_complete_wave);
}

/*======================================================*/
// 적군 죽음 추가
/*======================================================*/
void CEnemyGenerator::addDeadCount()
{
    m_dead_enemies--;

    if (m_dead_enemies == 0)
    {
        m_complete_wave = true;
    }
}
