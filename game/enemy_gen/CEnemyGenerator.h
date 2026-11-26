//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/10/02
//
// File Name : CEnemyGenerator.h
//
// 적군 생성기
//
//////////////////////////////////////////////////////////////////////////

#ifndef ENEMY_GENERATOR_H
#define ENEMY_GENERATOR_H

class CGameMap;
class CGameUnitEnemy;

class CEnemyGenerator
{
    u32 m_enemy_generate_period;
    u32 m_enemy_appear_period;
    line3df m_enemy_generate_line;
    CGameMap* m_game_map;
    u32 m_next_appear_time;
    u32 m_next_generate_time;
    bool m_generate_flag;
    bool m_start_flag;

    u32 m_enemy_max_counts;
    u32 m_current_enemy_max_counts;
    u32 m_dead_enemies;
    CGameUnitEnemy* m_enemy;
    bool m_on_wave;
    bool m_complete_wave;

    void initialize();
    CGameUnitEnemy* generateEnemy();

public:
    CEnemyGenerator(CGameMap* p_map, const u32 enemy_generate_period,
        const u32 enemy_appear_period, const u32 enemy_max_counts);

    ~CEnemyGenerator();

    void addDeadCount();

    const line3df& getEnemyGenerateLine() { return m_enemy_generate_line; }

    void setStartWave() {};

    bool isInGenerate();
};

#endif
