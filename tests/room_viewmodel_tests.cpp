#include "../stdafx.h"
#include "../game/interfaces/CControllerGUI.h"
#include "../game/interfaces/CRoomJailGUI.h"
#include "../game/interfaces/viewmodel/RoomViewModel.h"
#include "../game/objects/CGameObjectManager.h"
#include "../game/objects/CGameRoomJail.h"

#include <iostream>
#include <stdexcept>

namespace
{
void require(bool condition, const char* message)
{
    if (!condition) throw std::runtime_error(message);
}

class TestRoom final : public CGameRoomJail
{
public:
    explicit TestRoom(const ROOM_RESOURCE& resource)
        : CGameRoomJail(object_mine, GODTYPE_BUILDING, BUILDING_JAIL, &resource) {}
    void control(CEventHandler*) override {}
    void onCommand() override {}
};
}

int main()
{
    try
    {
        ROOM_RESOURCE resource{};
        CControllerGUI selection;
        CGameObjectManager manager(&selection);
        int sound_requests = 0;
        manager.setSoundSink([&](const char* name, bool) {
            require(std::string(name) == "explosion", "sound event name");
            ++sound_requests;
        });
        auto room = std::make_unique<TestRoom>(resource);
        auto* raw = room.get();
        raw->setId(12);
        require(manager.registerObject(std::move(room)), "room registered");

        RoomViewModel vm(BUILDING_JAIL);
        int notifications = 0;
        vm.setObserver([&](const RoomViewState&) { ++notifications; });
        vm.bind(raw);
        require(vm.state().bound && vm.state().hp == 1000, "room state bound");
        const int before = notifications;
        vm.refresh();
        require(notifications == before, "unchanged state not notified");
        raw->addDamage(250, nullptr);
        vm.refresh();
        require(vm.state().hp == 750 && vm.state().hp_ratio == 0.75f, "HP snapshot updated");
        RoomViewModel wrong(BUILDING_WAREHOUSE);
        wrong.bind(raw);
        require(!wrong.state().bound, "wrong room type rejected");

        manager.setController(raw);
        auto* view = dynamic_cast<CRoomJailGUI*>(selection.getCurrentControlGUI());
        require(view && view->getViewState().hp == 750, "controller binds room view");
        require(vm.requestDestroy(), "destroy action queued");
        require(sound_requests == 1, "audio event emitted without GUI");
        manager.removeDeleteQueue();
        vm.refresh();
        require(!vm.state().bound && !vm.requestDestroy(), "deleted room binding invalidated");
        require(selection.getCurrentControlGUI() == nullptr, "selection cleared");
        std::cout << "Room MVVM tests passed\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
