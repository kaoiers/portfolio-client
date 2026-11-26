#include "../stdafx.h"
#include "../game/navigation/AsyncPathfinder.h"
#include "../game/map/CGameMap.h"
#include "../game/camera/CCameraManager.h"
#include "../game/objects/CGameObjectManager.h"
#include "../game/objects/CGameUnit.h"
#include "../game/objects/SGameUnitAttributeResources.h"
#include "../game/ai/Goal_MoveToPosition.h"

#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>

namespace
{
void require(bool condition, const char* message)
{
    if (!condition) throw std::runtime_error(message);
}

/// 비동기 경로 탐색 목표를 검증하는 테스트용 유닛이다.
class TestUnit final : public CGameUnit
{
public:
    TestUnit(const UNIT_RESOURCE& resource, const GAMEUNIT_ATTRIBUTE& attribute, vector3df position)
        : CGameUnit(object_mine, GODTYPE_UNIT, &resource, &attribute, UNIT_WORKER1, unit_mine, position) {}
    void control(CEventHandler*) override {}
    void onCommand() override {}
    bool shortAttack(CGameUnit*) override { return false; }
    void privateInitialize() override {}
    void enterControl() override {}
    void updateControl(CEventHandler*) override {}
    void exitControl() override {}
};

/// 테스트에서 이동 목표에 경유점 하위 목표가 설치되었는지 확인한다.
class InspectableMove final : public Goal_MoveToPosition
{
public:
    using Goal_MoveToPosition::Goal_MoveToPosition;
    bool followingPath() const { return !m_sub_goals.empty(); }
};

void awaitRoute(InspectableMove& goal)
{
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
    while (!goal.followingPath() && goal.process() == Goal<CGameUnit>::active &&
        std::chrono::steady_clock::now() < deadline)
        std::this_thread::yield();
    require(goal.followingPath(), "async result installed as follow-path goal");
}
}

int main()
{
    try
    {
        AsyncPathfinder service(2);
        NavigationGrid grid(5, 5);
        auto first = service.request(grid, 7, {0, 0}, {4, 0});
        grid.setBlocked({2, 0}, true);
        auto second = service.request(grid, 8, {0, 0}, {4, 0});
        const auto old_result = first.get();
        const auto new_result = second.get();
        require(old_result.revision == 7 && old_result.path.points.size() == 5, "old snapshot unchanged");
        require(new_result.revision == 8 && new_result.path.points.size() == 7, "new snapshot avoids obstacle");

        CGameObjectManager manager;
        CCameraManager camera;
        CGameMap map(manager, camera);
        require(map.init(60, 80, 10, 10, 50, 50), "map initialized");
        UNIT_RESOURCE resource{};
        resource.m_max_speed = 100;
        GAMEUNIT_ATTRIBUTE attribute{};
        attribute.m_default_hp = 100;
        TestUnit unit(resource, attribute, map.getPosByTile(20, 35));
        const auto target = map.getPosByTile(22, 35);

        InspectableMove goal(&unit, target, &map);
        goal.activate();
        awaitRoute(goal);
        // Headless test moves the unit to each expected waypoint as the renderer/steering layer would.
        unit.setPos(map.getPosByTile(21, 35));
        goal.process();
        unit.setPos(target);
        require(goal.process() == Goal<CGameUnit>::completed, "ordered waypoints complete movement goal");

        unit.setPos(map.getPosByTile(20, 35));
        InspectableMove stale(&unit, target, &map);
        stale.activate();
        map.removeNode(21, 35);
        awaitRoute(stale); // The old request is discarded and replanned on the new revision.
        require(stale.process() == Goal<CGameUnit>::active, "replanned goal active");
        stale.terminate();
        require(stale.isComplete(), "cancellation clears goal");

        std::cout << "Async path snapshot and goal integration tests passed\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
