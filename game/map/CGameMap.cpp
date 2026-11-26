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
m_obj_man(man),
m_terrain(0),
m_grid(0),
m_cell_width(0), 
m_cell_height(0),
m_total_width(0),
m_total_height(0),
m_cells_x(0),
m_cells_z(0),
m_cell_space_neighborhood_range(0),
m_boundary_manager(0),
m_enemy_generator(0),
m_min_usable_tile(vector2di(0,0)), 
m_max_usable_tile(vector2di(0,0))
{


}

CGameMap::~CGameMap()
{	
	SAFE_DELETE(m_enemy_generator);
}


/*======================================================*/
// 게임 배치 초기화
/*======================================================*/
bool CGameMap::init( s32 cells_x, s32 cells_z, s32 partition_x,  s32 partition_z, f32 cwidth /*= 300.0f */, f32 cheight /*= 300.0f*/ )
{
	m_cells_x = cells_x;
	m_cells_z = cells_z;

	m_cell_width = cwidth;
	m_cell_height = cheight;

	m_total_height = m_cells_z * m_cell_height;
	m_total_width = m_cells_x * m_cell_width;
	m_cell_space_neighborhood_range = (m_cell_height + m_cell_width) /2.0;


	

	m_terrain = m_obj_man->addTerrainMap(object_mine, m_cells_x, m_cells_z, m_cell_width, m_cell_height);	


	
	createGraph();
	partitionNavGraph( partition_x,  partition_z);	
	displayObjectsByDepth(15, 30, 3);



	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	//신전 배치
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	CGameObjectManager*  obj_man =   CGameObjectManager::getInstance();
	CGameRoom* p_room = 0;			
	p_room = obj_man->addRoomOnTile(object_mine, BUILDING_GOD, vector2di(28, 31));



	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	//캐릭터 배치
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	obj_man->addUnit(object_mine, 0, UNIT_WORKER1 , this->getNodePos(35,35) );

	obj_man->addUnit(object_mine, 0, UNIT_GOD_TIGER , this->getNodePos(29,35));

	return true;
}



/*======================================================*/
// 적군 생성기 만들기
/*======================================================*/
void CGameMap::createEnemyGenerator()
{
	if(m_enemy_generator)
	{
		SAFE_DELETE(m_enemy_generator);
		m_enemy_generator = NULL;
	}

	m_enemy_generator =	new CEnemyGenerator(this, 5, 4, 2);


}

/*======================================================*/
// 나무와 바위 배치하기
/*======================================================*/
void CGameMap::displayObjectsByDepth( u32 x_offset, u32 y_offset, u32 depth )
{


	m_min_usable_tile = vector2di(x_offset,y_offset);
	m_max_usable_tile = vector2di(m_cells_x-x_offset-1, m_cells_z-y_offset-1);

	s32 god_room_x = s32(f32(m_min_usable_tile.X + m_max_usable_tile.X)/2.0f);
	s32 god_room_z = m_min_usable_tile.Y+2;

	
	createEnemyGenerator(); //순서유의


 	CCameraManager*	camera_man = CAppContext::getGodGame()->getCameraManager();
 	vector3df topleftpos(getPosByTile(m_min_usable_tile.X , m_min_usable_tile.Y));
 	vector3df bottomrightpos(getPosByTile(m_max_usable_tile.X , m_max_usable_tile.Y));
 	camera_man->setBoundary(vector2df(topleftpos.X, topleftpos.Z), 
 		vector2df(bottomrightpos.X, bottomrightpos.Z));

	for(u32 i=0; i<depth; i++)
	{
		displayObjects(x_offset-i, y_offset-i);
	}
}



/*======================================================*/
// 웨이브 시작하기
/*======================================================*/
void CGameMap::startEnemyGenerate()
{

	m_enemy_generator->setStartWave();

}

/*======================================================*/
// 바위 나무 배치하기
/*======================================================*/
void CGameMap::displayObjects( u32 x_offset, u32 y_offset)
{


}


/*======================================================*/
// 길찾기용 그래프 생성하기 
/*======================================================*/
void CGameMap::createGraph()
{

}


/*======================================================*/
// 렌더링
/*======================================================*/
void CGameMap::render()
{

// 		GraphHelper_DrawUsingGDI<NavGraph>(*m_pNavGraph, driver);



}

CGameMap * CGameMap::getInstance()
{
	return CAppContext::getGodGame()->getGameMap();
}



/*======================================================*/
// 네비게이션 그래프 파티션으로 나누기
/*======================================================*/
void CGameMap::partitionNavGraph(const s32 x, const s32 y)
{

}





/*======================================================*/
// 섹션 초기화
/*======================================================*/
bool CGameMap::sectionInit( u32 tiles_x, u32 tiles_z, f32 height, f32 width )
{

	return true;
}



/*======================================================*/
// 마우스 포지션 -> 가까운 노드 포지션
/*======================================================*/
bool CGameMap::getNodePosFromMousePos( const vector3df& ground_point, vector3df& tile_pos )
{

	vector2di tile = getTileFromPos(ground_point);

	tile_pos = getPosByTile(tile.X, tile.Y);

	return true;
}



/*======================================================*/
// 포지션 -> 타일 인덱스
/*======================================================*/
vector2di CGameMap::getTileFromPos( const vector3df& ground_point )
{
	vector2di tile;

	tile.X =  s32(ceil((ground_point.X + (m_total_width/2.0f)) /m_cell_width)) - 1 ;

	tile.Y =  -s32(ceil((ground_point.Z - (m_total_height/2.0f)) /m_cell_height)) ;

	return tile;
}


