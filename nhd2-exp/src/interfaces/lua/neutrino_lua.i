/*
	$Id: neutrino_lua.i 20.01.2019 mohousch Exp $

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

%module neutrino
%{
#define SWIG_FILE_WITH_INIT
#include <gui/widget/messagebox.h>
%}

class CMessageBox
{
	protected:
		CWindow m_cBoxWindow;
		CWindow m_cTitleWindow;
		CWindow m_cBodyWindow;

		unsigned int m_currentPage;
		std::vector<int>m_startEntryOfPage;
		int m_maxEntriesPerPage;
		int m_pages;

		int m_width;
		int m_height;

		int m_fheight;
		int m_theight;

		std::string m_caption;
		char * m_message;
		ContentLines m_lines;
		std::string  m_iconfile;
		
		void refresh();

		void init(const char* const Caption, const int Width, const char * const Icon);

		bool has_scrollbar(void);
		void scroll_up(void);
		void scroll_down(void);

		void paint(void);
		void hide(void);

	private:
		uint32_t  showbuttons;
		bool returnDefaultOnTimeout;

		void paintButtons();

	public:
		enum result_
		{
			mbrYes    = 0,
			mbrNo     = 1,
			mbrCancel = 2,
			mbrBack   = 3,
			mbrOk     = 4
		} result;
	
		enum buttons_
		{
			mbYes= 0x01,
			mbNo = 0x02,
			mbCancel = 0x04,
			mbAll = 0x07,
			mbBack = 0x08,
			mbOk = 0x10,
			mbNone = 0x20
		} buttons;
	
		// Text & Caption are always UTF-8 encoded
		CMessageBox(const neutrino_locale_t Caption, const char * const Text, const int Width = MESSAGEBOX_WIDTH, const char * const Icon = NULL, const CMessageBox::result_ Default = mbrYes, const uint32_t ShowButtons = mbAll);
		CMessageBox(const neutrino_locale_t Caption, ContentLines& Lines, const int Width = MESSAGEBOX_WIDTH, const char * const Icon = NULL, const CMessageBox::result_ Default = mbrYes, const uint32_t ShowButtons = mbAll);
		CMessageBox(const char * const Caption, const char * const Text, const int Width = MESSAGEBOX_WIDTH, const char * const Icon = NULL, const CMessageBox::result_ Default = mbrYes, const uint32_t ShowButtons = mbAll);
		CMessageBox(const char * const Caption, ContentLines& Lines, const int Width = MESSAGEBOX_WIDTH, const char * const Icon = NULL, const CMessageBox::result_ Default = mbrYes, const uint32_t ShowButtons = mbAll);

		~CMessageBox(void);

		int exec(int timeout = -1);
		void returnDefaultValueOnTimeout(bool returnDefault);
};


