/*
	$Id: listbox.h 2018.08.19 mohousch Exp $


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

#if !defined(LISTBOX_H_)
#define LISTBOX_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string>
#include <vector>

#include <driver/framebuffer.h>

#include <gui/widget/textbox.h>
#include <gui/widget/widget_helpers.h>
#include <gui/widget/widget.h>



extern CLocaleManager		*g_Locale;
//extern CFont* g_Font[FONT_TYPE_COUNT];

// item type
enum 
{
	ITEM_TYPE_OPTION_CHOOSER,
	ITEM_TYPE_OPTION_NUMBER_CHOOSER,
	ITEM_TYPE_OPTION_STRING_CHOOSER,
	ITEM_TYPE_OPTION_LANGUAGE_CHOOSER,
	ITEM_TYPE_SEPARATOR,
	ITEM_TYPE_FORWARDER,
	ITEM_TYPE_LOCKED_FORWARDER,
	ITEM_TYPE_LISTBOXITEM
};

enum
{
	WIDGET_TYPE_STANDARD = 0,
	WIDGET_TYPE_CLASSIC,
	WIDGET_TYPE_EXTENDED,
	WIDGET_TYPE_FRAME
};

enum 
{
	MODE_MENU = 0,
	MODE_SETUP,
	MODE_LISTBOX
};

enum
{
	FOOT_INFO_MODE = 0,
	FOOT_HINT_MODE
};

// line separator
enum
{
	EMPTY =	0,
	LINE = 1,
	STRING = 2,
	ALIGN_CENTER = 4,
	ALIGN_LEFT = 8,
	ALIGN_RIGHT = 16
};

typedef struct keyval
{
	int key;
	neutrino_locale_t value;
	char* valname;
} keyval_struct;

// CChangeObserver
class CChangeObserver
{
	public:
		virtual ~CChangeObserver(){}
		virtual bool changeNotify(const neutrino_locale_t, void *)
		{
			return false;
		}

		virtual bool changeNotify(const std::string&, void *)
		{
			return false;
		}
};

// CMenuItem
class CMenuItem
{
	protected:
		int x, y, dx, offx;
		
	public:
		bool active;
		bool marked;
		neutrino_msg_t directKey;
		neutrino_msg_t msg;
		bool can_arrow;
		std::string iconName;
		std::string itemName;
		std::string option;
		std::string optionInfo;
		std::string itemHelpText;
		std::string itemIcon;
		std::string info1, option_info1;
		std::string info2, option_info2;

		//
		std::string icon1;
		std::string icon2;
		int number;
		int runningPercent;

		//
		int itemType;
		int widgetType;
		int widgetMode;
		bool isPlugin;

		//
		int item_height;
		int item_width;

		//
		//static CFont* nameFont;
		//static CFont* optionFont;

		bool nLinesItem; // 2 lines Item (classicWidget)

		CMenuTarget *jumpTarget;
		std::string actionKey;

		CMenuItem();
		virtual ~CMenuItem(){};

		virtual void init(const int X, const int Y, const int DX, const int OFFX);
		virtual int paint(bool selected = false, bool AfterPulldown = false) = 0;
		virtual int getHeight(void) const = 0;
		virtual int getWidth(void) const
		{
			return 0;
		}

		virtual bool isSelectable(void) const {return false;}

		virtual int exec(CMenuTarget */*parent*/) {return 0;}
		
		//
		virtual void setActive(const bool Active);
		virtual void setMarked(const bool Marked);

		//
		virtual int getYPosition(void) const { return y; }
		virtual int getItemType(){ return itemType;};

		//
		virtual void setOption(const char* text){option = text;};
		virtual void setOptionInfo(const char* text){optionInfo = text;};

		//
		virtual void setInfo1(const char* const text){info1 = text;};
		virtual void setInfo2(const char* const text){info2 = text;};
		virtual void setOptionInfo1(const char* const text){option_info1 = text;};
		virtual void setOptionInfo2(const char* const text){option_info2 = text;};

		//
		virtual void setHelpText(const char* const Text){itemHelpText =  Text;};
		virtual void setHelpText(const neutrino_locale_t locale){itemHelpText = g_Locale->getText(locale); };

		//
		virtual void setIconName(const char* const icon){iconName = icon;};
		virtual void setItemIcon(const char* const icon){itemIcon = icon;};

		//
		virtual void setIcon1(const char* const icon){icon1 = icon;};
		virtual void setIcon2(const char* const icon){icon2 = icon;};
		virtual void setNumber(int nr){number = nr;};
		virtual void setPercent(int percent = -1){runningPercent = percent;};

		//virtual void setNameFont(CFont* font = g_Font[SNeutrinoSettings::FONT_TYPE_MENU]){nameFont = font;};
		//virtual void setOptionFont(CFont* font = g_Font[SNeutrinoSettings::FONT_TYPE_CHANNELLIST_NUMBER]){optionFont = font;};

		virtual void set2lines(void){nLinesItem = true;};
		virtual void setWidgetType(int type){widgetType = type;};
		virtual void setWidgetMode(int mode){widgetMode = mode;};

		//
		virtual void setDirectKey(neutrino_msg_t key){directKey = key;};
		virtual void setActionKey(CMenuTarget *Target, const char *const ActionKey){jumpTarget = Target; actionKey = ActionKey;};
};

