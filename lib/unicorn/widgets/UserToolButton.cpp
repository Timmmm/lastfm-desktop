/*
   Copyright 2005-2009 Last.fm Ltd. 
      - Primarily authored by Jono Cole and Doug Mansell

   This file is part of the Last.fm Desktop Application Suite.

   lastfm-desktop is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   lastfm-desktop is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with lastfm-desktop.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "UserToolButton.h"
#include <QApplication>

#include <QToolButton>
#include <lastfm/User>
#include "lib/unicorn/widgets/UserMenu.h"

using namespace lastfm;

UserToolButton::UserToolButton()
{
    setIconSize( QSize( 32, 32 ));
    setCheckable( true );

    if( unicorn::Settings().userRoster().count() > 1 ) {
        setMenu( new UserMenu());
        setPopupMode( QToolButton::MenuButtonPopup );
    }

    connect( this, SIGNAL( toggled( bool )), window(), SLOT( toggleProfile( bool )));
    connect( qApp, SIGNAL( sessionChanged( unicorn::Session, unicorn::Session )), SLOT( onSessionChanged()));
    connect( qApp, SIGNAL( gotUserInfo( lastfm::UserDetails )), SLOT( onUserGotInfo( lastfm::UserDetails )));
    connect( qApp, SIGNAL( rosterUpdated()), SLOT( onRosterUpdated()));
}

void 
UserToolButton::onSessionChanged()
{
    setIcon( QIcon());
}

void 
UserToolButton::onUserGotInfo( const UserDetails& user )
{
    connect( lastfm::nam()->get(QNetworkRequest( user.mediumImageUrl())), SIGNAL( finished()),
                                                                          SLOT( onImageDownloaded()));
}

void 
UserToolButton::onImageDownloaded()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>( sender());
    Q_ASSERT( reply);

    QImage img = QImage::fromData( reply->readAll());    
    setIcon( QIcon(QPixmap::fromImage( img)));
}

void 
UserToolButton::onRosterUpdated()
{
    if( unicorn::Settings().userRoster().count() > 1 ) {
        setMenu( new UserMenu());
        setPopupMode( QToolButton::MenuButtonPopup );
        setStyle( QApplication::style());
    } else {
        setPopupMode( QToolButton::DelayedPopup );
        menu()->deleteLater();
        setStyle( QApplication::style());
    }
}
