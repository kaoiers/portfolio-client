#pragma once

class CGameObject;

// Controller-to-presentation boundary. Game objects do not know concrete GUI types.
/// 선택 상태를 구체적인 GUI에 결합하지 않고 전달하는 Controller 경계이다.
class ISelectionView
{
public:
    virtual ~ISelectionView() = default;
    virtual void showSelection(CGameObject* object) = 0;
    virtual void clearSelection() = 0;
};
