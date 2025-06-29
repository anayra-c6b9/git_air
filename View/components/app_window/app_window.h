#ifndef APP_WINDOW_H
#define APP_WINDOW_H

using uint = unsigned int;

namespace AppComponent{
    	class AppWindow{
				private:
						uint max_win_width;
						uint max_win_height;
						uint menu_bar_height = 3;
				public:
						AppWindow(){
							menu_bar_height = 3;
							max_win_width = 78;
							max_win_height = 23;
						}
						// functions to change window dimensions
						// when window is resized
						void setAppWinWidth(int width);
						void setAppWinHeight(int height);
						void setSectionHeight(int height);
						uint getAppWinWidth();
						uint getAppWinHeight();
						uint getMenuBarHeight();
						uint getMainBodyHeight();
						void setWindowSize();
    	};
}

#endif
