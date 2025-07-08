# compiler
CXX = g++

# flags
## -I > includes the header files
## -Wall > enables all warnings
CXXFLAGS = \
		-std=c++17 -Wall -I. \
		-Icomponents/app_window \
		-Icomponents/base_component \
		-Icomponents/menu_bar \
		-Icomponents/text_with_label \
		-Icomponents/app \
		-Icomponents/page \
		-IPages/auth \
		-IPages/loading_screen \
		-Icolors
LDFLAGS =

#libraries
LIBS = -lncurses

# source files
SRCF =	\
	index.cpp \
	components/app_window/app_window.cpp \
	components/base_component/base_component.cpp \
	components/text_with_label/text_with_label.cpp \
	components/menu_bar/menu_bar.cpp \
	components/app/app.cpp \
	colors/color_pair.cpp \
	Pages/auth/auth.cpp \
	Pages/loading_screen/loading_screen.cpp \

# object files
OBJF = $(SRCF:.cpp=.o)

# output binary
TARGET = auth_app

# default make
all: $(TARGET)

# libraries
$(TARGET): $(OBJF)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

# object file maker
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean make
clean:
	rm -rf $(OBJF) $(TARGET)



