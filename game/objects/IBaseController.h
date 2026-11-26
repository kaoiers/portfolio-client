//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/22
//
// File Name : IBaseController.h
// 
// 오브젝트 컨트롤 인터페이스
// 
//////////////////////////////////////////////////////////////////////////


#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

class CEventHandler;




class IBaseController
{
	

public :

	virtual void	enter_control() = 0;
	virtual void	update_control(CEventHandler* pReceiver) = 0;
	virtual void	exit_control() = 0;	
	virtual	void	OnCommand() = 0;
	//virtual	void	update(const u32 timeMs) = 0;


	virtual ~IBaseController(){};
};



#endif