#pragma once

class CGameUnit;

class IBaseGameUnit
{
public :

	virtual		bool							shortAttack(CGameUnit* p_target) = 0;
	virtual		void							privateInitialize() = 0;

	IBaseGameUnit() {}
	virtual  ~IBaseGameUnit() {}
};
