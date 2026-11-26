//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/22
//
// File Name : CLoginGUI.h
// 
// 로그인 인터페이스
// 
//////////////////////////////////////////////////////////////////////////

#include "IGameGUI.h"

class CEventHandler;
class CGameObject;

enum eLoginWindow_GUI
{
	GUI_LOGIN_WINDOW_IMAGE = 7000,
	GUI_LOGIN_EDIT_ID,
	GUI_LOGIN_EDIT_PASSWORD,
	GUI_LOGIN_BUTTON_OK,
	GUI_LOGIN_BUTTON_CANCEL,
	GUI_LOGIN_BUTTON_SIGNUP,
	
	
	GUI_JOIN_WINDOW_IMAGE,
	GUI_JOIN_BUTTON_CONFIRM,
	GUI_JOIN_BUTTON_BACK,
	GUI_JOIN_EDIT_NEWID,
	GUI_JOIN_EDIT_NEWPASSWORD,
	GUI_JOIN_EDIT_NEWPASSWORD_CONFIRM
};



class CLoginGUI  : public CGameGUI
{	
	

	void					ShowLoginWindow(const bool bshow);
	void					ShowJoinWindow(const bool bshow);

private :

	virtual	bool			interface_control(CEventHandler* pReceiver);

public :

	virtual void			GUI_Initialize();

	void					ShowLoginWindowGUI(const bool bshow = true);


	CLoginGUI(position2d<s32> rect);
	virtual	~CLoginGUI() {};

	virtual	void	SetOwner(CGameObject *owner) {};



};