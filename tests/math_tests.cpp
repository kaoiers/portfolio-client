#include "../stdafx.h"
#include "../game/camera/CCameraManager.h"
#include "../game/map/CGameMap.h"
#include "../game/objects/CGameObjectManager.h"
#include "../game/objects/MovingEntity.h"

#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace
{
void require(bool condition, const char* message)
{
    if (!condition)
        throw std::runtime_error(message);
}

bool near(double actual, double expected)
{
    return std::fabs(actual - expected) < 0.0001;
}

void testVectors()
{
    vector3df zero;
    require(near(zero.getLength(), 0), "zero-initialized vector");
    require(near(zero.normalize().getLength(), 0), "zero normalization");
    const vector3df a(3, 4, 0), b(1, 2, 3);
    require(near(a.getLength(), 5) && near(a.getLengthSquared(), 25), "3D length");
    const auto normalized = a.normalize();
    require(near(normalized.X, 0.6) && near(normalized.Y, 0.8) && near(a.getLength(), 5), "nonmutating normalization");
    const auto sum = a + b;
    const auto diff = a - b;
    require(sum.X == 4 && sum.Y == 6 && sum.Z == 3, "vector addition");
    require(diff.X == 2 && diff.Y == 2 && diff.Z == -3, "vector subtraction");
    require((a * 2.0f).Y == 8 && (2.0f * a).X == 6, "scalar multiplication");
    require(near(a.dot(b), 11), "dot product");
    const auto cross = vector3df(1, 0, 0).cross(vector3df(0, 1, 0));
    require(cross.X == 0 && cross.Y == 0 && cross.Z == 1, "cross product");

    const vector2di integer(1, 1);
    require(near(integer.getLength(), std::sqrt(2.0)), "integer length retains fractions");
    require(near(integer.normalize().getLength(), 1), "integer normalization uses floating point");
    const vector2df v(3, 4);
    require(near(v.getLength(), 5) && near(v.dot(v), 25), "2D length and dot");
    const line2df line2{{1, 1}, {4, 5}};
    const line3df line3{{1, 2, 3}, {4, 6, 3}};
    require(near(line2.getLength(), 5) && near(line3.getLength(), 5), "line segment lengths");
    require(near(line3df{}.getLength(), 0), "degenerate line");
}

/// 이동 수학 연산을 검증하기 위한 테스트용 이동 객체이다.
class TestMover final : public MovingEntity
{
public:
    TestMover() : MovingEntity(object_mine, GODTYPE_UNIT, 5, 1, 0.5f, 1, 2,
        vector3df(10, 0, 20), vector3df(), vector3df(1, 1, 1)) {}
    void control(CEventHandler*) override {}
    bool handleMessage(const Telegram&) override { return false; }
};

void testMovement()
{
    TestMover mover;
    require(mover.getPos().X == 10 && mover.getPos().Z == 20, "initial position stored");
    mover.setPos({0, 0, 0});
    require(near(mover.getPos().getLength(), 0), "position setter");
    mover.setVelocity({3, 0, 4});
    require(near(mover.getSpeed(), 5) && near(mover.getSpeedSq(), 25), "speed and squared speed");
    require(mover.isSpeedMaxedOut(), "max speed reached");
    mover.setVelocity({1, 0, 1});
    require(!mover.isSpeedMaxedOut(), "speed below maximum");
    require(near(mover.calculateTimeToReachPosition({0, 0, 10}), 2), "time to reach position");
    require(mover.isAtPosition({9, 0, 0}) && !mover.isAtPosition({10, 0, 0}), "arrival tolerance");
    mover.setMaxSpeed(0);
    require(std::isinf(mover.calculateTimeToReachPosition({10, 0, 0})), "unreachable with zero speed");
    require(near(mover.calculateTimeToReachPosition({0, 0, 0}), 0), "already at target");
    mover.setHeading({0, 0, 5});
    require(near(mover.getHeading().Z, 1) && near(mover.getSide().X, 1), "heading and perpendicular side");
    require(!mover.rotateHeadingToFacePosition({10, 0, 0}), "rotation bounded by turn rate");
    for (int i = 0; i < 4; ++i)
        mover.rotateHeadingToFacePosition({10, 0, 0});
    require(near(mover.getHeading().X, 1), "heading converges to target");
}

void testTileCoordinates()
{
    CGameObjectManager manager;
    CCameraManager camera;
    CGameMap map(manager, camera);
    auto invalid = map.getTileFromPos({0, 0, 0});
    require(invalid.X == -1 && invalid.Y == -1, "uninitialized map rejected");
    require(!map.init(0, 80, 10, 10), "invalid dimensions rejected");
    require(map.init(60, 80, 10, 10, 10, 20), "map initialized");
    for (const auto tile : {vector2di(0, 0), vector2di(59, 79), vector2di(30, 40), vector2di(15, 30)})
    {
        const auto world = map.getPosByTile(tile.X, tile.Y);
        const auto round_trip = map.getTileFromPos(world);
        require(round_trip.X == tile.X && round_trip.Y == tile.Y, "tile center round trip");
        require(near((map.getNodePos(tile.X, tile.Y) - world).getLength(), 0), "node center matches tile");
    }
    const auto left_top = map.getTileFromPos({-300, 0, 800});
    require(left_top.X == 0 && left_top.Y == 0, "left/top border included");
    const auto right = map.getTileFromPos({300, 0, 0});
    const auto bottom = map.getTileFromPos({0, 0, -800});
    require(right.X == -1 && bottom.Y == -1, "right/bottom border excluded");
    require(map.getTileFromPos({std::numeric_limits<float>::infinity(), 0, 0}).X == -1, "nonfinite coordinate rejected");
    require(map.getNodeIndexFromTile(59, 79) == 4799 && map.getNodeIndexFromTile(-1, 0) == -1, "node index bounds");
    vector3df snapped(1, 2, 3);
    require(!map.getNodePosFromMousePos({300, 0, 0}, snapped), "invalid world position rejected");
    require(snapped.X == 1 && snapped.Y == 2 && snapped.Z == 3, "invalid lookup leaves output unchanged");
    require(map.getNodePosFromMousePos({0, 0, 0}, snapped), "valid world position snapped");
}
}

int main()
{
    try
    {
        testVectors();
        testMovement();
        testTileCoordinates();
        std::cout << "3 math and coordinate test groups passed\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
