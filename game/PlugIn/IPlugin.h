#pragma once

#include <string>

/// DLL 플러그인이 구현해야 하는 초기화, 종료 및 내보내기 계약을 정의한다.
class IPlugin
{
public:
    virtual ~IPlugin() {};

    virtual bool Initialize() = 0;
    virtual bool Shutdown() = 0;
    virtual void About() = 0;

    virtual const std::string & GetName() = 0;
    virtual const std::string & GetExportName() = 0;

    virtual bool Export( const char * p_data) = 0;
};
