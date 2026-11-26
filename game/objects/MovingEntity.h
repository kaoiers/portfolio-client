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
#include <algorithm>
#include <limits>
#include "CGameObject.h"

enum { clockwise = 1, anticlockwise = -1 };

class MovingEntity :public CGameObject
{
#define Node getSceneNode()

protected:
    vector3df m_velocity;
    vector3df m_position;
    vector3df m_heading{0.0f, 0.0f, 1.0f};

    f32 m_movement_mass;

    f32 m_movement_max_speed;

    f32 m_movement_max_force;

    f32 m_max_turn_rate;

    f32 m_bounding_radius = 0.0f;

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
    m_position(pos),
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
    m_position(pos),
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

    vector3df getPos() const { return m_position; }
    void setPos(const vector3df& pos) { m_position = pos; }

    f32 getNormalSpeed() const { return m_movement_normal_speed; }

    vector3df getSide() const;

    f32 maxSpeed() const { return m_movement_max_speed; }
    void setMaxSpeed(f32 new_speed) { m_movement_max_speed = new_speed; }

    f32 maxForce() const { return m_movement_max_force; }
    void setMaxForce(f32 mf) { m_movement_max_force = mf; }

    bool isSpeedMaxedOut() const { return m_velocity.getLengthSquared() >= m_movement_max_speed * m_movement_max_speed; }
    f32 getSpeed() const { return m_velocity.getLength(); }
    f32 getSpeedSq() const { return m_velocity.getLengthSquared(); }

    vector3df getHeading() const;
    void setHeading(const vector3df& new_heading);
    bool rotateHeadingToFacePosition(vector3df target);

    f32 getMaxTurnRate() const { return m_max_turn_rate; }
    void setMaxTurnRate(f32 val) { m_max_turn_rate = val; }

    inline double calculateTimeToReachPosition(const vector3df& pos) const;
    inline bool isAtPosition(const vector3df& pos) const;
};

/*======================================================*/
// 전방을 목표방향으로 돌리기
/*======================================================*/
inline bool MovingEntity::rotateHeadingToFacePosition(vector3df target)
{
    // Rotation is measured in radians per call on the XZ ground plane.
    const vector3df offset = target - m_position;
    const auto desired = vector3df(offset.X, 0.0f, offset.Z).normalize();
    if (desired.getLengthSquared() == 0.0f)
        return true;

    const auto heading = vector3df(m_heading.X, 0.0f, m_heading.Z).normalize();
    if (heading.getLengthSquared() == 0.0f)
    {
        m_heading = desired;
        return true;
    }

    const f32 angle = std::atan2(heading.Z * desired.X - heading.X * desired.Z, heading.dot(desired));
    const f32 limit = (std::max)(0.0f, m_max_turn_rate);
    constexpr f32 ALIGNMENT_EPSILON = 0.0001f;
    if (std::fabs(angle) <= limit + ALIGNMENT_EPSILON)
    {
        m_heading = desired;
        return true;
    }

    const f32 step = std::clamp(angle, -limit, limit);
    m_heading = vector3df(
        heading.X * std::cos(step) + heading.Z * std::sin(step),
        0.0f,
        heading.Z * std::cos(step) - heading.X * std::sin(step)).normalize();
    return false;
}

inline void MovingEntity::setHeading(const vector3df& new_heading)
{
    const auto heading = new_heading.normalize();
    if (heading.getLengthSquared() > 0.0f)
        m_heading = heading;
}

inline vector3df MovingEntity::getHeading() const
{
    return m_heading;
}

inline vector3df MovingEntity::getSide() const
{
    return vector3df(0.0f, 1.0f, 0.0f).cross(m_heading).normalize();
}

inline double MovingEntity::calculateTimeToReachPosition(const vector3df& pos) const
{
    const auto distance = (getPos() - pos).getLength();
    if (distance == 0.0f)
        return 0.0;
    if (maxSpeed() <= 0.0f)
        return std::numeric_limits<double>::infinity();
    return static_cast<double>(distance) / maxSpeed();
}

inline bool MovingEntity::isAtPosition(const vector3df& pos) const
{
    constexpr f32 POSITION_TOLERANCE = 10.0f;
    return (getPos() - pos).getLengthSquared() < POSITION_TOLERANCE * POSITION_TOLERANCE;
}

#endif
