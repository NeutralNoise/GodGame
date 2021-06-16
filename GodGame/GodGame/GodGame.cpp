// GodGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
#include <iostream>
#include "SDLEngine/GameEngine.h"
#include "SDLEngine/ImageLoader.h"
#include "SDLEngine/Input.h"
#include "SDLEngine/EngineEvents.h"
//#include "SDLEngine/RenderEngine/RenderEngine.h"
#include <SDL2/SDL.h>
#include "SDLEngine/FontEngine.h"
#include "SDLEngine/InfoEngine.h"
#include "SDLEngine/ErrorEngine.h"
#include "SDLEngine/EngineConfig.h"

#include "SDLEngine/Renderers/RendererSDL.h"
#include "SDLEngine/Renderers/RendererOpenGL.h"


//Uncomment this to spawn a shit load of tiles.
//#define BULK_FAKE_TILE_TEST
//#define BULK_FAKE_TILE_TEST_LOOP
//#define BULK_FAKE_TILE_TEST_LOOP_NO_CLEAR
#define BULK_FAKE_TILE_NUM 16000

int main(int argc, char ** argv)
{
    std::cout << "Hello World!\n"; 
	bool isRunning = false;
	GameEngine ge;
	RendererSDL testRender;
	RendererOpenGL testOpenGL;
	//TODO Load window size from file.
	//EngineRenderer EngineR(&testRender, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_RENDERER_ACCELERATED);
	EngineRenderer EngineR(&testOpenGL, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	isRunning = ge.InitGameEngine("SDL_BASE_GAME_ENGINE", &EngineR, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (!isRunning) {
		DisplayErrors();
		std::cin.get();
		exit(5);
	}

	Rect testRect(32,0, 32, 32);
	Rect testWinRect(16, 16, 128, 128);
	Rect testWinRect2(0, 0, 32, 32);
	//RenderEngine renderEngine;
	
	//FontEngine fe;
	FontEngine renderTime;
	FontEngine drawCallsFont;
	FontEngine engineFPS;
	FontEngine currentFPS;
	renderTime.LoadFont("data/OpenSans-Regular.ttf");	
	drawCallsFont.LoadFont("data/OpenSans-Regular.ttf");
	engineFPS.LoadFont("data/OpenSans-Regular.ttf");
	currentFPS.LoadFont("data/OpenSans-Regular.ttf");
	/*
	FontEngine renderTimeAvg;	
	renderTimeAvg.LoadFont("data/OpenSans-Regular.ttf");
	fe.LoadFont("data/OpenSans-Regular.ttf");
	fe.LoadFromRenderedText("Hello World");
	*/
	EngineInfo * testInfo = nullptr;
	EngineInfo * RenderInfo = nullptr;
	EngineInfo * RenderAvgInfo = nullptr;
	EngineInfo * DrawCalls = nullptr;
	int xpos = 0;
	int ypos = 0;

	float lastTime = 0.0f;
	float thisTime = 0.0f;
	SimpleTimer fpsTimer;
	if (isRunning) {
		Input input;
		/*
		ImageLoader::LoadTexture("data/test.png");
		Texture *texture = ImageLoader::GetTexture("data/test.png");
		Texture * lightTex = ImageLoader::GetTexture("data/light.png");

		RenderObject testObject;
		testObject.texture = texture;
		testObject.angle = 45;
		testObject.translateWithCamera = true;
		RenderObject testObject2;
		testObject2.layer = 3;
		testObject2.x = 0;
		testObject2.y = 0;
		//testObject2.height = 600;
		//testObject2.width = 600;
		testObject2.renderTile.height = texture->height;
		testObject2.renderTile.width = texture->width;
		testObject2.texture = texture;
		RenderObject light;
		light.texture = lightTex;
		light.renderTile.height = 64;
		light.renderTile.width = 64;
		light.layer = 2;
		light.height = 600;
		light.width = 600;*/
		
#ifdef BULK_FAKE_TILE_TEST

		std::vector<RenderObject*> fakeTiles;

		auto FAKE_TILE_TEST_LAMDA = [](Renderer*renderer, std::vector<RenderObject*> tiles, bool addAll) {
			EngineCamera fake_camera = *GameEngine::GetRenderer()->camera;
			size_t tileCount = tiles.size();
			for (size_t i = 0; i < tileCount; i++) {
				RenderObject * object = tiles[i];
				if (addAll) {
					renderer->AddRenderObject(object);
				}
				else if (fake_camera.CollisionWithCamera(Rect(object->x, object->y, object->width, object->height))) {
					renderer->AddRenderObject(object);
				}
			}
			return true;
		};

		//Simple test to test rendering speeds.
		int Fake_layer = 1;
		int Fake_X = 0;
		int Fake_Y = 0;
		int MAX_X = (64 * 128);
		for (int i = 0; i < (int)BULK_FAKE_TILE_NUM; i++) {
			RenderObject * tileTest = new RenderObject;
			tileTest->x = Fake_X;
			tileTest->y = Fake_Y;
			tileTest->height = 64;
			tileTest->width = 64;
			if (i >= BULK_FAKE_TILE_NUM / 2) {
				Fake_layer = 2;
			}
			tileTest->layer = Fake_layer;
			tileTest->renderTile.width = 32;
			tileTest->renderTile.height = 32;

			tileTest->texture = texture;
			tileTest->translateWithCamera = true;
			fakeTiles.push_back(tileTest);

			Fake_X += 64;
			if (Fake_X > MAX_X) {
				Fake_Y += 64;
				Fake_X = 0;
			}
		}

		
#endif // BULK_FAKE_TILE_TEST

#ifdef BULK_FAKE_TILE_TEST_LOOP_NO_CLEAR
		FAKE_TILE_TEST_LAMDA(&testRender, fakeTiles, true);
		testRender.ToggleLayerClear(1);
		testRender.ToggleLayerClear(2);
#endif //BULK_FAKE_TILE_TEST

		//Draw some stats on the screen.
		testInfo = InfoEngine::GetEngineInfo("rendered_textures");
		RenderInfo = InfoEngine::GetEngineInfo("layer_render_time");
		RenderAvgInfo = InfoEngine::GetEngineInfo("layer_render_time_avg");
		DrawCalls = InfoEngine::GetEngineInfo("ren_draw_calls");
		while (isRunning) {
			fpsTimer.StartTimer();
			//testRender.AddRenderObject(&testObject);
			//testRender.AddRenderObject(&testObject2);
			//testRender.AddLightRenderObject(&light);
#ifdef BULK_FAKE_TILE_TEST_LOOP
			FAKE_TILE_TEST_LAMDA(&testRender, fakeTiles, false);
#endif //BULK_FAKE_TILE_TEST_LOOP

			ge.ClearScreen();
			/*
			drawCallsFont.LoadFromRenderedText(std::to_string(DrawCalls->uidata));
			renderTime.LoadFromRenderedText("Layer Draw Time:" + std::to_string(RenderInfo->fdata / 1000));
			engineFPS.LoadFromRenderedText("Engine FPS:" + std::to_string(1000 / RenderInfo->fdata));
			currentFPS.LoadFromRenderedText("Current FPS:" + std::to_string(1000 /thisTime));
			drawCallsFont.Draw(&testRender, Rect(5, 0, 0, 0), 5);
			renderTime.Draw(&testRender, Rect(5, 45, 0, 0), 5);
			engineFPS.Draw(&testRender, Rect(5, 90, 0, 0), 5);
			currentFPS.Draw(&testRender, Rect(5, 135, 0, 0), 5);
			*/
			ge.Draw();
			ge.UpdateWindow();
			input.Update();
			//testRender.ClearRenderObjects();

			input.ProcessEvents();
			InputEvent ie = input.GetNextEvent();

			while (ie.type != -1) {

				if (ie.type == EE_QUIT) {
					isRunning = false;
				}
				if (ie.type == EE_KEYDOWN) {
					//Shit Will Happen here maybe
				}
				ie = input.GetNextEvent();
			}


			if (input.IsInputDown(SDLK_w)) {
				ypos -= 5;
				/*
				if (tile->y == (0 - testRect.height)) {
					tile->y = 599;
				}
				*/
			}

			if (input.IsInputDown(SDLK_s)) {
				ypos += 5;
				/*
				if (ypos == 600) {
					ypos = 0 - testRect.height;
				}
				*/
			}

			if (input.IsInputDown(SDLK_a)) {
				xpos -= 5;
			}

			if (input.IsInputDown(SDLK_d)) {
				xpos += 5;
			}
			EngineCamera *camera = GameEngine::GetRenderer()->camera;
			Rect newPos(camera->pos); //so we dont have to copy the height
			newPos.x = xpos;
			newPos.y = ypos;
			//newPos.x = 64;
			//newPos.y = 64;

			camera->MoveCamera(newPos);
			//Work out FPS
			thisTime = fpsTimer.GetTime();
			if (MAX_FRAME_TIME > thisTime) {
				ge.EngineWait(MAX_FRAME_TIME - (int)thisTime);
				thisTime += MAX_FRAME_TIME - thisTime;
			}

			ErrorEngine::GetInstance()->OnFatel();

		}
		//We still need clean up our objects.
		//fe.CloseFontEngine();
		ge.CloseGameEngine();
	}
	return 0;
}
