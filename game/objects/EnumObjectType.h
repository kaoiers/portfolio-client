#ifndef DEF_OBJTYPE
#define DEF_OBJTYPE

#include <string>

enum ONTILE_TYPE
{
	TILE_NOTHING = 0,
	TILE_BUILDING 
};


typedef enum 
{
	object_mine = 0xaa,
	object_frined	
	
}OwnerType;


enum OBJ_TYPE 
{
	GODTYPE_BUILDING = 1, 

	GODTYPE_UNIT,

	GODTYPE_BLOCK,

	GODTYPE_TERRAIN_MAP
};


typedef enum 
{
	BUILDING_JAIL = 0,

	BUILDING_TRAP,
	
	BUILDING_GOD,

	BUILDING_TOWER,
	
	BUILDING_WAREHOUSE,

	BUILDING_WAITINGROOM,

	BUILDING_FARM,

	BUILDING_GOLD,

	BUILDING_WOOD,

	BUILDING_FRIEND,

	BUILDING_COUNTS

}BuildingTypes ;

typedef enum 
{
	UNIT_TEST_DWARF = 0,
	

	UNIT_GOD_TIGER = 1,
	
	UNIT_WORKER1 = 2,
	
	UNIT_ENEMY_SOLDIER,
	

	UNIT_ARMY_BUNNY,

	UNIT_ARMY_NAPOLEON,

	UNIT_ARMY_TIGER,


	

	UNIT_COUNTS


}UnitTypes;


typedef enum 
{

	PRODUCT_GOLD = 0,

	PRODUCT_WHEAT,

	PRODUCT_BARLEY,

	PRODUCT_WILLOW,

	PRODUCT_WALNUT,

	PRODUCT_BRONZE,

	PRODUCT_SILVER,
	
	PRODUCT_COUNTS


}ProductTypes;



typedef enum  
{
	com_none = 0,
	com_building,
	com_collection,
	com_attack,
	com_room_guard
	//com_
	
}Command_Type;	

#endif