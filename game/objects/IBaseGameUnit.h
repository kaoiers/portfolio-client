#pragma once

class CGameUnit;

/// 유닛 유형별 초기화와 공격 동작의 인터페이스를 정의한다.
class IBaseGameUnit
{
public:
    virtual bool shortAttack(CGameUnit* p_target) = 0;
    virtual void privateInitialize() = 0;

    IBaseGameUnit() {}
    virtual ~IBaseGameUnit() {}
};