// CMenuOptionChooser
class CMenuOptionChooser : public CMenuItem
{
	protected:
		neutrino_locale_t optionName;
		int height;
		int * optionValue;

		int getHeight(void) const
		{
			return height;
		}
		
		bool isSelectable(void) const
		{
			return active;
		}

	private:
		const struct keyval* options;
		unsigned number_of_options;
		CChangeObserver* observ;
		
		std::string optionNameString;
		
		bool pulldown;

	public:
		CMenuOptionChooser(const neutrino_locale_t OptionName, int * const OptionValue, const struct keyval * const Options, const unsigned Number_Of_Options, const bool Active = false, CChangeObserver * const Observ = NULL, const neutrino_msg_t DirectKey = RC_nokey, const std::string & IconName= "", bool Pulldown = false);
		CMenuOptionChooser(const char* const OptionName, int * const OptionValue, const struct keyval * const Options, const unsigned Number_Of_Options, const bool Active = false, CChangeObserver * const Observ = NULL, const neutrino_msg_t DirectKey = RC_nokey, const std::string & IconName= "", bool Pulldown = false);

		~CMenuOptionChooser(){};

		void setOptionValue(const int newvalue);
		int getOptionValue(void) const;

		int paint(bool selected, bool AfterPulldown = false);

		int exec(CMenuTarget *parent);
};

// CMenuOptionNumberChooser
class CMenuOptionNumberChooser : public CMenuItem
{
	const char* optionString;

	int lower_bound;
	int upper_bound;

	int display_offset;

	int localized_value;
	neutrino_locale_t localized_value_name;
	
	std::string nameString;
	neutrino_locale_t name;

	protected:
		neutrino_locale_t optionName;
		int height;
		int* optionValue;

		int getHeight(void) const
		{
			return height;
		}
		
		bool isSelectable(void) const
		{
			return active;
		}

	private:
		CChangeObserver * observ;

	public:
		CMenuOptionNumberChooser(const neutrino_locale_t Name, int * const OptionValue, const bool Active, const int min_value, const int max_value, CChangeObserver * const Observ = NULL, const int print_offset = 0, const int special_value = 0, const neutrino_locale_t special_value_name = NONEXISTANT_LOCALE, const char * non_localized_name = NULL);
		CMenuOptionNumberChooser(const char * const Name, int * const OptionValue, const bool Active, const int min_value, const int max_value, CChangeObserver * const Observ = NULL, const int print_offset = 0, const int special_value = 0, const neutrino_locale_t special_value_name = NONEXISTANT_LOCALE, const char * non_localized_name = NULL);

		~CMenuOptionNumberChooser(){};
		
		int paint(bool selected, bool AfterPulldown = false);

		int exec(CMenuTarget *parent);
};

// CMenuOptionStringChooser
class CMenuOptionStringChooser : public CMenuItem
{
	std::string nameString;
	neutrino_locale_t name;
	int height;
	char * optionValue;
	std::vector<std::string> options;
	CChangeObserver * observ;
	bool pulldown;

