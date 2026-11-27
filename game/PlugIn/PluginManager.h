//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/08/08
//
// File Name : PluginManager.h
//
// 플러그인 관리
//
//////////////////////////////////////////////////////////////////////////

#ifndef PLUGINMANAGER_H_
#define PLUGINMANAGER_H_

#include "../../basicType.h"
#include "IPlugin.h"
#include <windows.h>
#include <map>
#include <memory>
#include <type_traits>
#include <vector>

class God_Game;
class CSoundManager;

/// 플러그인 DLL 로딩, 등록, 조회 및 해제를 관리한다.
class PluginManager
{
    struct ModuleDeleter
    {
        void operator()(HMODULE module) const noexcept;
    };

    using Module = std::unique_ptr<std::remove_pointer_t<HMODULE>, ModuleDeleter>;

    /// 로드된 DLL 핸들과 플러그인 인스턴스의 연결 정보를 보관한다.
    struct PluginInfo
    {
        // Members are destroyed in reverse order, so the DLL outlives its plugin.
        Module module;
        std::unique_ptr<IPlugin> plugin;
    };

    typedef std::map< std::string, IPlugin * > PluginMap;
    PluginMap m_map_plugins;
    std::vector<PluginInfo> m_plugins;

public:
    static PluginManager * getInstance(void);
    void loadPlugins ( const std::string & str_dir);
    void unloadAll ( void);

    size_t getNumPlugins ( void) const;
    IPlugin * getPlugin ( s32 n_index);
    IPlugin * getPlugin(std::string plugin_name);
    void getFilenames(const std::string & dir, std::vector<std::string> & filenames) const;
    bool loadPlugin(const std::string & filename);
};

#endif
