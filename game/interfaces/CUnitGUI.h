#pragma once

#include "IGameGUI.h"
#include "viewmodel/UnitViewModel.h"

// Engine-independent presentation state; the renderer can consume the cached snapshot.
class CUnitGUI : public CGameGUI
{
public:
    CUnitGUI(UnitViewRole role, position2d<s16> rect)
        : CGameGUI(rect), m_view_model(role)
    {
        m_view_model.setObserver([this](const UnitViewState& state) { m_view_state = state; });
    }

    void setOwner(CGameObject* object) override { m_view_model.bind(object); }
    void setDamage(const u32, const u32) override { m_view_model.refresh(); }
    const UnitViewState& getViewState() const { return m_view_state; }
    void refreshView() { m_view_model.refresh(); }

protected:
    UnitViewModel m_view_model;

private:
    UnitViewState m_view_state;
};
