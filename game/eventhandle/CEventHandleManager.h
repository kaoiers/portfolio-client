//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/03/30
//
// File Name : CEventHandleManager.h
// 
// 게임 이벤트 관리
// 
//////////////////////////////////////////////////////////////////////////


enum
{
	INVALID_BUTTON = -1,
	
};

class CGUIManager;
class God_Game;
class IGUIObject;

struct SGuiEvent : public SEvent
{
	s32	GUI_ID;
	s32	GetGUID() const {return GUI_ID;}
};


struct KeyEventParam
{
	char key;
	bool downed;
	bool shift;

	KeyEventParam()
	{
		downed = shift = false;
	}

	KeyEventParam( const KeyEventParam& rvalue )
	{
		this->key = rvalue.key;
		this->downed = rvalue.downed;
		this->shift = rvalue.shift;
	}
};


class CEventHandler 
{
	enum {
		MOUSELEFT = 0, 
		MOUSEMIDDLE, 
		MOUSERIGHT,
		KEY_KEY_CODES_COUNT = 0xff,
	};

private :

	God_Game*						m_pGame;
	CGUIManager*					m_pGUIManager;
	position2d<s32>					MousePosition;
	position2d<f32>					MouseRelativePosition;
	bool							KeyIsDown[0xFF];
	bool							OneKeyIsDown[0xFF];
	bool							bMouseButtonDown[3];
	bool							bMouseButtonUp[3];
	bool							bMouseOneclick[3];
	f32								iOffsetWheel;
	s32								m_iButtonID;
	bool							m_bOverGUI;

	void							allkeyUpdate();

	std::vector<KeyEventParam>		m_pressedKeys;
public :	
	bool		isMouseLDown() const  {return bMouseButtonDown[MOUSELEFT]; }
	bool		isMouseMDown() const  { return bMouseButtonDown[MOUSEMIDDLE]; }
	bool		isMouseRDown() const  { return bMouseButtonDown[MOUSERIGHT]; }

	bool		isMouseLUp()  {	return bMouseButtonUp[MOUSELEFT]; }
	bool		isMouseMUp() const { return bMouseButtonUp[MOUSEMIDDLE]; }
	bool		isMouseRUp() const { return bMouseButtonUp[MOUSERIGHT]; }


	bool		isMouseLOneClick() { return bMouseOneclick[MOUSELEFT]; }
	bool		isMouseROneClick() { return bMouseOneclick[MOUSERIGHT]; }
	bool		isMouseMOneClick() { return bMouseOneclick[MOUSEMIDDLE]; } 


	bool		getPressedKey( KeyEventParam& keyParam );

	inline f32 getWheelOffset()  
	{
		f32 tempOffset = iOffsetWheel;
		iOffsetWheel = 0.0f;		
		return tempOffset; 	
	}

	position2d<s32>		getMousePosition() const {return MousePosition; }
	const position2d<s32>		getWindowMousePos() const;

	const position2d<f32>&		getRelativeMousePosition() const {return MouseRelativePosition; }
	const line3d<f32>			getRay();
	const bool					isMouseOutOfScreen();
	vector3d<f32>				getMouseUpGroundPosition() { return vector3d<f32>(0, 0, 0); };
	
	bool						isClickedButtonID(s32 buttonID);
	void						setInvalidButtonID() { m_iButtonID = INVALID_BUTTON;  }
	
	void						setCursorOnGUI(const IGUIObject* obj, const bool on = true );
	const bool					isCursorOnGUI() const  { return m_bOverGUI ; }
	u32							getScreenHeight() const ;
	u32							getScreenWidth() const ;
	
	CEventHandler();

	inline	 void	 update()
	{
		allkeyUpdate();
		setInvalidButtonID();
		m_bOverGUI =  false;
	}
};



