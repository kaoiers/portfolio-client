#include "../stdafx.h"
#include "../game/ai/MessageDispatcher.h"
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

class Receiver final : public CGameObject
{
public:
    explicit Receiver(u32 id) : CGameObject(object_mine, id, GODTYPE_BLOCK) {}
    void control(CEventHandler*) override {}
    void onCommand() override {}
    bool handleMessage(const Telegram& message) override
    {
        received.push_back(message);
        return true;
    }
    std::vector<Telegram> received;
};

Receiver* addReceiver(CGameObjectManager& manager, u32 id)
{
    auto receiver = std::make_unique<Receiver>(id);
    auto* raw = receiver.get();
    require(manager.registerObject(std::move(receiver)), "receiver registered");
    return raw;
}
}

int main()
{
    try
    {
        CGameObjectManager manager;
        CGameObjectManager other;
        auto* one = addReceiver(manager, 1);
        auto* two = addReceiver(manager, 2);
        auto* foreign = addReceiver(other, 2);
        auto& dispatcher = manager.getMessageDispatcher();

        int payload = 42;
        require(dispatcher.dispatchMsg(0.0, 1, 2, 10, &payload), "immediate delivery accepted");
        require(two->received.size() == 1 && two->received.back().extra_info == &payload, "payload forwarded synchronously");
        require(foreign->received.empty(), "separate manager isolated");
        require(!dispatcher.dispatchMsg(0.0, 1, 99, 10), "missing receiver rejected");
        require(!dispatcher.dispatchMsg(1.0, 1, 2, 10, &payload), "borrowed delayed payload rejected");

        require(dispatcher.dispatchMsg(0.2, 1, 2, 20), "later message queued");
        require(dispatcher.dispatchMsg(0.1, 1, 2, 11), "earlier message queued");
        require(dispatcher.dispatchMsg(0.1, 1, 2, 12), "same deadline preserved");
        require(dispatcher.dispatchMsg(0.1, 1, 2, 12), "duplicate message preserved");
        manager.update(nullptr, 99);
        require(two->received.size() == 1, "no early delivery");
        manager.update(nullptr, 1);
        require(two->received.size() == 4, "all same-deadline messages delivered");
        require(two->received[1].msg == 11 && two->received[2].msg == 12 && two->received[3].msg == 12, "FIFO at equal deadlines");
        manager.update(nullptr, 100);
        require(two->received.back().msg == 20, "later message delivered");

        require(dispatcher.dispatchMessageToAllObjects(0.0, SENDER_ID_IRRELEVANT, 30), "system broadcast accepted");
        require(one->received.back().msg == 30 && two->received.back().msg == 30, "broadcast delivered to both");
        require(dispatcher.dispatchMessageToAllObjects(0.1, 1, 31), "delayed broadcast accepted");
        manager.update(nullptr, 100);
        require(one->received.back().msg == 31 && two->received.back().msg == 31, "delayed broadcast delivered");

        require(dispatcher.dispatchMsg(1.0, 1, 2, 40), "message queued before deletion");
        require(manager.removeObject(2), "receiver deleted");
        auto* replacement = addReceiver(manager, 2);
        manager.update(nullptr, 1000);
        require(replacement->received.empty(), "deleted receiver message not delivered to reused ID");

        std::cout << "Message dispatcher tests passed\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
