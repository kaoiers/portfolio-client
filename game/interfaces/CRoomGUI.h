#pragma once
#include "IGameGUI.h"
#include "viewmodel/RoomViewModel.h"

/// 건물 ViewModel의 바인딩과 표시 상태 캐시를 제공하는 공통 View이다.
class CRoomGUI : public CGameGUI
{
public:
    CRoomGUI(BuildingTypes type, position2d<s16> rect)
        : CGameGUI(rect), m_view_model(type)
    {
        m_view_model.setObserver([this](const RoomViewState& state) { m_view_state = state; });
    }
    CRoomGUI(const CRoomGUI&) = delete;
    CRoomGUI& operator=(const CRoomGUI&) = delete;
    void setOwner(CGameObject* object) override { m_view_model.bind(object); }
    void setDamage(u32, u32) override { refreshView(); }
    void refreshView() { m_view_model.refresh(); }
    const RoomViewState& getViewState() const { return m_view_state; }

protected:
    RoomViewModel m_view_model;
private:
    RoomViewState m_view_state;
};
