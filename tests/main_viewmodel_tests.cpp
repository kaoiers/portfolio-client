#include "../stdafx.h"
#include "../game/God_Game.h"
#include "../game/attributes/GameResourceManager.h"
#include "../game/interfaces/CGUIManager.h"
#include "../game/interfaces/CMainGameGUI.h"
#include "../game/interfaces/CControllerGUI.h"
#include "../game/interfaces/viewmodel/MainGameViewModel.h"
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

/// 건물 ViewModel과 선택 제어 검증을 위한 테스트용 건물이다.
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
        ROOM_RESOURCE room_resource{};
        God_Game game;
        CGameResourceManager resources(20);
        CControllerGUI selection;
        CGameObjectManager objects(&selection);
        MainGameViewModel vm(resources, objects, game);
        int notifications = 0;
        vm.setObserver([&](const MainGameViewState&) { ++notifications; });
        require(vm.state().level == 1 && vm.state().unit_limit == 20, "initial main state");
        const int before = notifications;
        vm.refresh();
        require(notifications == before, "unchanged state not notified");

        resources.onNetworkSetResources(12, 34, 56);
        resources.addUnitCounts();
        vm.refresh();
        require(vm.state().crop == 12 && vm.state().lumber == 34 && vm.state().stone == 56 &&
            vm.state().units == 1, "resource snapshot updated");
        vm.requestAddExp(50);
        require(vm.state().exp == 50 && vm.state().exp_ratio == 0.25f, "experience presentation");
        vm.requestAddExp(150);
        require(vm.state().level == 2 && vm.state().exp == 0, "level transition");

        CMainGameGUI view(resources, objects, game);
        require(view.getViewState().level == 2, "view bound on construction");
        view.enableDoorButton(true);
        require(view.getViewState().door_enabled, "door flag bound");
        auto room = std::make_unique<TestRoom>(room_resource);
        auto* raw = room.get();
        require(objects.registerObject(std::move(room)), "room registered");
        require(!view.selectObject(nullptr), "no picked object rejected");
        require(!view.selectObject(raw), "selection unavailable outside game");
        game.setGameState(God_Game::GameState::on_game);
        view.setObjectSelectAvailable(false);
        require(!view.selectObject(raw), "selection flag respected");
        view.setObjectSelectAvailable(true);
        require(view.selectObject(raw) && selection.getCurrentControlGUI(), "selection routed through controller");
        require(objects.removeObject(raw->getId()), "selected room removed");
        require(!selection.getCurrentControlGUI(), "selection cleared");

        // The real composition root wires the resource model to the main view.
        God_Game composed;
        require(composed.initialize(), "game composition initialized");
        auto* main_view = composed.getGUIManager()->getMainGameGUI();
        require(main_view && main_view->getViewState().level == 1, "main GUI initialized by composition");
        std::cout << "Main game MVVM tests passed\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
