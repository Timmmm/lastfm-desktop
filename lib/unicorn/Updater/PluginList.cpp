#include "PluginList.h"
#include <QStringList>

QList<IPluginInfo*> 
PluginList::availablePlugins() const
{
    QList<IPluginInfo*> ret;
    foreach( IPluginInfo* plugin, *this ) {
        if( plugin->isInstalled() ||
            !plugin->isPlatformSupported() ) continue;
        if( plugin->isAppInstalled() )
            ret << plugin;
    }
    return ret;
}

QList<IPluginInfo*> 
PluginList::installedPlugins() const
{
    QList<IPluginInfo*> ret;
    foreach( IPluginInfo* plugin, *this ) {
        if( plugin->isInstalled())
            ret << plugin;
    }
    return ret;
}

QList<IPluginInfo*>
PluginList::bootstrappablePlugins() const
{
    QList<IPluginInfo*> ret = installedPlugins();
    foreach( IPluginInfo* plugin, ret ) {
        if( !plugin->canBootstrap())
            ret.removeAll( plugin );
    }
    return ret;
}

PluginList 
PluginList::supportedList() const
{
    PluginList that( *this );
    foreach( IPluginInfo* i, that ) {
        if( !i->isPlatformSupported()) that.removeAll( i );
    }
    return that;
}

QString
PluginList::availableDescription() const
{
    QStringList mediaPlayers;
    
    foreach( IPluginInfo* i, supportedList() )
    {
        mediaPlayers << QString::fromStdString( i->name() );
    }

    QString ret = mediaPlayers.takeLast();
    
    if( mediaPlayers.count() > 0 )
        ret = mediaPlayers.join( ", " ) + " or " + ret;

    return ret;
}