/*======================================================*/
// 노드 존재하는지
/*======================================================*/
bool CGameMap::isNodePresent( const s32 x, const s32 y )
{
	s32 node_index = getNodeIndexFromTile(x, y) ;

	return false;
}



/*======================================================*/
// 유효 지역에 있는지
/*======================================================*/
bool CGameMap::isInUsableArea( const s32 x, const s32 y )
{
	return (m_min_usable_tile.X < x && m_min_usable_tile.Y < y 
		&& m_max_usable_tile.X > x && m_max_usable_tile.Y > y  );
}



/*======================================================*/
// 노드에 링크가 다 연결되어 있는지
/*======================================================*/
bool CGameMap::isNodeAllLinked( const s32 x, const s32 y )
{
	s32	total_linked_edges_number = 0;

	s32 to = getNodeIndexFromTile(x, y);

	for(s32 i=-1; i<=1; i++)
	{
		for(s32 j=-1; j<=1; j++)
		{
			s32 node_x = x+j;
			s32 node_z = y+i;

			if(node_x < 0 || node_z < 0) continue;

			if(node_x >= m_cells_x || node_z >= m_cells_z) continue;

			if( (abs(i) == 1 && abs(j) == 1) || (i==0 && j==0) ) continue;

			s32 from = getNodeIndexFromTile(node_x, node_z) ;
		}
	}

	if(total_linked_edges_number == 1)
	{
		return false;
	}

	return true;
}



/*======================================================*/
// 노드 삭제하기
/*======================================================*/
bool CGameMap::removeNode( const s32 x, const s32 y )
{
	s32 idx = y*m_cells_x+x;
	
	return true;
}


/*======================================================*/
// 노드 포지션 가져오기
/*======================================================*/
vector3df CGameMap::getNodePos( const s32 x, const s32 y )
{
	s32 node_index = y*m_cells_x+x;

	return vector3df(0,0,0);
}





/*======================================================*/
// 타일 인덱스로 노드 추가하기 
/*======================================================*/
bool CGameMap::addNodeByTile( const s32 x, const s32 y)
{
	s32 idx = y*m_cells_x+x;

	return true;
}



/*======================================================*/
// 타일 인데스-> 포지션
/*======================================================*/
vector3df CGameMap::getPosByTile( const s32 x, const s32 y )
{
	vector3df pos;

	pos.X = -(m_total_width/2.0f) + (x* m_cell_width) + (m_cell_width/2.0f);
	pos.Y = 0.0f;
	pos.Z = (m_total_height/2.0f) - (y* m_cell_height) - (m_cell_height/2.0f);

	return pos;
}


/*======================================================*/
// 노드 추가하고 엣지 연결하기
/*======================================================*/
bool CGameMap::addNodeAndLinkEdges( const s32 x, const s32 y )
{	
	addNodeByTile(x, y);

	vector2di tile_a(x, y);

	for(s32 i=-1; i<=1; i++)
	{
		for(s32 j=-1; j<=1; j++)
		{
			s32 node_x = x+j;
			s32 node_z = y+i;

			if(node_x < 0 || node_z < 0) continue;

			if(node_x >= m_cells_x || node_z >= m_cells_z) continue;

			if( (abs(i) == 1 && abs(j) == 1) || (i==0 && j==0) ) continue;

			if(isNodePresent( node_x , node_z ))
			{
				vector2di tile_b(node_x, node_z);
				linkEdges(tile_a, tile_b);				
			}
		}
	}

	return true;
}


/*======================================================*/
// 노드 추가하고 엣지 연결하기 
/*======================================================*/
bool CGameMap::addNodeAndLinkEdgesForDoor( const s32 x, const s32 y, const vector3df& pos)
{
	s32 idx = y*m_cells_x+x;

	vector2di tile_a(x, y);

	for(s32 i=-1; i<=1; i++)
	{
		for(s32 j=-1; j<=1; j++)
		{
			s32 node_x = x+j;
			s32 node_z = y+i;

			if(node_x < 0 || node_z < 0) continue;

			if(node_x >= m_cells_x || node_z >= m_cells_z) continue;

			if( (abs(i) == 1 && abs(j) == 1) || (i==0 && j==0) ) continue;

			if(isNodePresent( node_x , node_z ))
			{
				vector2di tile_b(node_x, node_z);
				linkEdges(tile_a, tile_b);				
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
								 f32    bounding_radius) const
{
 

  return false;
}



/*======================================================*/
// 건물 안에 있는지
/*======================================================*/
bool CGameMap::isInBoundaries( const vector3df& point,s32 return_idx )
{
	return false;
}


/*======================================================*/
// 셀에 노드 추가하기
/*======================================================*/
void CGameMap::addNodeToCellSpace( const s32 x, const s32 y )
{
	s32 node_index = y*m_cells_x+x;
}



/*======================================================*/
// 타일 인덱스 -> 노드 인덱스
/*======================================================*/
s32 CGameMap::getNodeIndexFromTile( const s32 x, const s32 y ) const
{
	return y*m_cells_x+x;

}





/*======================================================*/
// 게임 가능 지역 오른쪽 하위 모서리 포지션 가져오기 
/*======================================================*/
vector3df CGameMap::getBottomRightUsablePos()
{
	return getPosByTile(m_max_usable_tile.X , m_max_usable_tile.Y);
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
void CGameMap::godDeadEvent()
{
}


/*======================================================*/
// 일꾼 부활 처리기 작동시키기
/*======================================================*/
void CGameMap::workerDeadEvent()
{
}