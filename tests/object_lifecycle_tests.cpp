#include "../stdafx.h"
#include "../game/objects/CGameObject.h"
#include "../game/objects/CGameObjectManager.h"

#include <iostream>
#include <stdexcept>

namespace
{
void require(bool condition, const char* message)
{
    if (!condition)
        throw std::runtime_error(message);
}

class TestObject final : public CGameObject
{
public:
    TestObject(u32 id, int& destroyed)
        : CGameObject(object_mine, id, GODTYPE_BLOCK), destroyed_(destroyed) {}
    ~TestObject() override { ++destroyed_; }
    void control(CEventHandler*) override {}
    void onCommand() override {}
    bool handleMessage(const Telegram&) override { return false; }

private:
    int& destroyed_;
};
}

int main()
{
    try
    {
        int destroyed = 0;
        {
            CGameObjectManager manager;
            require(!manager.registerObject(nullptr), "null registration rejected");
            auto object = std::make_unique<TestObject>(7, destroyed);
            auto* raw = object.get();
            require(manager.registerObject(std::move(object)), "registration succeeds");
            require(manager.getObjectFromId(7) == raw, "lookup returns registered object");
            require(raw->getObjectManager() == &manager, "owner manager bound");
            require(!manager.registerObject(std::make_unique<TestObject>(7, destroyed)), "duplicate rejected");
            require(destroyed == 1, "rejected object destroyed");
            require(manager.getObjectFromId(7) == raw, "duplicate does not replace original");
            manager.deleteRequest(7);
            manager.deleteRequest(7);
            manager.removeDeleteQueue();
            require(manager.getObjectFromId(7) == nullptr, "deferred deletion removes object");
            require(destroyed == 2, "duplicate deletion is harmless");
            auto generated = std::make_unique<TestObject>(0, destroyed);
            auto* generated_raw = generated.get();
            require(manager.registerObject(std::move(generated)), "auto id registration succeeds");
            require(generated_raw->getId() != 0, "nonzero id assigned");
            require(manager.registerObject(std::make_unique<TestObject>(8, destroyed)), "second object registered");
            manager.removeAllObjects();
            require(manager.getObjectFromId(8) == nullptr && destroyed == 4, "bulk cleanup releases owned objects");
            require(manager.registerObject(std::make_unique<TestObject>(9, destroyed)), "registration before teardown");
        }
        require(destroyed == 5, "manager destructor releases remaining objects");
        std::cout << "Object lifecycle tests passed\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
