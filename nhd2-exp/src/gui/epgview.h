/*
	Neutrino-GUI  -   DBoxII-Project
	
	$Id: epgview.h 15.01.2019 mohousch Exp $

	Copyright (C) 2001 Steffen Hehn 'McClean'
	Homepage: http://dbox.cyberphoria.org/

	Kommentar:

	Diese GUI wurde von Grund auf neu programmiert und sollte nun vom
	Aufbau und auch den Ausbaumoeglichkeiten gut aussehen. Neutrino basiert
	auf der Client-Server Idee, diese GUI ist also von der direkten DBox-
	Steuerung getrennt. Diese wird dann von Daemons uebernommen.


	License: GPL

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/


#ifndef __epgview__
#define __epgview__

#include <vector>
#include <string>

#include <driver/framebuffer.h>
#include <driver/rcinput.h>
#include <driver/fontrenderer.h>
#include <system/settings.h>

#include <gui/color.h>

#include <gui/widget/menue.h>
#include <gui/widget/headers.h>

#include <sectionsdclient/sectionsdclient.h>


#define BIG_FONT_FAKTOR 1.5

class CEpgData
{
	private:
		CFrameBuffer* frameBuffer;

		CBox cFrameBox;
		CBox cHeadBox;
		CBox cFootBox;
		CBox cFollowScreeningBox;
		CBox cScrollBar;

		CHeaders headers;

		int sb;
		int medlineheight;
		int medlinecount;

		CChannelEventList evtlist;
		CEPGData epgData;

		std::string epg_date;
		std::string epg_start;
		std::string epg_end;
		int epg_done;
		
		bool bigFonts;

		uint64_t prev_id;
		time_t prev_zeit;
		uint64_t next_id;
		time_t next_zeit;

		int emptyLineCount, info1_lines;
		int textCount;
		std::vector<std::string> epgText;

		void GetEPGData(const t_channel_id channel_id, uint64_t id, time_t* startzeit, bool clear = true);
		void GetPrevNextEPGData( uint64_t id, time_t* startzeit );
		void addTextToArray( const std::string& text );
		void processTextToArray(std::string text);
		void showText( int startPos, int ypos );
		bool hasFollowScreenings(const t_channel_id channel_id, const std::string & title);
		int FollowScreenings(const t_channel_id channel_id, const std::string & title);
		void showTimerEventBar(bool show);
		void showHead(const t_channel_id channel_id);

		//
		uint32_t sec_timer_id;
	public:

		CEpgData();
		void start();
		int show(const t_channel_id channel_id, uint64_t id = 0, time_t * startzeit = NULL, bool doLoop = true );
		void hide();
};

class CEPGDataHandler : public CMenuTarget
{
	public:
		int exec(CMenuTarget* parent,  const std::string& actionKey);
};

#endif

