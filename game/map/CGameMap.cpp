//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/19
//
// File Name : CGameMap.cpp
// 
// 게임 맵 배치 세팅
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>


#include "CGameMap.h"
#include "../objects/CGameObjectManager.h"
#include "../CAppContext.h"
#include "../shader/CLightEffectManager.h"

#include "../God_Game.h"
#include "../camera/CCameraManager.h"
#include "../enemy_gen/CEnemyGenerator.h"
#include "../interfaces/CMainGameGUI.h"


CGameMap::CGameMap(CGameObjectManager* man)
:	
m_pObjMan(man),
m_pTerrain(0),
m_pGrid(0),
m_dCellWidth(0), 
m_dCellHeight(0),
m_fTotalWidth(0),
m_fTotalHeight(0),
m_iCellsX(0),
m_iCellsZ(0),
m_dCellSpaceNeighborhoodRange(0),
m_pBoundaryManager(0),
m_pEnemyGenerator(0),
m_vMinUsableTile(vector2di(0,0)), 
m_vMaxUsableTile(vector2di(0,0))
{


}

CGameMap::~CGameMap()
{	
	SAFE_DELETE(m_pEnemyGenerator);
}


/*======================================================*/
// 게임 배치 초기화
/*======================================================*/
bool CGameMap::init( int cellsX, int cellsZ, int PartitionX,  int PartitionZ, float cwidth /*= 300.0f */, float cheight /*= 300.0f*/ )
{
	m_iCellsX = cellsX;
	m_iCellsZ = cellsZ;

	m_dCellWidth = cwidth;
	m_dCellHeight = cheight;

	m_fTotalHeight = m_iCellsZ * m_dCellHeight;
	m_fTotalWidth = m_iCellsX * m_dCellWidth;
	m_dCellSpaceNeighborhoodRange = (m_dCellHeight + m_dCellWidth) /2.0;


	

	m_pTerrain = m_pObjMan->AddTerrainMap(object_mine, m_iCellsX, m_iCellsZ, m_dCellWidth, m_dCellHeight);	


	
	CreateGraph();
	PartitionNavGraph( PartitionX,  PartitionZ);	
	DisplayObjectsByDepth(15, 30, 3);



	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	//신전 배치
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	CGameObjectManager*  objMan =   CGameObjectManager::GetInstance();
	CGameRoom* pRoom = 0;			
	pRoom = objMan->AddRoomOnTile(object_mine, BUILDING_GOD, vector2di(28, 31));



	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	//캐릭터 배치
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	objMan->AddUnit(object_mine, 0, UNIT_WORKER1 , this->getNodePos(35,35) );

	objMan->AddUnit(object_mine, 0, UNIT_GOD_TIGER , this->getNodePos(29,35));

	return true;
}



/*======================================================*/
// 적군 생성기 만들기
/*======================================================*/
void CGameMap::CreateEnemyGenerator()
{
	if(m_pEnemyGenerator)
	{
		SAFE_DELETE(m_pEnemyGenerator);
		m_pEnemyGenerator = NULL;
	}

	m_pEnemyGenerator =	new CEnemyGenerator(this, 5, 4, 2);


}

/*======================================================*/
// 나무와 바위 배치하기
/*======================================================*/
void CGameMap::DisplayObjectsByDepth( u32 xOffset, u32 yOffset, u32 depth )
{


	m_vMinUsableTile = vector2di(xOffset,yOffset);
	m_vMaxUsableTile = vector2di(m_iCellsX-xOffset-1, m_iCellsZ-yOffset-1);

	int godRoomX = int(float(m_vMinUsableTile.X + m_vMaxUsableTile.X)/2.0f);
	int godRoomZ = m_vMinUsableTile.Y+2;	

	
	CreateEnemyGenerator(); //순서유의


 	CCameraManager*	cameraMan = CAppContext::GetGodGame()->getCameraManager();
 	vector3df topleftpos(getPosByTile(m_vMinUsableTile.X , m_vMinUsableTile.Y));
 	vector3df bottomrightpos(getPosByTile(m_vMaxUsableTile.X , m_vMaxUsableTile.Y));
 	cameraMan->setBoundary(vector2df(topleftpos.X, topleftpos.Z), 
 		vector2df(bottomrightpos.X, bottomrightpos.Z));

	for(unsigned int i=0; i<depth; i++)
	{
		DisplayObjects(xOffset-i, yOffset-i);
	}
}



/*======================================================*/
// 웨이브 시작하기
/*======================================================*/
void CGameMap::StartEnemyGenerate()
{

	m_pEnemyGenerator->SetStartWave();

}

