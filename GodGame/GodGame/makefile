SRC_FILES := GodGame.cpp SDLEngine/ErrorEngine.cpp SDLEngine/FontEngine.cpp SDLEngine/GameEngine.cpp SDLEngine/ImageLoader.cpp SDLEngine/InfoEngine.cpp SDLEngine/Input.cpp SDLEngine/Renderer.cpp SDLEngine/Texture.cpp SDLEngine/Timer.cpp SDLEngine/Renderers/RendererSDL/RendererSDL.cpp SDLEngine/Renderers/RendererOpenGL/RendererOpenGL.cpp SDLEngine/Renderers/RendererOpenGL/IndexBuffer.cpp SDLEngine/Renderers/RendererOpenGL/VertexBuffer.cpp SDLEngine/Renderers/RendererOpenGL/VertexAtribArray.cpp SDLEngine/Renderers/RendererOpenGL/VertexBufferLayout.cpp SDLEngine/Renderers/RendererOpenGL/Shader.cpp
CXX := g++
RELEASE_FLAGS := -w -std=c++11 -O3 -s
DEBUG_FLAGS := -Wall -g -std=c++11
INCLUDE_DIR := -I../../Deps/Includes
LIBARY_FILES := -lSDL2 -lSDL2_image -lSDL2_ttf -lGL -lGLEW -lGLU
APP_NAME_DEBUG := godgame_d
APP_NAME := godgame

godgame_d:
	$(CXX) $(DEBUG_FLAGS) -o $(APP_NAME_DEBUG) $(SRC_FILES) $(LIBARY_FILES) $(INCLUDE_DIR)

godgame:
	$(CXX) $(RELEASE_FLAGS) -o $(APP_NAME) $(SRC_FILES) $(LIBARY_FILES)

clean:
	rm -f -r godgame_d
	rm -f -r godgame
