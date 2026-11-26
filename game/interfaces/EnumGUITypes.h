//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/04/09
//
// File Name : ENUMGUITYPES.h
// 
// GUI 타입 정의
// 
//////////////////////////////////////////////////////////////////////////

#ifndef DEF_GUITYPE
#define DEF_GUITYPE

#include <string>

enum GUI_TYPE 
{
	GUI_TYPE_START = 0,

	GUI_TYPE_INGAME, 

	GUI_TYPE_LOGIN, 

	GUI_TYPE_OBJECT_SOLDIER, 
	
	GUI_TYPE_OBJECT_ARCHER, 

	GUI_TYPE_OBJECT_MAGICIAN, 

	GUI_TYPE_OBJECT_ENEMY, 

	GUI_TYPE_OBJECT_GOD
};


inline std::string GetLuaFileFromGUIType(int objtype)
{
	switch(objtype)
	{
	case GUI_TYPE_START:

		return "gui_start";

	case GUI_TYPE_INGAME:

		return "gui_ingame";

	case GUI_TYPE_LOGIN:

		return "gui_login";

	case GUI_TYPE_OBJECT_SOLDIER:

		return "gui_soldier";

	case GUI_TYPE_OBJECT_ARCHER:

		return "gui_archer";

	case GUI_TYPE_OBJECT_MAGICIAN:

		return "gui_magician";
	
	case GUI_TYPE_OBJECT_ENEMY:

		return "gui_enemy";

	case GUI_TYPE_OBJECT_GOD:

		return "gui_god";

	default:

		return "Undefined Object!";
	}
}



#endif