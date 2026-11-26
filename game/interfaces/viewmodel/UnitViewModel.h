#pragma once

#include "../../../basicType.h"
#include "../../objects/EnumObjectType.h"
#include <functional>
#include <memory>

class CGameObject;
class CGameUnit;

enum class UnitViewRole { Army, God, Worker };

/// 유닛 식별 정보, 성장 상태 및 현재 명령을 담는 값 스냅샷이다.
struct UnitViewState
{
    bool bound = false;
    u32 id = 0;
    u32 level = 0;
    s16 hp = 0;
    u32 max_hp = 0;
    f32 hp_ratio = 0;
    u32 exp = 0;
    u32 max_exp = 0;
    Command_Type command = com_none;
};

// Main-thread binding. The model owns its lifetime; the view model never owns the unit.
/// 유닛의 역할별 명령과 표시 상태를 중재하며 모델 수명을 소유하지 않는다.
class UnitViewModel
{
public:
    using Observer = std::function<void(const UnitViewState&)>;

    explicit UnitViewModel(UnitViewRole role) : m_role(role) {}
    UnitViewModel(const UnitViewModel&) = delete;
    UnitViewModel& operator=(const UnitViewModel&) = delete;

    void bind(CGameObject* object);
    void unbind();
    void refresh();
    void setObserver(Observer observer);
    const UnitViewState& state() const { return m_state; }

    bool requestGuard();
    bool requestAttack();
    bool requestCollect();
    bool requestIdle();
    bool requestBuild(BuildingTypes type);
    bool requestCancelBuilding();

private:
    CGameUnit* model() const;
    bool requestCommand(UnitViewRole required_role, Command_Type command);

    UnitViewRole m_role;
    CGameUnit* m_unit = nullptr;
    std::weak_ptr<const int> m_lifetime;
    UnitViewState m_state;
    Observer m_observer;
};
