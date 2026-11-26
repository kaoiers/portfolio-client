//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/08/08
//
// File Name : PluginManager.cpp
// 
// 플러그인 관리
// 
//////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "PluginManager.h"
#include "Plugin.h"
#include "../CAppContext.h"
#include <io.h>

using namespace std;

PluginManager * PluginManager::getInstance()
{
	static std::unique_ptr<PluginManager> instance = std::make_unique<PluginManager >();

    return instance.get();
}


/*======================================================*/
// 모든 플러그인 불러오기
/*======================================================*/
void PluginManager::loadPlugins ( const string & str_dir )
{
    std::vector<string> filenames;
    getFilenames(str_dir, filenames);

    std::vector<std::string>::const_iterator it;
    for (it = filenames.begin(); it != filenames.end(); ++it)
    {
        const string & filename = *it;
        string & full_name = str_dir + string("\\") + filename;
        loadPlugin (full_name);
    }
}

/*======================================================*/
// 파일 이름 가져오기
/*======================================================*/
void PluginManager::getFilenames ( const string & dir, 
                                  std::vector<string> & filenames ) const
{
    string mask = dir + string("\\*.plug");

    struct _finddata_t fileinfo;
    intptr_t handle = ::_findfirst(mask.c_str(), &fileinfo);
	intptr_t file   = handle;

	while (file >= 0)
	{
        filenames.push_back(string(fileinfo.name));
        file = ::_findnext(handle, &fileinfo);
	}

    ::_findclose(handle);
}

/*======================================================*/
// 플러그인 불러오기
/*======================================================*/
bool PluginManager::loadPlugin ( const string & filename )
{
    HMODULE h_dll = ::LoadLibraryA (filename.c_str());
    if ( h_dll == NULL )
    {
        LPSTR lp_msg_buf = nullptr;
        ::FormatMessageA( 
            FORMAT_MESSAGE_ALLOCATE_BUFFER | 
            FORMAT_MESSAGE_FROM_SYSTEM | 
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
            reinterpret_cast<LPSTR>(&lp_msg_buf),
            0,
            NULL 
        );

        if (lp_msg_buf) ::OutputDebugStringA(lp_msg_buf);

        LocalFree( lp_msg_buf );
        return false;
    }

	CREATEPLUGIN p_func = (CREATEPLUGIN)::GetProcAddress (h_dll, "CreatePlugin");
    if ( p_func == NULL )
        return false;


    IPlugin * p_plugin = p_func(*this);
    if ( p_plugin == NULL )
        return false;


    PluginInfo info;
    info.p_plugin = p_plugin;
    info.h_dll    = h_dll;

	m_map_plugins[p_plugin->GetName()] = p_plugin;

	m_plugins.push_back(info);

    return true;
}





/*======================================================*/
// 모든 플러그인 해제하기 
/*======================================================*/
void PluginManager::unloadAll ( void )
{

	std::vector<PluginInfo>::iterator it;
		for (it=m_plugins.begin(); it!=m_plugins.end(); ++it)
		{
			PluginInfo & info = *it;
	            

			SAFE_DELETE(info.p_plugin);
			::FreeLibrary (info.h_dll);
		}

	

    m_plugins.clear();
	m_map_plugins.clear();
}



/*======================================================*/
//플러그인 갯수 가져오기
/*======================================================*/
size_t PluginManager::getNumPlugins ( void ) const
{
    return m_plugins.size();
}


/*======================================================*/
// 플러그인 가져오기
/*======================================================*/
IPlugin * PluginManager::getPlugin ( s32 n_index )
{
    if ( n_index < 0 || n_index >= getNumPlugins() )
        return NULL;

    return m_plugins[n_index].p_plugin;
}


/*======================================================*/
// 플러그인 가져오기
/*======================================================*/
IPlugin * PluginManager::getPlugin(std::string plugin_name )
{

 	PluginMap::iterator itr = m_map_plugins.find(plugin_name);
// 
 	if(itr != m_map_plugins.end())
 		return (itr->second);


	return NULL;

	
}

