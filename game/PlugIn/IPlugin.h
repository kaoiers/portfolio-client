#pragma once

#include <string>

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
