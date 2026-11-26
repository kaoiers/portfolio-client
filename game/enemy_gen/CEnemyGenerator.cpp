//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/10/02
//
// File Name : CEnemyGenerator.cpp
// 
// 적군 생성기
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include <time.h>
#include "CEnemyGenerator.h"
#include "../objects/CGameObjectManager.h"
#include "../objects/CGameRoomGod.h"
#include "../objects/CGameUnitEnemy.h"
#include "../interfaces/CMainGameGUI.h"
#include "../map/CGameMap.h"



/*======================================================*/
// 초기화
/*======================================================*/
void CEnemyGenerator::Initialize()
{

}





/*======================================================*/
// 적군 생성하기
/*======================================================*/
CGameUnitEnemy* CEnemyGenerator::GenerateEnemy()
{
	s32 DIstanceOffset = s32(m_lEnemyGenerateLine.getLength());

	DIstanceOffset = rand() % DIstanceOffset;
		 
 	vector3df GeneratePos = m_lEnemyGenerateLine.start + 
		(vector3df(1,0,0) * f32(DIstanceOffset) );

	GeneratePos.Y = 0.0f;

		CGameUnitEnemy*	pEnemy = m_pGameMap->getObjectManager()->AddUnitEnemy(GeneratePos, this);
	 
		vector3df vDestination = vector3df(0, 0, 
			m_pGameMap->getTopLeftUsablePos().Z);

		pEnemy->AddGoal_MoveToPosition(vDestination);

		m_pEnemy = pEnemy;


	return NULL;	
}



CEnemyGenerator::CEnemyGenerator(CGameMap * pMap, const u32 EnemyGeneratePeriod, const u32 EnemyApperPeriod, const u32 EnemyMaxCounts) 
	: m_pGameMap(pMap)
{
		srand((s32)time(NULL));

		vector3df tl = m_pGameMap->getTopLeftUsablePos();
		vector3df br = m_pGameMap->getBottomRightUsablePos();

		m_lEnemyGenerateLine.start = vector3df(tl.X, 0.0f, br.Z);
		m_lEnemyGenerateLine.end = vector3df(br.X, 0.0f, br.Z);
}

CEnemyGenerator::~CEnemyGenerator()
{

}







/*======================================================*/
// 적군 생성 중인지
/*======================================================*/
bool CEnemyGenerator::isInGenerate()
{
	return (!m_bCompleteWave);
}




/*======================================================*/
// 적군 죽음 추가
/*======================================================*/
void CEnemyGenerator::addDeadCount()
{
	m_uDeadEnemies--;	

	if(m_uDeadEnemies == 0)
	{
		m_bCompleteWave = true;

	}
}