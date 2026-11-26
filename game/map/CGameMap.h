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


	float								m_dCellWidth, m_dCellHeight;
	float								m_fTotalHeight, m_fTotalWidth;
	line3df								m_lselectedRect[4];	
	int									m_iCellsX, m_iCellsZ;

	vector2di							m_vMinUsableTile, m_vMaxUsableTile;
	CGameRoomGod*						m_pGodRoom;
	double								m_dCellSpaceNeighborhoodRange;

	void								CreateGraph();
	void								CreateEnemyGenerator();
	void								PartitionNavGraph(const int x, const int y);
	void								DisplayObjects(u32	xOffset, u32	yOffset);
	void								DisplayObjectsByDepth(u32	xOffset, u32	yOffset, u32 depth);
	

public :

	CGameMap(CGameObjectManager* man) ;
	~CGameMap();

	bool								SectionInit(unsigned int tilesX, unsigned int tilesZ, float Height, float Width);
	bool								init(int cellsX, int cellsZ, int PartitionX,  int PartitionZ,  float cwidth  = 300.0f , float cheight = 300.0f);	


	void								render();	
	void								update(const u32 timeMs) { };
	static CGameMap*					GetInstance();
	CBoundaryManager*					getBoundaryManager() {return m_pBoundaryManager; }
	bool								isPathObstructed(const vector3df& A, 
		const vector3df& B, f32 BoundingRadius) const;
	bool								isInBoundaries(const vector3df& point, int return_idx);
	bool								isWalkableWall(const unsigned int idx) { return true; };
	
	//일꾼, 신 죽었을 때 받는 이벤트
	void								GodDeadEvent();
	void								WorkerDeadEvent();
	void								removeAllTrees();

public :

	void								addExplosion(const vector3df& pos, const f32 scl);
	
	int							getNumCellsX() const	{return m_iCellsX;}
	int							getNumCellsZ() const	{return m_iCellsZ;}
	float						getCellWidth() const	{ return m_dCellWidth; }
	float						getCellHeight() const   { return m_dCellHeight; }

	const double&						GetCellSpaceNeighborhoodRange() {return m_dCellSpaceNeighborhoodRange;}

	bool								getNodePosFromMousePos(const vector3df& groundPoint, vector3df& tilePos);
	bool								IsNodePresent(const int x, const int y);
	bool								IsNodeAllLinked(const int x, const int y);
	bool								IsInUsableArea(const int x, const int y);

	vector3df							getTopLeftUsablePos() { return vector3df(0,0,0); };
	vector3df							getBottomRightUsablePos();
	CGameRoomGod*						getGodRoom() {	return m_pGodRoom; }
	CGameObjectManager*					getObjectManager() { return m_pObjMan; }
	void								StartEnemyGenerate(); 


	bool								RemoveNode(const int x, const int y);
	vector3df							getNodePos(const int x, const int y);
	vector3df							getPosByTile(const int x, const int y);
	vector2di							getTileFromPos(const vector3df& groundPoint);
	
	void								setOnebyOneBuildingNode(const int x, const int y) {};
	bool								LinkEdges(const vector2di a, const vector2di b) { return true; };
	bool								AddNodeByTile( const int x, const int y);

	bool								AddNodeAndLinkEdges(const int x, const int y);
	bool								AddNodeAndLinkEdgesForDoor(const int x, const int y, const vector3df& pos);
	void								AddNodeToCellSpace(const int x, const int y);

	int									getNodeIndexFromTIle( const int x, const int y) const; 
};

#endif