	public:
		CMenuOptionStringChooser(const neutrino_locale_t Name, char* OptionValue, bool Active = false, CChangeObserver* Observ = NULL, const neutrino_msg_t DirectKey = RC_nokey, const std::string & IconName= "", bool Pulldown = false);
		CMenuOptionStringChooser(const char * Name, char * OptionValue, bool Active = false, CChangeObserver* Observ = NULL, const neutrino_msg_t DirectKey = RC_nokey, const std::string & IconName= "", bool Pulldown = false);
		~CMenuOptionStringChooser();

		void addOption(const char * value);

		int paint(bool selected, bool AfterPulldown = false);
		int getHeight(void) const {return height;}

		bool isSelectable(void) const {return active;}

		int exec(CMenuTarget* parent);
};

// CMenuOptionLanguageChooser
class CMenuOptionLanguageChooser : public CMenuItem
{
	int height;
	char * optionValue;
	std::vector<std::string> options;
	CChangeObserver * observ;

	public:
		CMenuOptionLanguageChooser(char *Name, CChangeObserver *Observ = NULL, const char *const IconName = NULL);
		~CMenuOptionLanguageChooser();

		void addOption(const char* value);

		int paint(bool selected, bool AfterPulldown = false);
		int getHeight(void) const {return height;}

		bool isSelectable(void) const {return true;}

		int exec(CMenuTarget * parent);
};

// CMenuSeparator
class CMenuSeparator : public CMenuItem
{
	int type;

	public:
		const char * textString;

		CMenuSeparator(const int Type = EMPTY, const char * const Text = NULL);
		~CMenuSeparator(){};

		int paint(bool selected = false, bool AfterPulldown = false);
		int getHeight(void) const;
		int getWidth(void) const;

		virtual const char * getString(void);
};

// CMenuForwarder
class CMenuForwarder : public CMenuItem
{
	//
	std::string optionValueString;

	protected:
		std::string textString;
		neutrino_locale_t text;

		virtual const char *getName(void);
		virtual const char *getOption(void);
	public:

		CMenuForwarder(const neutrino_locale_t Text, const bool Active = true, const char * const Option = NULL, CMenuTarget* Target = NULL, const char* const ActionKey = NULL, const neutrino_msg_t DirectKey = RC_nokey, const char* const IconName = NULL, const char* const ItemIcon = NULL, const neutrino_locale_t HelpText = NONEXISTANT_LOCALE );
		
		CMenuForwarder(const char* const Text, const bool Active = true, const char* const Option = NULL, CMenuTarget* Target = NULL, const char* const ActionKey = NULL, const neutrino_msg_t DirectKey = RC_nokey, const char* const IconName = NULL, const char* const ItemIcon = NULL, const neutrino_locale_t HelpText = NONEXISTANT_LOCALE );

		~CMenuForwarder(){};
		
		int paint(bool selected = false, bool AfterPulldown = false);
		int getHeight(void) const;
		int getWidth(void) const;

		int exec(CMenuTarget* parent);
		bool isSelectable(void) const {return active;}

		void setName(const char * const name){textString = name;};
};

// CPINProtection
class CPINProtection
{
	protected:
		char * validPIN;
		bool check();
		virtual CMenuTarget * getParent() = 0;
	public:
		CPINProtection( char *validpin){ validPIN = validpin;};
		virtual ~CPINProtection(){}
};

// CZapProtection
class CZapProtection : public CPINProtection
{
	protected:
		virtual CMenuTarget * getParent() { return( NULL);};
	public:
		int fsk;

		CZapProtection(char * validpin, int FSK) : CPINProtection(validpin){ fsk = FSK; };
		~CZapProtection(){};
		bool check();
};

// CLockedMenuForwarder
class CLockedMenuForwarder : public CMenuForwarder, public CPINProtection
{
	CMenuTarget * Parent;
	bool AlwaysAsk;

	protected:
		virtual CMenuTarget* getParent(){ return Parent;};
	public:
		CLockedMenuForwarder(const neutrino_locale_t Text, char * _validPIN, bool alwaysAsk = false, const bool Active = true, char * Option = NULL, CMenuTarget * Target = NULL, const char * const ActionKey = NULL, neutrino_msg_t DirectKey = RC_nokey, const char * const IconName = NULL, const char * const ItemIcon = NULL, const neutrino_locale_t HelpText = NONEXISTANT_LOCALE )
		 : CMenuForwarder(Text, Active, Option, Target, ActionKey, DirectKey, IconName, ItemIcon, HelpText) ,
		   CPINProtection( _validPIN){AlwaysAsk = alwaysAsk;};
		   
