#include "../game/ai/Goal_Composite.h"
#include "../game/ai/Telegram.h"
#include "../game/objects/CObjectListSet.h"

#include <iostream>
#include <memory>
#include <stdexcept>

namespace
{
void require(bool condition, const char* message)
{
    if (!condition)
        throw std::runtime_error(message);
}

struct Owner {};
struct Counters
{
    int activated = 0;
    int terminated = 0;
    int destroyed = 0;
};

class TestGoal final : public Goal<Owner>
{
public:
    TestGoal(Owner* owner, Counters& counts, s32 state = completed)
        : Goal(owner, 1), counts_(counts), next_state_(state) {}
    ~TestGoal() override { ++counts_.destroyed; }

    void activate() override
    {
        ++counts_.activated;
        m_status = active;
    }

    s32 process() override
    {
        activateIfInactive();
        m_status = next_state_;
        return m_status;
    }

    void terminate() override { ++counts_.terminated; }
    bool handleMessage(const Telegram&) override { return true; }

private:
    Counters& counts_;
    s32 next_state_;
};

class TestComposite final : public Goal_Composite<Owner>
{
public:
    explicit TestComposite(Owner* owner) : Goal_Composite(owner, 2) {}
    void activate() override { m_status = active; }
    s32 process() override
    {
        activateIfInactive();
        return processSubgoals();
    }
    void terminate() override { removeAllSubgoals(); }
};

void testGoalOwnership()
{
    Owner owner;
    Counters first, second;
    TestComposite composite(&owner);
    composite.addSubgoal(std::make_unique<TestGoal>(&owner, first));
    composite.addSubgoal(std::make_unique<TestGoal>(&owner, second));
    require(composite.process() == Goal<Owner>::active, "remaining goal keeps composite active");
    require(second.activated == 1 && first.activated == 0, "goals process front first");
    require(composite.handleMessage(Telegram{}), "message forwarded to front");
    require(composite.process() == Goal<Owner>::completed, "last goal completes");
    require(second.terminated == 1 && second.destroyed == 1, "completed goal retired");
    composite.terminate();
    require(first.terminated == 1 && first.destroyed == 1, "remaining goal released");
    require(!composite.handleMessage(Telegram{}), "empty composite rejects message");
}

void testTelegram()
{
    require(Telegram{}.extra_info == nullptr, "default payload is empty");
    int payload = 42;
    Telegram first(1.0, 1, 2, 3, &payload);
    Telegram near(1.1, 1, 2, 3, &payload);
    Telegram later(2.0, 1, 2, 3, &payload);
    require(!(first == near), "distinct timestamps remain distinct");
    require(first < near && near < later, "message timestamps are ordered");
    require(first == Telegram(1.0, 1, 2, 3, &payload), "same identity compares equal");
    require(first < later, "earlier telegram sorts first");
    require(dereferenceToType<int>(first.extra_info) == 42, "payload access");
}

void testObjectList()
{
    CObjectListSet<int> objects;
    objects.add(1);
    objects.add(2);
    objects.add(1);
    require(objects.getAll().size() == 2, "duplicate objects ignored");
    objects.remove(1);
    require(objects.getAll().size() == 1 && objects.getAll().front() == 2, "object removed");
    objects.clear();
    require(objects.getAll().empty(), "object list cleared");
}
}

int main()
{
    try
    {
        testGoalOwnership();
        testTelegram();
        testObjectList();
        std::cout << "3 core tests passed\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
