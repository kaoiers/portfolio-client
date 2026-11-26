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


class IPlugin;
class God_Game;
class CSoundManager;



class PluginManager
{
	struct PluginInfo
	{
		IPlugin * pPlugin;
		HMODULE   hDll;
	};

	

	typedef std::map< std::string, IPlugin * > PluginMap;
	PluginMap					m_mapPlugins;
	std::vector<PluginInfo>		m_plugins;

public:

    static PluginManager * GetInstance(void);
	void LoadPlugins ( const std::string & strDir );
    void UnloadAll ( void );

    size_t GetNumPlugins ( void ) const;
    IPlugin * GetPlugin ( s32 nIndex );
	IPlugin * GetPlugin(std::string plugin_name );
	void GetFilenames(const std::string & dir, std::vector<std::string> & filenames) const;
	bool LoadPlugin(const std::string & filename);
};


#endif