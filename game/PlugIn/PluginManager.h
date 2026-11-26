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
		IPlugin * p_plugin;
		HMODULE   h_dll;
	};

	

	typedef std::map< std::string, IPlugin * > PluginMap;
	PluginMap					m_map_plugins;
	std::vector<PluginInfo>		m_plugins;

public:

    static PluginManager * getInstance(void);
	void loadPlugins ( const std::string & str_dir );
    void unloadAll ( void );

    size_t getNumPlugins ( void ) const;
    IPlugin * getPlugin ( s32 n_index );
	IPlugin * getPlugin(std::string plugin_name );
	void getFilenames(const std::string & dir, std::vector<std::string> & filenames) const;
	bool loadPlugin(const std::string & filename);
};


#endif