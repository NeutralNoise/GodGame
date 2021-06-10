SRC_FILES := GodGame.cpp SDLEngine/ErrorEngine.cpp SDLEngine/FontEngine.cpp SDLEngine/GameEngine.cpp SDLEngine/ImageLoader.cpp SDLEngine/InfoEngine.cpp SDLEngine/Input.cpp SDLEngine/Renderer.cpp SDLEngine/Texture.cpp SDLEngine/Timer.cpp SDLEngine/Renderers/RendererSDL.cpp
CXX := g++
RELEASE_FLAGS := -w -std=c++11 -O3 -s
DEBUG_FLAGS := -Wall -g -std=c++11
#INCLUDE_DIR := 
LIBARY_FILES := -lSDL2 -lSDL2_image -lSDL2_ttf
APP_NAME_DEBUG := godgame_d
APP_NAME := godgame

godgame_d:
	$(CXX) $(DEBUG_FLAGS) -o $(APP_NAME_DEBUG) $(SRC_FILES) $(LIBARY_FILES)

godgame:
	$(CXX) $(RELEASE_FLAGS) -o $(APP_NAME) $(SRC_FILES) $(LIBARY_FILES)

clean:
	rm -f -r godgame_d
	rm -f -r godgame
