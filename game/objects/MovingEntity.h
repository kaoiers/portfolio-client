//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/02/09
//
// File Name : MovingEntity.h
//
// 움직이는 개체용 클래스
//
//////////////////////////////////////////////////////////////////////////

#ifndef MOVING_ENTITY
#define MOVING_ENTITY

#include <cassert>
#include "CGameObject.h"

enum { clockwise = 1, anticlockwise = -1 };

class MovingEntity :public CGameObject
{
#define Node getSceneNode()

protected:
    vector3df m_velocity;

    f32 m_movement_mass;

    f32 m_movement_max_speed;

    f32 m_movement_max_force;

    f32 m_max_turn_rate;

    f32 m_bounding_radius;

    f32 m_movement_normal_speed;

    u32 m_last_updated_time;

public:
    MovingEntity(OwnerType owner, s32 objtype,
        f32 max_speed,
        f32 mass,
        f32 turn_rate,
        f32 max_force,
        f32 nspeed,
        const vector3df& pos,
        const vector3df& rot,
        const vector3df& scale)
        :CGameObject(owner, objtype, pos, rot, scale),
    m_movement_mass(mass),
    m_movement_max_speed(max_speed),
    m_max_turn_rate(turn_rate),
    m_movement_max_force(max_force),
    m_movement_normal_speed(nspeed),
    m_last_updated_time(0)
    {
    }

    MovingEntity(OwnerType owner, u32 obj_id,
        s32 objtype,
        f32 max_speed,
        f32 mass,
        f32 turn_rate,
        f32 max_force,
        f32 nspeed,
        const vector3df& pos,
        const vector3df& rot,
        const vector3df& scale)
        :CGameObject(owner, obj_id, objtype, pos, rot, scale),
    m_movement_mass(mass),
    m_movement_max_speed(max_speed),
    m_max_turn_rate(turn_rate),
    m_movement_max_force(max_force),
    m_movement_normal_speed(nspeed),
    m_last_updated_time(0)
    {
    }

    virtual ~MovingEntity() {};

    virtual void control() {}

    virtual void render() {};

    virtual void onCommand() {};

    virtual void update(u32 time_ms) {};

    //accessors
    vector3df getVelocity() const { return m_velocity; }
    void setVelocity(const vector3df& new_vel) { m_velocity = new_vel; }

    f32 getMass() const { return m_movement_mass; }

    vector3df getPos() { return vector3df(0, 0, 0); }
    void setPos(vector3df& pos) { }

    f32 getNormalSpeed() const { return m_movement_normal_speed; }

    vector3df getSide();

    f32 maxSpeed() const { return m_movement_max_speed; }
    void setMaxSpeed(f32 new_speed) { m_movement_max_speed = new_speed; }

    f32 maxForce() const { return m_movement_max_force; }
    void setMaxForce(f32 mf) { m_movement_max_force = mf; }

    bool isSpeedMaxedOut() const { return m_movement_max_speed*m_movement_max_speed >= m_velocity.getLength(); }
    f32 getSpeed() const { return m_velocity.getLength(); }
    f32 getSpeedSq() const { return m_velocity.getLength(); }

    vector3df getHeading();
    void setHeading(const vector3df& new_heading);
    bool rotateHeadingToFacePosition(vector3df target);

    f32 getMaxTurnRate() const { return m_max_turn_rate; }
    void setMaxTurnRate(f32 val) { m_max_turn_rate = val; }

    inline double calculateTimeToReachPosition(vector3df& pos);
    inline bool isAtPosition(const vector3df& pos);
};

/*======================================================*/
// 전방을 목표방향으로 돌리기
/*======================================================*/
inline bool MovingEntity::rotateHeadingToFacePosition(vector3df target)
{
    return false;
}

/*======================================================*/
// 전방을 목표방향으로 바꾸기
/*======================================================*/
inline void MovingEntity::setHeading(const vector3df& new_heading)
{
    vector3df offset = new_heading;// - Pos();

    offset.normalize();

    vector3df node_rotation = offset;

    node_rotation.X = 0.0f;

    //the side vector must always be perpendicular to the heading
}

/*======================================================*/
// 전방 벡터 가져오기
/*======================================================*/
inline vector3df MovingEntity::getHeading()
{
    vector3df heading(0, 0, 0);

    heading.normalize();

    return heading;
}

/*======================================================*/
// 사이드 벡터 가져오기
/*======================================================*/
inline vector3df MovingEntity::getSide()
{
    vector3df vside(0, 1, 2);

    vside.normalize();

    return vside;
}

/*======================================================*/
// 포지션에 도달할 수 있는 시간 구하기
/*======================================================*/
inline double MovingEntity::calculateTimeToReachPosition( vector3df& pos)
{
    return ((getPos() -pos).getLength()) / (maxSpeed());
}

/*======================================================*/
// 특정 포지션에 있는지
/*======================================================*/
inline bool MovingEntity::isAtPosition(const vector3df& pos)
{
    const static double tolerance = 10;

    return (getPos() - pos).getLength() < (tolerance * tolerance);
}

#endif
