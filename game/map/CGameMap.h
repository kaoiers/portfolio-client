//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/19
//
// File Name : CGameMap.h
// 
// 게임 맵 배치 세팅
// 
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_MAP_H
#define GAME_MAP_H



class CTerrainObject;
class CGameObjectManager;
class CGridSceneNode;
class CPathPlanner;
class CBoundaryManager;
class CGameRoomGod;
class CEnemyGenerator;
class CExplosionSystem;

#include "../common/UnCopyableUtil.h"


class CGameMap : private UnCopyable
{	
	//NavGraph*							m_pNavGraph;
	CGameObjectManager*					m_pObjMan;

	CTerrainObject*						m_pTerrain;

	CGridSceneNode*						m_pGrid;

	//CellSpace*						m_pSpacePartition;
	//PathManager<CPathPlanner>*		m_pPathManager;
	//CGameSectionManager*				m_pGameSectionManager;

	CBoundaryManager*					m_pBoundaryManager;
	CEnemyGenerator*					m_pEnemyGenerator;


	f32								m_dCellWidth, m_dCellHeight;
	f32								m_fTotalHeight, m_fTotalWidth;
	line3df								m_lselectedRect[4];	
	s32									m_iCellsX, m_iCellsZ;

	vector2di							m_vMinUsableTile, m_vMaxUsableTile;
	CGameRoomGod*						m_pGodRoom;
	double								m_dCellSpaceNeighborhoodRange;

	void								CreateGraph();
	void								CreateEnemyGenerator();
	void								PartitionNavGraph(const s32 x, const s32 y);
	void								DisplayObjects(u32	xOffset, u32	yOffset);
	void								DisplayObjectsByDepth(u32	xOffset, u32	yOffset, u32 depth);
	

public :

	CGameMap(CGameObjectManager* man) ;
	~CGameMap();

	bool								SectionInit(u32 tilesX, u32 tilesZ, f32 Height, f32 Width);
	bool								init(s32 cellsX, s32 cellsZ, s32 PartitionX,  s32 PartitionZ,  f32 cwidth  = 300.0f , f32 cheight = 300.0f);


	void								render();	
	void								update(const u32 timeMs) { };
	static CGameMap*					GetInstance();
	CBoundaryManager*					getBoundaryManager() {return m_pBoundaryManager; }
	bool								isPathObstructed(const vector3df& A, 
		const vector3df& B, f32 BoundingRadius) const;
	bool								isInBoundaries(const vector3df& point, s32 return_idx);
	bool								isWalkableWall(const u32 idx) { return true; };
	
	//일꾼, 신 죽었을 때 받는 이벤트
	void								GodDeadEvent();
	void								WorkerDeadEvent();
	void								removeAllTrees();

public :

	void								addExplosion(const vector3df& pos, const f32 scl);
	
	s32							getNumCellsX() const	{return m_iCellsX;}
	s32							getNumCellsZ() const	{return m_iCellsZ;}
	f32						getCellWidth() const	{ return m_dCellWidth; }
	f32						getCellHeight() const   { return m_dCellHeight; }

	const double&						GetCellSpaceNeighborhoodRange() {return m_dCellSpaceNeighborhoodRange;}

	bool								getNodePosFromMousePos(const vector3df& groundPoint, vector3df& tilePos);
	bool								IsNodePresent(const s32 x, const s32 y);
	bool								IsNodeAllLinked(const s32 x, const s32 y);
	bool								IsInUsableArea(const s32 x, const s32 y);

	vector3df							getTopLeftUsablePos() { return vector3df(0,0,0); };
	vector3df							getBottomRightUsablePos();
	CGameRoomGod*						getGodRoom() {	return m_pGodRoom; }
	CGameObjectManager*					getObjectManager() { return m_pObjMan; }
	void								StartEnemyGenerate(); 


	bool								RemoveNode(const s32 x, const s32 y);
	vector3df							getNodePos(const s32 x, const s32 y);
	vector3df							getPosByTile(const s32 x, const s32 y);
	vector2di							getTileFromPos(const vector3df& groundPoint);
	
	void								setOnebyOneBuildingNode(const s32 x, const s32 y) {};
	bool								LinkEdges(const vector2di a, const vector2di b) { return true; };
	bool								AddNodeByTile( const s32 x, const s32 y);

	bool								AddNodeAndLinkEdges(const s32 x, const s32 y);
	bool								AddNodeAndLinkEdgesForDoor(const s32 x, const s32 y, const vector3df& pos);
	void								AddNodeToCellSpace(const s32 x, const s32 y);

	s32									getNodeIndexFromTIle( const s32 x, const s32 y) const;
};

#endif