//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/04/06
//
// File Name : CGameUnitProduct.h
// 
// 자원 생산 클래스
// 
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_UNIT_PRODUCT_H
#define GAME_UNIT_PRODUCT_H



#include "../CAppContext.h"

class CGameUnitProduct
{

	CGameRoomWaiting*	m_pWaitingRoom;
	UnitTypes			m_CurrentUnitType;
	unsigned	int		m_uDestinationTime;	
	unsigned	int		m_uProductTIme;
	f32			m_fPercentage;

	void		CompleteProcessing();

public :

	void				BeginProcessing(const UnitTypes& Type);
	void				UpdateProcessing(const u32& Ms);
	void				CancelProcessing();
	const f32&		getPercentage() { return m_fPercentage; }

	bool				isOnProcessing() { return (m_uDestinationTime > 0); }
	

	CGameUnitProduct(CGameRoomWaiting* pRoom ) :m_pWaitingRoom(pRoom), m_CurrentUnitType(UNIT_COUNTS), m_uDestinationTime(0),m_uProductTIme(0),m_fPercentage(0) {}
	~CGameUnitProduct(){};
};


/*======================================================*/
// 유닛 생성시 처리
/*======================================================*/
inline void CGameUnitProduct::BeginProcessing( const UnitTypes& Type )
{
	m_CurrentUnitType = Type;
	

	m_uProductTIme *= 1000;

}


/*======================================================*/
// 유닛 생성과정 업데이트
/*======================================================*/
inline void CGameUnitProduct::UpdateProcessing( const u32& currentTime )
{
	if(m_uDestinationTime > 0)
	{
		if(currentTime >= m_uDestinationTime )
		{
			CompleteProcessing();

		}

		m_fPercentage =  f32(m_uDestinationTime - currentTime)/f32(m_uProductTIme); 		
	}

}


/*======================================================*/
// 프로세싱 완료시 처리
/*======================================================*/
inline void CGameUnitProduct::CompleteProcessing()
{
	m_pWaitingRoom->CreateArmy(m_CurrentUnitType);
	m_pWaitingRoom->HideProcessing();
	m_uDestinationTime = 0;
	m_uProductTIme = 0;
	m_fPercentage = 0.0f;
	m_CurrentUnitType = UNIT_COUNTS;
}


/*======================================================*/
// 유닛 생산 처리 중지하기
/*======================================================*/
inline void CGameUnitProduct::CancelProcessing()
{
	m_pWaitingRoom->HideProcessing();
	m_uDestinationTime = 0;
	m_uProductTIme = 0;
	m_fPercentage = 0.0f;
	m_CurrentUnitType = UNIT_COUNTS;
}


#endif