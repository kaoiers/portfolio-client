#include "../stdafx.h"
#include "../game/attributes/GameResourceManager.h"
#include "../game/interfaces/CControllerGUI.h"
#include "../game/interfaces/CUnitArmyGUI.h"
#include "../game/interfaces/viewmodel/UnitViewModel.h"
#include "../game/objects/CGameObjectManager.h"
#include "../game/objects/CGameUnitArmy.h"
#include "../game/objects/SGameUnitAttributeResources.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

namespace
{
void require(bool condition, const char* message)
{
    if (!condition)
        throw std::runtime_error(message);
}

class TestArmy final : public CGameUnitArmy
{
public:
    TestArmy(u32 id, const UNIT_RESOURCE& resource, const GAMEUNIT_ATTRIBUTE& attribute)
        : CGameUnitArmy(object_mine, id, GODTYPE_UNIT, &resource, &attribute, UNIT_ARMY_BUNNY) {}
    void control(CEventHandler*) override {}
    void onCommand() override {}
    void privateInitialize() override {}
};
}

int main()
{
    try
    {
        UNIT_RESOURCE resource{};
        GAMEUNIT_ATTRIBUTE attribute{};
        attribute.m_default_level = 2;
        attribute.m_default_hp = 100;
        attribute.m_default_exp = 30;
        CGameResourceManager resources;
        CControllerGUI selection;
        CGameObjectManager manager(&selection);

        auto unit = std::make_unique<TestArmy>(17, resource, attribute);
        auto* raw = unit.get();
        require(manager.registerObject(std::move(unit)), "unit registered");

        UnitViewModel vm(UnitViewRole::Army);
        int notifications = 0;
        vm.setObserver([&](const UnitViewState&) { ++notifications; });
        require(!vm.requestGuard(), "unbound command rejected");
        vm.bind(raw);
        require(vm.state().bound && vm.state().id == 17, "model bound");
        require(vm.state().level == 2 && vm.state().hp == 100 && vm.state().exp == 0, "presentation snapshot");
        require(std::fabs(vm.state().hp_ratio - 1.0f) < 0.0001f, "initial HP ratio");
        const int before = notifications;
        vm.refresh();
        require(notifications == before, "unchanged state does not notify");
        raw->calAttacked(25);
        vm.refresh();
        require(vm.state().hp == 75 && std::fabs(vm.state().hp_ratio - 0.75f) < 0.0001f, "model change reflected");
        require(notifications == before + 1, "one change notification");
        require(vm.requestGuard() && raw->getCommandType() == com_room_guard, "guard command reaches model");
        require(!vm.requestAttack(), "role-specific command rejected");

        UnitViewModel worker(UnitViewRole::Worker);
        worker.bind(raw);
        require(!worker.state().bound && !worker.requestCollect(), "wrong unit role rejected");

        manager.setController(raw);
        auto* view = dynamic_cast<CUnitArmyGUI*>(selection.getCurrentControlGUI());
        require(view && view->getViewState().id == 17, "controller selects unit view");
        raw->calAttacked(5);
        view->refreshView();
        require(view->getViewState().hp == 70, "view consumes changed state");
        require(manager.removeObject(17), "bound object removed");
        vm.refresh();
        require(!vm.state().bound && !vm.requestGuard(), "destroyed binding invalidated");
        require(selection.getCurrentControlGUI() == nullptr, "selection cleared on deletion");

        std::cout << "Unit MVVM binding and controller tests passed\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
