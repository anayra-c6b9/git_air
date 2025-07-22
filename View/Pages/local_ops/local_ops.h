#ifndef LOCAL_OPS_H
#define LOCAL_OPS_H

#include <string>

#include "../../components/page/page.h"
#include "../auth/auth.h"
#include "../../../Model/local_repo/mlocal_repo.h"

using uint = unsigned int;

namespace AppPages{
	
	class LocalOpsPage: public AppComponent::Page{
		private:
            uint current_selection;
            bool has_pushed;
			bool is_push_touched;
            AppModels::LocalRepo *local_repo;
            enum Field{
                PUSH = 0,
                TOTAL_FIELDS = 1
            };
		public:
            bool hasRepos;
			LocalOpsPage() {
				current_selection = 0;
				hasFooter = true;
                has_pushed = false;
				is_push_touched = false;
			}

			void display() override;
            void handleInput(int ch, AppComponent::App *app) override ;
			void clearValues();
            bool pushCode();
			~LocalOpsPage(){
			}
	};

}

#endif