		CLockedMenuForwarder(const char * const Text, char * _validPIN, bool alwaysAsk = false, const bool Active = true, char * Option = NULL, CMenuTarget * Target = NULL, const char * const ActionKey = NULL, neutrino_msg_t DirectKey = RC_nokey, const char * const IconName = NULL, const char * const ItemIcon = NULL, const neutrino_locale_t HelpText = NONEXISTANT_LOCALE )
		 : CMenuForwarder(Text, Active, Option, Target, ActionKey, DirectKey, IconName, ItemIcon, HelpText) ,
		   CPINProtection( _validPIN){AlwaysAsk = alwaysAsk;};

		virtual int exec(CMenuTarget* parent);
};

// CMenulistBoxItem
class ClistBoxItem : public CMenuItem
{
	std::string optionValueString;

	protected:
		//
		neutrino_locale_t text;
		std::string textString;

		//
		virtual const char *getName(void);
		virtual const char *getOption(void);

	public:
		ClistBoxItem(const neutrino_locale_t Text, const bool Active = true, const char* const Option = NULL, CMenuTarget * Target = NULL, const char* const ActionKey = NULL, const neutrino_msg_t DirectKey = RC_nokey, const char* const Icon = NULL, const char* const ItemIcon = NULL);

		ClistBoxItem(const char* const Text, const bool Active = true, const char* const Option = NULL, CMenuTarget * Target = NULL, const char* const ActionKey = NULL, const neutrino_msg_t DirectKey = RC_nokey, const char* const IconName = NULL, const char* const ItemIcon = NULL);
		
		~ClistBoxItem(){};
		
		int paint(bool selected = false, bool AfterPulldown = false);
		int getHeight(void) const;
		int getWidth(void) const;

		int exec(CMenuTarget* parent);
		bool isSelectable(void) const {return active;}
};

//
class ClistBox : public CWidgetItem
{
	public:
		std::vector<CMenuItem*>	items;
	private:
		CFrameBuffer* frameBuffer;

		CBox cFrameBox;
		CBox cFrameFootInfo;

		int selected;

		//
		std::vector<unsigned int> page_start;
		unsigned int current_page;
		unsigned int total_pages;
		int item_height;
		int item_width;
		int sb_width;
		int listmaxshow;
		int iconOffset;
		int pos;
		unsigned int item_start_y;
		int items_height;
		int items_width;

		CScrollBar scrollBar;

		//
		bool enableCenter;
		bool shrinkMenu;

		// frame
		int itemsPerX;
		int itemsPerY;
		int maxItemsPerPage;

		// widget type
		int widgetType;
		int widgetMode;
		bool widgetChange;
		std::vector<int> widget;
		int cnt;

		// head
		std::string iconfile;
		std::string l_name;
		int hheight;
		fb_pixel_t headColor;
		int headRadius;
		int headCorner;
		int headGradient;
		int hbutton_count;
		button_label_list_t hbutton_labels;
		bool paintDate;
		bool paintTitle;
		bool logo;

		// foot
		int fheight;
		fb_pixel_t footColor;
		int footRadius;
		int footCorner;
		int footGradient;
		int fbutton_count;
		int fbutton_width;
		button_label_list_t fbutton_labels;
		bool paint_Foot;

		// footInfo
		int footInfoHeight;
		CItems2DetailsLine itemsLine;
		int connectLineWidth;
		bool paintFootInfo;
		int footInfoMode;

		// methods
		virtual void paintItems();

		//
		int full_height;
		int full_width;
		int start_x;
		int start_y;

		fb_pixel_t * background;
		bool savescreen;
		void saveScreen();
		void restoreScreen();

		CTextBox * textBox;

		std::string actionKey;

	public:
		ClistBox(const int x = 0, int const y = 0, const int dx = MENU_WIDTH, const int dy = MENU_HEIGHT);
		ClistBox(CBox* position);
		virtual ~ClistBox();

		void setPosition(const int x, const int y, const int dx, const int dy){cFrameBox.iX = x;
	cFrameBox.iY = y; cFrameBox.iWidth = dx; cFrameBox.iHeight = dy; full_height = dy; full_width = dx; start_x = x; start_y = y;};
		void setPosition(CBox* position){cFrameBox = *position; full_height = position->iHeight; full_width = position->iWidth; start_x = position->iX; start_y = position->iY;};

