//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/06/14
//
// File Name : SObjectResources.h
//
// 오브젝트 데이터 관련
//
//////////////////////////////////////////////////////////////////////////

#ifndef OBJECT_RESORUCE_DEFINE
#define OBJECT_RESOURCE_DEFINE

#include "../common/UncopyableUtil.h"

struct CAnimation_Info;
#include <vector>
#include <list>

/// 오브젝트에 연결되는 공통 애니메이션 자원 정보를 표현한다.
struct BASIC_OBJECT_RESOURCE
{
    std::vector<CAnimation_Info *> m_animations;
};

/// 건물 크기, 출입구, 건설 시간 및 필요 자원 정보를 표현한다.
struct ROOM_RESOURCE : BASIC_OBJECT_RESOURCE
{
    u32 m_width_cells;
    u32 m_height_cells;
    vector3di door_vector;
    f32 m_building_time;
    s16 need_gold;
    s16 need_stone;
    s16 need_wood;
};

/// 유닛의 이동, 공격 및 무기 관련 자원 설정을 표현한다.
struct UNIT_RESOURCE : BASIC_OBJECT_RESOURCE
{
    f32 m_max_speed;
    f32 m_normal_speed;
    f32 m_mass;
    f32 m_turn_rate;
    f32 m_max_force;
    f32 m_hit_range;
    u32 m_attack_frm1;
    u32 m_attack_frm2;
    f32 m_radius;
    vector3df m_weapon_pos;
    vector3df m_weapon_scale;
    u32 m_weapon_joint_number;
    u32 m_production_time;
};

#endif
