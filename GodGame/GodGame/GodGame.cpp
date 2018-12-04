// GodGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
#include <iostream>
#include "SDLEngine/GameEngine.h"
#include "SDLEngine/ImageLoader.h"
#include "SDLEngine/Input.h"
#include "SDLEngine/EngineEvents.h"
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
	int xpos = 0;
	int ypos = 0;
	if (isRunning) {
		Input input;
		ImageLoader::LoadTexture("data/test.png");
		Texture *texture = ImageLoader::GetTexture("data/test.png");
		while (isRunning) {
			
			testRect.x = xpos;
			testRect.y = ypos;
			
			ge.ClearScreen();
			ge.RenderCopy(texture, &testWinRect2, &testRect);
			ge.RenderCopy(texture, &testWinRect2, &testWinRect2);


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
				ypos--;
				if (ypos == (0 - testRect.height)) {
					ypos = 599;
				}
			}

			if (input.IsInputDown(SDLK_s)) {
				ypos++;
				if (ypos == 600) {
					ypos = 0 - testRect.height;
				}
			}

			if (input.IsInputDown(SDLK_a)) {
				xpos--;
				if (xpos == (0 - testRect.width)) {
					xpos = 599;
				}
			}

			if (input.IsInputDown(SDLK_d)) {
				xpos++;
				if (xpos == 600) {
					xpos = 0 - testRect.width;
				}
			}

		}
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
