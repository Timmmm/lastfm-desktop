#ifndef WINAMP_PLUGIN_INFO_H_
#define WINAMP_PLUGIN_INFO_H_

#include "../../lib/unicorn/Updater/IPluginInfo.h"
#include "../../lib/DllExportMacro.h"

class UNICORN_DLLEXPORT WinampPluginInfo : public IPluginInfo
{
public:
    std::string name() const { return "Winamp"; }
    Version minVersion() const { return Version(); }
    Version maxVersion() const { return Version(); }
    
    std::string pluginPath() const { return std::string( "plugins" ); }
    std::string displayName() const { return std::string( "MPlayer2" ); }
    std::string processName() const { return std::string( "winamp.exe" ); }

    std::string id() const { return "wa2"; }
    BootstrapType bootstrapType() const { return PluginBootstrap; }
    bool isPlatformSupported() const
    {
        #ifdef WIN32
            return true;
        #endif
        return false;
    }

    IPluginInfo* clone() const { return new WinampPluginInfo( *this ); }

#ifdef QT_VERSION
    std::tstring pluginInstallPath() const
    {
    #ifdef Q_OS_WIN
	return programFilesX86().append(L"\\WA5\\Plugins");
    #endif 
        Q_ASSERT( !"There is no winamp on non-windows platforms!" );
        return std::tstring();
    }
#endif

};

#endif //WINAMP_PLUGIN_INFO_H_

