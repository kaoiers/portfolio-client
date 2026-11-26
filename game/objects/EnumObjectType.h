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





inline std::string GetLuaFileFromProductType(int productType)
{
	switch(productType)
	{
		case PRODUCT_GOLD : 
			
			return "scripts/Products/ProductGold.lua";

		case PRODUCT_WHEAT : 

			return "scripts/Products/ProductWheat.lua";

		case PRODUCT_BARLEY : 

			return "scripts/Products/ProductBarley.lua";

		case PRODUCT_WILLOW : 

			return "scripts/Products/ProductWillow.lua";

		case PRODUCT_WALNUT : 

			return "scripts/Products/Productwalnut.lua";

		case PRODUCT_SILVER : 

			return "scripts/Products/ProductSilver.lua";

		case PRODUCT_BRONZE : 

			return "scripts/Products/ProductBronze.lua";

		default:

			return "Undefined Object!";

	}

}



inline std::string GetLuaFileFromGameUnits(int unittype)
{
	switch(unittype)
	{

	case UNIT_WORKER1:

		return "scripts/Objects/Worker1.lua";

	case UNIT_GOD_TIGER:

		return "scripts/Objects/Tiger.lua";


	case UNIT_TEST_DWARF :

		return "scripts/Objects/Dwarf.lua";


	case UNIT_ARMY_BUNNY :

		return "scripts/Objects/ArmyBunny.lua";

	case UNIT_ARMY_NAPOLEON :

		return "scripts/Objects/ArmyNapoleon.lua";

	case UNIT_ARMY_TIGER :

		return "scripts/Objects/ArmyTiger.lua";

	case UNIT_ENEMY_SOLDIER:

		return "scripts/Objects/Soldier1.lua";

	default:

		return "Undefined Object!";
	}
}

inline std::string GetLuaFileFromBuildingType(int buildingtype)
{
	switch(buildingtype)
	{

	case BUILDING_TRAP:

		return "scripts/Objects/BuildingTrap.lua";

	case BUILDING_GOD:

		return "scripts/Objects/BuildingGodRoom.lua";

	case BUILDING_TOWER:

		return "scripts/Objects/BuildingTower.lua";

	
	case BUILDING_JAIL:

		return "scripts/Objects/BuildingJail.lua";

	case BUILDING_WAREHOUSE:

		return "scripts/Objects/BuildingWareHouse.lua";

	case BUILDING_WAITINGROOM:

		return "scripts/Objects/BuildingWaitingRoom.lua";

	case BUILDING_FARM : 

		return "scripts/Objects/BuildingFarm.lua";

	case BUILDING_GOLD :

		 return "scripts/Objects/BuildingGold.lua";


	case BUILDING_WOOD :

		return  "scripts/Objects/BuildingWood.lua";

	case BUILDING_FRIEND :

		return  "scripts/Objects/BuildingFriend.lua";

	default:

		return "Undefined Object!";
	}
}



#endif