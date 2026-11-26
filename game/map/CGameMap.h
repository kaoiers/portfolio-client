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

#include "../common/UncopyableUtil.h"

class CGameMap : private UnCopyable
{
    CGameObjectManager* m_obj_man;

    CTerrainObject* m_terrain;

    CGridSceneNode* m_grid;

    CBoundaryManager* m_boundary_manager;
    CEnemyGenerator* m_enemy_generator;

    f32 m_cell_width, m_cell_height;
    f32 m_total_height, m_total_width;
    line3df m_selected_rect[4];
    s32 m_cells_x, m_cells_z;

    vector2di m_min_usable_tile, m_max_usable_tile;
    CGameRoomGod* m_god_room;
    double m_cell_space_neighborhood_range;

    void createGraph();
    void createEnemyGenerator();
    void partitionNavGraph(const s32 x, const s32 y);
    void displayObjects(u32 x_offset, u32 y_offset);
    void displayObjectsByDepth(u32 x_offset, u32 y_offset, u32 depth);

public:
    CGameMap(CGameObjectManager* man);
    ~CGameMap();

    bool sectionInit(u32 tiles_x, u32 tiles_z, f32 height, f32 width);
    bool init(s32 cells_x, s32 cells_z, s32 partition_x, s32 partition_z, f32 cwidth = 300.0f, f32 cheight = 300.0f);

    void render();
    void update(const u32 time_ms) { };
    static CGameMap* getInstance();
    CBoundaryManager* getBoundaryManager() { return m_boundary_manager; }
    bool isPathObstructed(const vector3df& A,
        const vector3df& B, f32 bounding_radius) const;
    bool isInBoundaries(const vector3df& point, s32 return_idx);
    bool isWalkableWall(const u32 idx) { return true; };

    //일꾼, 신 죽었을 때 받는 이벤트
    void godDeadEvent();
    void workerDeadEvent();
    void removeAllTrees();

public:
    void addExplosion(const vector3df& pos, const f32 scl);

    s32 getNumCellsX() const { return m_cells_x; }
    s32 getNumCellsZ() const { return m_cells_z; }
    f32 getCellWidth() const { return m_cell_width; }
    f32 getCellHeight() const { return m_cell_height; }

    const double& getCellSpaceNeighborhoodRange() { return m_cell_space_neighborhood_range; }

    bool getNodePosFromMousePos(const vector3df& ground_point, vector3df& tile_pos);
    bool isNodePresent(const s32 x, const s32 y);
    bool isNodeAllLinked(const s32 x, const s32 y);
    bool isInUsableArea(const s32 x, const s32 y);

    vector3df getTopLeftUsablePos() { return vector3df(0, 0, 0); };
    vector3df getBottomRightUsablePos();
    CGameRoomGod* getGodRoom() { return m_god_room; }
    CGameObjectManager* getObjectManager() { return m_obj_man; }
    void startEnemyGenerate();

    bool removeNode(const s32 x, const s32 y);
    vector3df getNodePos(const s32 x, const s32 y);
    vector3df getPosByTile(const s32 x, const s32 y);
    vector2di getTileFromPos(const vector3df& ground_point);

    void setOnebyOneBuildingNode(const s32 x, const s32 y) {};
    bool linkEdges(const vector2di a, const vector2di b) { return true; };
    bool addNodeByTile( const s32 x, const s32 y);

    bool addNodeAndLinkEdges(const s32 x, const s32 y);
    bool addNodeAndLinkEdgesForDoor(const s32 x, const s32 y, const vector3df& pos);
    void addNodeToCellSpace(const s32 x, const s32 y);

    s32 getNodeIndexFromTile( const s32 x, const s32 y) const;
};

#endif