/*======================================================*/
// 바위 나무 배치하기
/*======================================================*/
void CGameMap::DisplayObjects( u32 xOffset, u32 yOffset)
{


}


/*======================================================*/
// 길찾기용 그래프 생성하기 
/*======================================================*/
void CGameMap::CreateGraph()
{

}


/*======================================================*/
// 렌더링
/*======================================================*/
void CGameMap::render()
{

// 	if(m_pNavGraph)
// 	{
// 		if (m_pNavGraph->NumNodes() == 0) return;		
// 		video::IVideoDriver* driver = CAppContext::GetDevice()->getSceneManager()->getVideoDriver();		 
// 		driver->setMaterial(m_pGrid->getMaterial(0));
// 		driver->setTransform(video::ETS_WORLD, m_pGrid->getAbsoluteTransformation());
// 		GraphHelper_DrawUsingGDI<NavGraph>(*m_pNavGraph, driver);
// 	}


	//if(m_pGrid) m_pGrid->render();

	//m_pShieldManager->drawAll();
}

CGameMap * CGameMap::GetInstance()
{
	return CAppContext::GetGodGame()->getGameMap();
}



/*======================================================*/
// 네비게이션 그래프 파티션으로 나누기
/*======================================================*/
void CGameMap::PartitionNavGraph(const int x, const int y)
{

	//m_pSpacePartition->RenderCells(CAppContext::GetDevice());
}





/*======================================================*/
// 섹션 초기화
/*======================================================*/
bool CGameMap::SectionInit( unsigned int tilesX, unsigned int tilesZ, float Height, float Width )
{

	return true;
}



/*======================================================*/
// 마우스 포지션 -> 가까운 노드 포지션
/*======================================================*/
bool CGameMap::getNodePosFromMousePos( const vector3df& groundPoint, vector3df& tilePos )
{

	vector2di tile = getTileFromPos(groundPoint);

	tilePos = getPosByTile(tile.X, tile.Y);

	return true;
}



/*======================================================*/
// 포지션 -> 타일 인덱스
/*======================================================*/
vector2di CGameMap::getTileFromPos( const vector3df& groundPoint )
{
	vector2di tile;

	tile.X =  int(ceil((groundPoint.X + (m_fTotalWidth/2.0f)) /m_dCellWidth)) - 1 ;

	tile.Y =  -int(ceil((groundPoint.Z - (m_fTotalHeight/2.0f)) /m_dCellHeight)) ;

	return tile;
}


/*======================================================*/
// 노드 존재하는지
/*======================================================*/
bool CGameMap::IsNodePresent( const int x, const int y )
{
	int NodeIndex = getNodeIndexFromTIle(x, y) ;

	return false;
}



/*======================================================*/
// 유효 지역에 있는지
/*======================================================*/
bool CGameMap::IsInUsableArea( const int x, const int y )
{
	return (m_vMinUsableTile.X < x && m_vMinUsableTile.Y < y 
		&& m_vMaxUsableTile.X > x && m_vMaxUsableTile.Y > y  );
}



/*======================================================*/
// 노드에 링크가 다 연결되어 있는지
/*======================================================*/
bool CGameMap::IsNodeAllLinked( const int x, const int y )
{
	int	TotalLinkedEdgesNumber = 0;

	int to = getNodeIndexFromTIle(x, y);

	for(int i=-1; i<=1; i++)
	{
		for(int j=-1; j<=1; j++)
		{
			int nodeX = x+j;
			int nodeZ = y+i;		

			if(nodeX < 0 || nodeZ < 0) continue;

			if(nodeX >= m_iCellsX || nodeZ >= m_iCellsZ) continue;

			if( (abs(i) == 1 && abs(j) == 1) || (i==0 && j==0) ) continue;

			int from = getNodeIndexFromTIle(nodeX, nodeZ) ;
		}
	}

	if(TotalLinkedEdgesNumber == 1)
	{
		return false;
	}

	return true;
}



/*======================================================*/
// 노드 삭제하기
/*======================================================*/
bool CGameMap::RemoveNode( const int x, const int y )
{
	int idx = y*m_iCellsX+x;
	
	return true;
}


/*======================================================*/
// 노드 포지션 가져오기
/*======================================================*/
vector3df CGameMap::getNodePos( const int x, const int y )
{
	int NodeIndex = y*m_iCellsX+x;

	return vector3df(0,0,0);
}





