
//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/02/22
//
// File Name : EnumPickingType.cpp
// 
// 피킹 상태 열거형 상수
// 
//////////////////////////////////////////////////////////////////////////


#ifndef PICKING_ENUMERATION
#define PICKING_ENUMERATION

enum {
	
	
	ID_IsNotPickable = 0,

	IDFlag_IsPickable,


	IDFlag_IsBuildingPickable,


	IDFlag_IsTerrainPickable,

	IDFlag_IsHighlightable

};

#endif
