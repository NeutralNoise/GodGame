// GodGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
#include <iostream>
#include "SDLEngine/GameEngine.h"
#include "SDLEngine/ImageLoader.h"
#include "SDLEngine/Input.h"
#include "SDLEngine/EngineEvents.h"
#include "SDLEngine/RenderEngine/RenderEngine.h"
#include <SDL2/SDL.h>
#include "SDLEngine/FontEngine.h"
#include "SDLEngine/InfoEngine.h"
#include "SDLEngine/ErrorEngine.h"

int main(int argc, char ** argv)
{
    std::cout << "Hello World!\n"; 
	bool isRunning = false;
	GameEngine ge;
	isRunning = ge.InitGameEngine();

	if (!isRunning) {
		DisplayErrors();
		std::cin.get();
		exit(5);
	}

	Rect testRect(32,0, 32, 32);
	Rect testWinRect(16, 16, 128, 128);
	Rect testWinRect2(0, 0, 32, 32);
	RenderEngine renderEngine;
	FontEngine fe;
	fe.LoadFont("data/OpenSans-Regular.ttf");
	fe.LoadFromRenderedText("Hello World");
	EngineInfo * testInfo = nullptr;
	int xpos = 0;
	int ypos = 0;
	if (isRunning) {

		renderEngine.InitRenderImage(&ge);
		
		Input input;
		ImageLoader::LoadTexture("data/test.png");
		Texture *texture = ImageLoader::GetTexture("data/test.png");

		LayerTile * tile = new LayerTile;
		//tile->x = 0;
		//tile->y = 0;
		tile->x = 600 / 2;
		tile->y = 600 / 2;
		tile->height = 32;
		tile->width = 32;
		tile->texture = texture;
		tile->translateWithCamera = false;
		tile->checkCameraCollision = false;

		LayerTile * tile2 = new LayerTile;
		tile2->x = 0;
		tile2->y = 0;
		tile2->height = 32;
		tile2->width = 32;
		tile2->texture = texture;
		tile2->translateWithCamera = true;

		RenderLayer * layer = new RenderLayer;
		layer->layer = 1;
		layer->id = 1;
		layer->tiles.push_back(tile);
		layer->tiles.push_back(tile2);

		renderEngine.AddLayer(layer);
		/*
		for (int y = 0; y <= (600 / 32); y++) {
			for (int x = 0; x <= (600 / 32); x++) {
				LayerTile * world = new LayerTile;
				world->x = x * 32;
				world->y = y * 32;
				world->height = 32;
				world->width = 32;
				world->texture = texture;
				layer->tiles.push_back(world);
			}
		}
		*/
		while (isRunning) {
			
			testRect.x = xpos;
			testRect.y = ypos;
			
			ge.ClearScreen();

			renderEngine.DrawLayers();
			//Draw some stats on the screen.
			testInfo = InfoEngine::GetEngineInfo("rendered_textures");
			fe.LoadFromRenderedText(std::to_string(testInfo->idata));
			fe.Draw(Rect(5,0,0,0));

			ge.UpdateWindow();
			//This really shouldn't be here. set the number of fps to 60 the engine will track the fps and it can be reported to the user.
			ge.EngineWait(33);

			input.Update();
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
				xpos-=5;
			}

			if (input.IsInputDown(SDLK_d)) {
				xpos+=5;
			}
			EngineCamera *camera = GameEngine::GetRenderer()->camera;
			Rect newPos(camera->pos); //so we dont have to copy the height
			newPos.x = xpos;
			newPos.y = ypos;
			//newPos.x = 64;
			//newPos.y = 64;

			camera->MoveCamera(newPos);
			EngineRenderer * er = GameEngine::GetRenderer();
			tile->x = (er->window_width/2) - (int)(tile->width / 2);
			tile->y = (er->window_height/2) - (int)(tile->width / 2);
			
		}

		renderEngine.RemoveLayer(1);
		fe.CloseFontEngine();
		ge.CloseGameEngine();
	}
	return 0;
}
