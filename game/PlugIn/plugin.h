//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/08/08
//
// File Name : plugin.h
// 
// 플러그인 인터페이스 클래스
// 
//////////////////////////////////////////////////////////////////////////



#ifndef IPLUGIN_H_
#define IPLUGIN_H_



#include "IPlugin.h"
#ifdef PLUGIN_EXPORTS
#define PLUGINDECL __declspec(dllexport)
#else
#define PLUGINDECL __declspec(dllimport)
#endif


class PluginManager;


typedef IPlugin * (* CREATEPLUGIN)(PluginManager&mgr);

extern "C" PLUGINDECL IPlugin * CreatePlugin(PluginManager & mgr);


#endif  // IPLUGIN_H_
