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

int main(int argc, char ** argv)
{
    std::cout << "Hello World!\n"; 
	bool isRunning = false;
	GameEngine ge;
	isRunning = ge.InitGameEngine();
	Rect testRect(32,0, 32, 32);
	Rect testWinRect(16, 16, 128, 128);
	Rect testWinRect2(0, 0, 32, 32);
	RenderEngine renderEngine;
	int xpos = 0;
	int ypos = 0;
	if (isRunning) {

		renderEngine.InitRenderImage(&ge);
		
		Input input;
		ImageLoader::LoadTexture("data/test.png");
		Texture *texture = ImageLoader::GetTexture("data/test.png");

		LayerTile * tile = new LayerTile;
		tile->x = 0;
		tile->y = 0;
		tile->height = 32;
		tile->width = 32;
		tile->texture = texture;
		LayerTile * tile2 = new LayerTile;
		tile2->x = 0;
		tile2->y = 0;
		tile2->height = 32;
		tile2->width = 32;
		tile2->texture = texture;

		RenderLayer * layer = new RenderLayer;
		layer->layer = 1;
		layer->id = 1;
		//layer->tiles.push_back(tile);
		layer->tiles.push_back(tile2);

		renderEngine.AddLayer(layer);

		while (isRunning) {
			
			testRect.x = xpos;
			testRect.y = ypos;
			
			ge.ClearScreen();
			//ge.RenderCopy(texture, &testWinRect2, &testRect);
			//ge.RenderCopy(texture, &testWinRect2, &testWinRect2);

			renderEngine.DrawLayers();

			//texture.surface = ImageLoader::GetTexture("data/test.bmp")->surface;
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
				xpos--;
			}

			if (input.IsInputDown(SDLK_d)) {
				xpos++;
			}
			EngineCamera *camera = GameEngine::GetRenderer()->camera;
			Rect newPos(camera->pos);
			newPos.x = xpos;
			newPos.y = ypos;
			//newPos.x = 64;
			//newPos.y = 64;

			camera->MoveCamera(newPos);

			tile->x = camera->centerPos.x;
			tile->y = camera->centerPos.y;

		}

		renderEngine.RemoveLayer(1);

		ge.CloseGameEngine();
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
