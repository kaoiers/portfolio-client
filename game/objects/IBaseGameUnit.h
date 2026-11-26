#pragma once

class CGameUnit;

class IBaseGameUnit
{
public :

	virtual		bool							short_attack(CGameUnit* pTarget) = 0;
	virtual		void							PrivateInitialize() = 0;

	IBaseGameUnit() {}
	virtual  ~IBaseGameUnit() {}
};