/*======================================================*/
// 타일 인덱스로 노드 추가하기 
/*======================================================*/
bool CGameMap::AddNodeByTile( const int x, const int y)
{
	int idx = y*m_iCellsX+x;

	return true;
}



/*======================================================*/
// 타일 인데스-> 포지션
/*======================================================*/
vector3df CGameMap::getPosByTile( const int x, const int y )
{
	vector3df pos;

	pos.X = -(m_fTotalWidth/2.0f) + (x* m_dCellWidth) + (m_dCellWidth/2.0f);
	pos.Y = 0.0f;
	pos.Z = (m_fTotalHeight/2.0f) - (y* m_dCellHeight) - (m_dCellHeight/2.0f);

	return pos;
}


/*======================================================*/
// 노드 추가하고 엣지 연결하기
/*======================================================*/
bool CGameMap::AddNodeAndLinkEdges( const int x, const int y )
{	
	AddNodeByTile(x, y);

	vector2di tileA(x, y);

	for(int i=-1; i<=1; i++)
	{
		for(int j=-1; j<=1; j++)
		{
			int nodeX = x+j;
			int nodeZ = y+i;		

			if(nodeX < 0 || nodeZ < 0) continue;

			if(nodeX >= m_iCellsX || nodeZ >= m_iCellsZ) continue;

			if( (abs(i) == 1 && abs(j) == 1) || (i==0 && j==0) ) continue;

			if(IsNodePresent( nodeX , nodeZ ))
			{
				vector2di tileB(nodeX, nodeZ);
				LinkEdges(tileA, tileB);				
			}
		}
	}

	return true;
}


/*======================================================*/
// 노드 추가하고 엣지 연결하기 
/*======================================================*/
bool CGameMap::AddNodeAndLinkEdgesForDoor( const int x, const int y, const vector3df& pos)
{
	int idx = y*m_iCellsX+x;

	vector2di tileA(x, y);

	for(int i=-1; i<=1; i++)
	{
		for(int j=-1; j<=1; j++)
		{
			int nodeX = x+j;
			int nodeZ = y+i;		

			if(nodeX < 0 || nodeZ < 0) continue;

			if(nodeX >= m_iCellsX || nodeZ >= m_iCellsZ) continue;

			if( (abs(i) == 1 && abs(j) == 1) || (i==0 && j==0) ) continue;

			if(IsNodePresent( nodeX , nodeZ ))
			{
				vector2di tileB(nodeX, nodeZ);
				LinkEdges(tileA, tileB);				
			}
		}
	}

	return true;
}



/*======================================================*/
// 장애물이 있는지
/*======================================================*/
bool CGameMap::isPathObstructed(const vector3df& A,
                                 const vector3df& B,
								 f32    BoundingRadius) const
{
 

  return false;
}



/*======================================================*/
// 건물 안에 있는지
/*======================================================*/
bool CGameMap::isInBoundaries( const vector3df& point,int return_idx )
{
	return false;
}


/*======================================================*/
// 셀에 노드 추가하기
/*======================================================*/
void CGameMap::AddNodeToCellSpace( const int x, const int y )
{
	int NodeIndex = y*m_iCellsX+x;
}



/*======================================================*/
// 타일 인덱스 -> 노드 인덱스
/*======================================================*/
int CGameMap::getNodeIndexFromTIle( const int x, const int y ) const
{
	return y*m_iCellsX+x;

}





/*======================================================*/
// 게임 가능 지역 오른쪽 하위 모서리 포지션 가져오기 
/*======================================================*/
vector3df CGameMap::getBottomRightUsablePos()
{
	return getPosByTile(m_vMaxUsableTile.X , m_vMaxUsableTile.Y);
}


/*======================================================*/
// 특정 지역에 폭발 효과
/*======================================================*/
void CGameMap::addExplosion( const vector3df& pos, const f32 scl )
{
	
}



/*======================================================*/
// 깔린 나무들 모두 지우기
/*======================================================*/
void CGameMap::removeAllTrees()
{

}

/*======================================================*/
// 신수 부활 처리기 작동시키기
/*======================================================*/
void CGameMap::GodDeadEvent()
{
	//CMainGameGUI::GetInstance()->WarningMessage(L"신수가 30초 후에 부활합니다");
	//m_pGodResurrection->begin(30);
}


/*======================================================*/
// 일꾼 부활 처리기 작동시키기
/*======================================================*/
void CGameMap::WorkerDeadEvent()
{
	//CMainGameGUI::GetInstance()->WarningMessage(L"일꾼이 30초 후에 부활합니다");
	//m_pWorkerResurrection->begin(30);
}