		virtual void addItem(CMenuItem * menuItem, const bool defaultselected = false);
		bool hasItem();
		void clearItems(void){items.clear(); current_page = 0;};
		void clearAll(void){items.clear(); hbutton_labels.clear(); fbutton_labels.clear(); widget.clear();current_page = 0;};
		void setSelected(unsigned int _new) { /*if(_new <= items.size())*/ selected = _new; };

		virtual void initFrames();
		virtual void paint();
		virtual void hide();
		virtual void paintHead();
		virtual void paintFoot();
		virtual void paintItemInfo(int pos);
		virtual void hideItemInfo();

		// head
		void enablePaintHead(){paintTitle = true;};
		void enablePaintDate(void){paintDate = true;};
		void setTitle(const char* title = "", const char* icon = NULL, bool logo_ok = false){l_name = title; if(icon != NULL) iconfile = icon; logo = logo_ok;};
		void setHeaderButtons(const struct button_label *_hbutton_label, const int _hbutton_count = 1);
		void setHeadColor(fb_pixel_t col) {headColor = col;};
		void setHeadCorner(int ra, int co){headRadius = ra; headCorner = co;};
		void setHeadGradient(int grad){headGradient = grad;};
		
		// foot
		void enablePaintFoot(){paint_Foot = true;};
		void setFooterButtons(const struct button_label *_fbutton_label, const int _fbutton_count = 1, const int _fbutton_width = 0);
		void setFootColor(fb_pixel_t col) {footColor = col;};
		void setFootCorner(int ra, int co){footRadius = ra; footCorner = co;};
		void setFootGradient(int grad){footGradient = grad;};

		// item footInfo
		void enablePaintFootInfo(int fh = 70){paintFootInfo = true; footInfoHeight = fh;};
		void setFootInfoMode(int mode = FOOT_INFO_MODE){footInfoMode = mode;};

		void enableCenterPos(){enableCenter = true;};
		void enableShrinkMenu(){shrinkMenu = true;};

		virtual void scrollLineDown(const int lines = 1);
		virtual void scrollLineUp(const int lines = 1);
		virtual void scrollPageDown(const int pages = 1);
		virtual void scrollPageUp(const int pages = 1);
		virtual void swipLeft();
		virtual void swipRight();

		int getItemsCount()const{return items.size();};
		int getCurrentPage()const{return current_page;};
		int getTotalPages()const{return total_pages;};
		int getSelected(){return selected;};
		inline CBox getWindowsPos(void){return(cFrameBox);};
		int getTitleHeight(){return hheight;};
		int getFootHeight(){return fheight;};
		int getItemHeight(){return item_height;};
		int getFootInfoHeight(){return footInfoHeight;};
		int getListMaxShow(void) const {return listmaxshow;};

		//
		void setItemsPerPage(int itemsX = 6, int itemsY = 3){itemsPerX = itemsX; itemsPerY = itemsY; maxItemsPerPage = itemsPerX*itemsPerY;};
		int getItemsPerX()const{return itemsPerX;};
		int getItemsPerY()const{return itemsPerY;};
		int getMaxItemsPerPage()const{return maxItemsPerPage;};

		// widget type|mode
		void setWidgetType(int type){widgetType = type; widget.push_back(widgetType);};
		int getWidgetType(){return widgetType;};
		void setWidgetMode(int mode){widgetMode = mode; if(widgetMode == MODE_SETUP) enableCenter = true;};
		void enableWidgetChange(){widgetChange = true;};
		void addWidget(int wtype){widget.push_back(wtype);};
		void changeWidgetType(int cnt = 0);

		//
		bool isSelectable(void){return true;};

		int oKKeyPressed(CMenuTarget *parent);

		//
		virtual void onHomeKeyPressed();
		virtual void onUpKeyPressed();
		virtual void onDownKeyPressed();
		virtual void onRightKeyPressed();
		virtual void onLeftKeyPressed();
		virtual void onPageUpKeyPressed();
		virtual void onPageDownKeyPressed();

		void enableSaveScreen();

		//
		std::string getName(){return l_name;};
		std::string getActionKey(void){return actionKey;};
};

#endif // LISTBOX_H_
