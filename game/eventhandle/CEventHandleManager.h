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
	s16	GUI_ID;
	s16	getGuid() const {return GUI_ID;}
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

	God_Game*						m_game;
	CGUIManager*					m_gui_manager;
	position2d<s16>					mouse_position;
	position2d<f32>					mouse_relative_position;
	bool							key_is_down[0xFF];
	bool							one_key_is_down[0xFF];
	bool							b_mouse_button_down[3];
	bool							b_mouse_button_up[3];
	bool							b_mouse_one_click[3];
	f32								wheel_offset;
	s16								m_button_id;
	bool							m_over_gui;

	void							allKeyUpdate();

	std::vector<KeyEventParam>		m_pressed_keys;
public :	
	bool		isMouseLDown() const  {return b_mouse_button_down[MOUSELEFT]; }
	bool		isMouseMDown() const  { return b_mouse_button_down[MOUSEMIDDLE]; }
	bool		isMouseRDown() const  { return b_mouse_button_down[MOUSERIGHT]; }

	bool		isMouseLUp()  {	return b_mouse_button_up[MOUSELEFT]; }
	bool		isMouseMUp() const { return b_mouse_button_up[MOUSEMIDDLE]; }
	bool		isMouseRUp() const { return b_mouse_button_up[MOUSERIGHT]; }


	bool		isMouseLOneClick() { return b_mouse_one_click[MOUSELEFT]; }
	bool		isMouseROneClick() { return b_mouse_one_click[MOUSERIGHT]; }
	bool		isMouseMOneClick() { return b_mouse_one_click[MOUSEMIDDLE]; } 


	bool		getPressedKey( KeyEventParam& key_param );

	inline f32 getWheelOffset()  
	{
		f32 temp_offset = wheel_offset;
		wheel_offset = 0.0f;		
		return temp_offset; 	
	}

	const position2d<s16>&		getMousePosition() const {return mouse_position; }
	const position2d<s16>		getWindowMousePos() const;

	const position2d<f32>&		getRelativeMousePosition() const {return mouse_relative_position; }
	const line3d<f32>			getRay();
	const bool					isMouseOutOfScreen();
	vector3d<f32>				getMouseUpGroundPosition() { return vector3d<f32>(0, 0, 0); };
	
	bool						isClickedButtonID(s16 button_id);
	void						setInvalidButtonID() { m_button_id = INVALID_BUTTON;  }
	
	void						setCursorOnGUI(const IGUIObject* obj, const bool on = true );
	const bool					isCursorOnGUI() const  { return m_over_gui ; }
	u32							getScreenHeight() const ;
	u32							getScreenWidth() const ;
	
	CEventHandler();

	inline	 void	 update()
	{
		allKeyUpdate();
		setInvalidButtonID();
		m_over_gui =  false;
	}
};



