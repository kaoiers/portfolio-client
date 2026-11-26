#pragma once

class CGameObject;

// Controller-to-presentation boundary. Game objects do not know concrete GUI types.
class ISelectionView
{
public:
    virtual ~ISelectionView() = default;
    virtual void showSelection(CGameObject* object) = 0;
    virtual void clearSelection() = 0;
};
