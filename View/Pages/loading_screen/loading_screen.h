#ifndef LOADING_SCREEN_H
#define LOADING_SCREEN_H

#include <string>
#include "../../components/page/page.h"
// #include "../../components/app/app.h"
#include <thread>

using uint = unsigned int;

namespace AppPages{
	
	class LoadingScreen: public AppComponent::Page{
		private:
			bool is_active = false;
			static constexpr size_t pause_time_size = 100;
			const uint pause_time[pause_time_size] = {
				10, 5, 5, 5, 5, 5, 5, 10, 100, 30, // 175 ms
				5, 20, 10, 10, 100, 10, 10, 10, 150, 
				10, 10, 10, 10, 10 , 10, 10, 10, 100, 10,
				10, 10, 10, 10, 10 , 10, 10, 10, 10, 10,
				10, 10, 10, 10, 10 , 10, 180, 10, 10, 10,
				10, 10, 10, 100, 10 , 10, 10, 10, 10, 10,
				10, 10, 10, 10, 10 , 10, 100, 10, 10, 10,
				100, 10, 10, 10, 10 , 10, 10, 10, 10, 10,
				10, 10, 10, 10, 10 , 10, 10, 10, 10, 100,
				10, 10, 10, 10, 10 , 10, 100, 10, 550, 50,
			};
		    std::atomic<short> loaded{0};
			std::thread loading_thread;

			void pauseTime();

		public:
			LoadingScreen() {
				hasFooter = false;
				is_active = true;
				loading_thread = std::thread(&LoadingScreen::pauseTime, this);
			}

			void display() override;
            void handleInput(int ch, AppComponent::App * app) override;
            void navigateToNext();
			void clearValues() override;

			~LoadingScreen(){
				is_active = false;
				try {
					if (loading_thread.joinable()) {
						loading_thread.join();
					}
				} catch (const std::system_error& ex) {
					// std::cerr << "[Join Error] " << ex.what() << std::endl;
				}
			}
	};

}

#endif
