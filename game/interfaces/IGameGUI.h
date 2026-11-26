//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/05/05
//
// File Name : CGameGUI.h
//
// GUI 인터페이스
//
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_GUI
#define	GAME_GUI

#include "IBaseGameGUI.h"
#include "EnumGUITypes.h"
#include "../objects/CObjectListSet.h"

class IGUIObject;
class CButtonGUI;
class CImageGUI;
class CTextGUI;
class CGameObject;
class CEditBoxGUI;
class CEventHandler;
class CGUIManager;

/// 공통 GUI 요소, 그룹, 표시 여부와 입력 처리 인터페이스를 관리한다.
class CGameGUI : public IBaseGameGUI
{
    u32 m_gid;

    bool m_need_owner;

    bool m_enable;

    bool m_use_one_select_button;

    bool m_one_button_select;

    IGUIObject* m_focused_object;

    static u32 m_next_valid_id;

    bool elementControl(CEventHandler* m_receiver);
protected:
    typedef std::list<IGUIObject *> GuiElementsList;

    typedef std::map<std::string, CObjectListSet<IGUIObject *> > GroupGUI;

    GroupGUI m_group;
    position2d<s16> m_absolute_position;
    GuiElementsList m_elements;
    CGameObject* m_owner;

public:
    CGameGUI() {};
    CGameGUI(position2d<s16> pos = position2d<s16>(0, 0));

    virtual ~CGameGUI();

    void setOneButtonInterface(const bool sel = true) { m_use_one_select_button = sel; }

    bool isOneButtonInterface() const { return m_use_one_select_button; }

    void setOneButtonSelectState( IGUIObject *guiobj);

    void setAllButtonSelectState(const bool states = true);

    bool isOneButtonSelectState();

    bool isMouseOnButton();

    bool hasFocus(IGUIObject* obj);

public:
    bool control(CEventHandler* m_receiver);

    void show();

    void hide();

    bool isEnable() const { return m_enable; }

    bool isClicked() { return true; };

public:
    void setPosition(const vector2di pos);

    void registerElement( IGUIObject *p_gui);

    IGUIObject* findElementById(s16 eid);

    position2d<s16> getPosition() const { return m_absolute_position; }

    u32 getId() const { return m_gid; }

    void setNeedOwner(const bool need = true) { m_need_owner = need; }

    bool isNeedOwner() const { return m_need_owner; }

    bool postEvent(const SEvent& event) { return true; };

public:
    CButtonGUI* addButton(const position2d<s16> position, const char* default_image, s16 m_id = -1, std::wstring text = L"");

    CImageGUI* addImage(const position2d<s16> position, const char* default_image, s16 m_id = -1);

    position2d<s16> getRelativePosition( const position2d<s16> pos) const;

    position2d<s16> getAbsolutePosition(const position2d<s16> pos) const;

    bool findGroupByName(const char * name, std::list<IGUIObject *>* p_group_list);

    CObjectListSet<IGUIObject *>* findGroupByName( const char * name);

    void addGroup(const char * name, IGUIObject* obj);

    void showGroup(const char *name, const bool bshow = true) {};

    CGUIManager* getGUIManager();
};

#endif
