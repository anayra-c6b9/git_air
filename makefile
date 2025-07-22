# ──────────────────────────────────────────────────────────────────────────────
#  Compiler and flags
# ──────────────────────────────────────────────────────────────────────────────
CXX      := g++
INC_DIRS := -Iexternal -IController -IModel \
    -I/opt/homebrew/opt/cpr/include \
    -I/opt/homebrew/opt/nlohmann-json/include \
	-I/opt/homebrew/include \
	-IView/components/app_window \
	-IView/components/base_component \
	-IView/components/menu_bar \
	-IView/components/text_with_label \
	-IView/components/app \
	-IView/components/page \
	-IView/components/button_with_label \
	-IView/Pages/auth \
	-IView/Pages/loading_screen \
	-IView/colors
CXXFLAGS := -std=c++17 -mmacosx-version-min=15.0 -Wall -Wextra $(INC_DIRS)
# LDFLAGS := 

# Linker flags (add -lssl -lcrypto if your cpr/curl build is OpenSSL‑based)
LIBS     := -L/opt/homebrew/opt/cpr/lib -L/opt/homebrew/opt/curl/lib \
			-L/opt/homebrew/lib \
            -Wl,-rpath,/opt/homebrew/opt/cpr/lib \
            -Wl,-rpath,/opt/homebrew/opt/curl/lib \
			-Wl,-rpath,/opt/homebrew/lib \
            -lcpr -lcurl -lncurses -lgit2
LDFLAGS  := $(LIBS)

# ──────────────────────────────────────────────────────────────────────────────
#  Folders
# ──────────────────────────────────────────────────────────────────────────────
OBJ_DIR  := build
TARGET   := $(OBJ_DIR)/git_air

# ──────────────────────────────────────────────────────────────────────────────
#  Source ⇢ Object list
#     – Recursively find all .cpp, excluding View/*
#     – Re‑map each src file to build/<same‑path>.o
# ──────────────────────────────────────────────────────────────────────────────
SOURCES  := $(shell find . -type f -name '*.cpp') #-not -path './View/*'
OBJECTS  := $(patsubst ./%, $(OBJ_DIR)/%, $(SOURCES:.cpp=.o))

# ──────────────────────────────────────────────────────────────────────────────
#  Default target
# ──────────────────────────────────────────────────────────────────────────────
all: $(TARGET)

# ──────────────────────────────────────────────────────────────────────────────
#  Link – build/<…>/git_air_backend
# ──────────────────────────────────────────────────────────────────────────────
$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET)…"
	$(CXX) $^ -o $@ $(LDFLAGS)

# ──────────────────────────────────────────────────────────────────────────────
#  Compile each .cpp → build/…/.o
#     – Automatically create the build sub‑directory
# ──────────────────────────────────────────────────────────────────────────────
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<…"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ──────────────────────────────────────────────────────────────────────────────
#  Convenience targets
# ──────────────────────────────────────────────────────────────────────────────
clean:
	@echo "Cleaning…"
	@rm -rf $(OBJ_DIR)

rebuild: clean all

.PHONY: all clean rebuild
