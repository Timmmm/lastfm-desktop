/***************************************************************************
 *   Copyright 2005-2008 Last.fm Ltd.                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *    This program is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Steet, Fifth Floor, Boston, MA  02110-1301, USA.          *
 ***************************************************************************/

#ifndef NOW_PLAYING_TUNER_H
#define NOW_PLAYING_TUNER_H

#include "ui_NowPlayingTuner.h"
#include <QWidget>

class NowPlayingTuner :public QWidget
{
	Q_OBJECT
	
public:
	NowPlayingTuner();
	
private:
	Ui::NowPlayingTuner ui;
	
	/** Note the QListWidget must have a StationDelegate class set as the delegate
	 otherwise this will break. Should probably fix this at some point. */
	void addWeightedStringsToList( class WeightedStringList& stringList, QListWidget* list );
	
private slots:
	void onTunerReturnPressed();
	void onAppEvent( int, const QVariant& );
	
	void onFetchedTopTags( class WsReply* );
	void onFetchedSimilarArtists( WsReply* r );
	
	void onTagClicked( QListWidgetItem* );
	void onArtistClicked( QListWidgetItem* );
	
signals:
	void tune( const class RadioStation& );
};

#endif //NOW_PLAYING_TUNER_H