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

PluginManager * PluginManager::GetInstance()
{
	static std::unique_ptr<PluginManager> Instance = std::make_unique<PluginManager >();

    return Instance.get();
}


/*======================================================*/
// 모든 플러그인 불러오기
/*======================================================*/
void PluginManager::LoadPlugins ( const string & strDir )
{
    std::vector<string> filenames;
    GetFilenames(strDir, filenames);

    std::vector<std::string>::const_iterator it;
    for (it = filenames.begin(); it != filenames.end(); ++it)
    {
        const string & filename = *it;
        string & fullName = strDir + string("\\") + filename;
        LoadPlugin (fullName);
    }
}

/*======================================================*/
// 파일 이름 가져오기
/*======================================================*/
void PluginManager::GetFilenames ( const string & dir, 
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
bool PluginManager::LoadPlugin ( const string & filename )
{
    HMODULE hDll = ::LoadLibraryA (filename.c_str());
    if ( hDll == NULL )
    {
        LPSTR lpMsgBuf = nullptr;
        ::FormatMessageA( 
            FORMAT_MESSAGE_ALLOCATE_BUFFER | 
            FORMAT_MESSAGE_FROM_SYSTEM | 
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
            reinterpret_cast<LPSTR>(&lpMsgBuf),
            0,
            NULL 
        );

        if (lpMsgBuf) ::OutputDebugStringA(lpMsgBuf);

        LocalFree( lpMsgBuf );
        return false;
    }

	CREATEPLUGIN pFunc = (CREATEPLUGIN)::GetProcAddress (hDll, "CreatePlugin");
    if ( pFunc == NULL )
        return false;


    IPlugin * pPlugin = pFunc(*this);
    if ( pPlugin == NULL )
        return false;


    PluginInfo info;
    info.pPlugin = pPlugin;
    info.hDll    = hDll;

	m_mapPlugins[pPlugin->GetName()] = pPlugin;

	m_plugins.push_back(info);

    //MainFrame * pMainFrame = static_cast<MainFrame*>(::AfxGetMainWnd());
    //pMainFrame->AddExporter(pPlugin->GetExportName());
    return true;
}





/*======================================================*/
// 모든 플러그인 해제하기 
/*======================================================*/
void PluginManager::UnloadAll ( void )
{
//     MainFrame * pMainFrame = static_cast<MainFrame*>(::AfxGetMainWnd());

	std::vector<PluginInfo>::iterator it;
		for (it=m_plugins.begin(); it!=m_plugins.end(); ++it)
		{
			PluginInfo & info = *it;
	            
		   // pMainFrame->RemoveExporter(info.pPlugin->GetExportName());

			SAFE_DELETE(info.pPlugin);
			::FreeLibrary (info.hDll);
		}

	

    m_plugins.clear();
	m_mapPlugins.clear();
}



/*======================================================*/
//플러그인 갯수 가져오기
/*======================================================*/
size_t PluginManager::GetNumPlugins ( void ) const
{
    return m_plugins.size();
}


/*======================================================*/
// 플러그인 가져오기
/*======================================================*/
IPlugin * PluginManager::GetPlugin ( int nIndex )
{
    if ( nIndex < 0 || nIndex >= GetNumPlugins() )
        return NULL;

    return m_plugins[nIndex].pPlugin;
}


/*======================================================*/
// 플러그인 가져오기
/*======================================================*/
IPlugin * PluginManager::GetPlugin(std::string plugin_name )
{

 	PluginMap::iterator itr = m_mapPlugins.find(plugin_name);
// 
 	if(itr != m_mapPlugins.end())
 		return (itr->second);


	return NULL;

	
}

