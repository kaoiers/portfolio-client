//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/03/08
//
// File Name : CGameRoomProduct.h
// 
// 자원 생산 클래스
// 
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_ROOM_PRODUCT_H
#define	GAME_ROOM_PRODUCT_H

#include <map>


#include "../attributes/GameResourceManager.h"
#include "../shader/CLightEffectManager.h"



class CGameRoomProduct
{
	CGameRoomProductBase*	m_pRoom;

	const f32									m_fStatusWidth, m_fStatusHeight, m_fBarWidth, m_fBarHeight;

	u32											m_uProductCompletedTime, m_uProductTime;

	ProductTypes								m_ProductType;


	bool										m_bProduced;
	
	void										assignTime(const u32 sec);
	void										SetCompletedEffect();




public :

	CGameRoomProduct(CGameRoomProductBase*	 pProductRoom)  : 
	   m_pRoom(pProductRoom), 
	   m_fStatusWidth(250), 
	   m_fStatusHeight(22),
	   m_fBarWidth(240),
	   m_fBarHeight(20),   
	   m_uProductCompletedTime(0),
	   m_uProductTime(0),
	   m_ProductType(PRODUCT_COUNTS),
	   m_bProduced(false)
	   
	{

 		


// 		scene::ISceneNode* node = m_pRoom->getSceneManager()->addSphereSceneNode();
// 		node->setParent(m_pRoom->GetSceneNode());
// 		node->setScale(vector3df(20,20,20));
// 		node->setPosition(m_pRoom->getHeightPos());
// 		node->setMaterialFlag(video::EMF_LIGHTING, false);
		//node->getMaterial(0).DiffuseColor = 
		//ShaderEffect->ApplyEffectToNode(node);
		
		
	}

	const		bool		isProduced() const { return m_bProduced; }
	void					setProduced(const bool pro) { m_bProduced = pro; } 

	f32						ProductProcessing();
	void					setProductToProcessing(ProductTypes type) { m_ProductType = type; }

	bool					isOnProduct() {	return		(m_uProductCompletedTime != 0); }

	void					TurnOnProcessing(ProductTypes type, const u32 sec);
	void					CompleteProcessing();
	void					CancelProcessing();



	~CGameRoomProduct() {};

	


};




/*======================================================*/
// 자원 생산 처리
/*======================================================*/
inline f32 CGameRoomProduct::ProductProcessing()
{
	
	return 0.0f;

}


/*======================================================*/
// 자원 생산 설정하기
/*======================================================*/
inline void CGameRoomProduct::TurnOnProcessing( ProductTypes type, const u32 sec  )
{
	setProductToProcessing(type);

	assignTime(sec);
}



/*======================================================*/
// 자원 생산 시간 설정하기
/*======================================================*/
inline void CGameRoomProduct::assignTime(const u32 sec )
{
	if(m_ProductType != PRODUCT_COUNTS)
	{

		
		
		//m_ProductStatus->setVisible(true);	
	}
}


/*======================================================*/
// 자원 생산 완료 처리
/*======================================================*/

inline void CGameRoomProduct::CompleteProcessing()
{
	m_uProductCompletedTime = 0;

	m_uProductTime = 0;

	m_ProductType = PRODUCT_COUNTS;

	m_bProduced = false;

	m_pRoom->CollectProductCompleteProcedure();


}


/*======================================================*/
// 처리 취소
/*======================================================*/
inline void CGameRoomProduct::CancelProcessing()
{

	m_uProductCompletedTime = 0;

	m_uProductTime = 0;

	m_ProductType = PRODUCT_COUNTS;
}



/*======================================================*/
// 처리효과 완료
/*======================================================*/
inline void CGameRoomProduct::SetCompletedEffect()
{

// 	scene::IParticleAffector* paf;
// 	paf = m_ParticleNode->createAttractionAffector(pos ,30.0f, true );
// 	m_ParticleNode->addAffector(paf);
// 	paf->drop();

	

}




#endif


