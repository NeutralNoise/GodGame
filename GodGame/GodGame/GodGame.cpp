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

#include "SDLEngine/Renderers/RendererSDL/RendererSDL.h"
#include "SDLEngine/Renderers/RendererOpenGL/RendererOpenGL.h"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_sdl.h"
#include "ImGUI/imgui_impl_opengl3.h"
#include "SDLEngine/EngineAssert.h"


//Uncomment this to spawn a shit load of tiles.
#define BULK_FAKE_TILE_TEST
#define BULK_FAKE_TILE_TEST_LOOP
//#define BULK_FAKE_TILE_TEST_LOOP_NO_CLEAR
#define BULK_FAKE_TILE_NUM 25000

int main(int argc, char ** argv)
{
    std::cout << "Hello World!\n";
	bool isRunning = false;
	GameEngine ge;
	//RendererSDL testRender;
	//RendererOpenGL testOpenGL;
	RendererOpenGL testRender;
	//TODO Load window size from file.
	//EngineRenderer EngineR(&testRender, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_RENDERER_ACCELERATED);
	EngineRenderer EngineR(&testRender, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

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
	EngineInfo * DrawnQuards = nullptr;
	EngineInfo * DrawVertexs = nullptr;
	EngineInfo * BatchCount = nullptr;
	EngineInfo * BatchMemMax = nullptr;
	EngineInfo * BatchMemUsed = nullptr;
	float xpos = 0;
	float ypos = 0;

	float lastTime = 0.0f;
	float thisTime = 0.0f;
	SimpleTimer fpsTimer;

	double frameTimeCount = 0.0f;
	double frameRateCount = 0.0f;

	double frameNumber = 0.0f;

	if (isRunning) {
		Input input;
		//ImageLoader::LoadTexture("data/test.png");
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
		static float rangle = 0.0;
		static float oangle = 0.0;
		auto FAKE_TILE_TEST_LAMDA = [](Renderer*renderer, std::vector<RenderObject*> tiles, bool addAll) {
			int drawCount = 0;
			EngineCamera fake_camera = *GameEngine::GetRenderer()->camera;
			size_t tileCount = tiles.size();
			for (size_t i = 0; i < tileCount; i++) {
				RenderObject * object = tiles[i];
				object->doesRotate = true;
				object->spinAngle = -rangle;
				object->pivoitPoint.x = 32.0;
				object->pivoitPoint.y = 32.0;
				
				if (addAll) {
					renderer->AddRenderObject(object);
				}
				else if (fake_camera.CollisionWithCamera(Rect(object->x, object->y, object->width, object->height))) {
					renderer->AddRenderObject(object);
					drawCount++;
				}
			}
			//std::cout << drawCount << std::endl;
			rangle += 1.0f;
			return true;
		};

		//Simple test to test rendering speeds.
		int Fake_layer = 0;
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
				Fake_layer = 1;
			}
			tileTest->layer = Fake_layer;
			//tileTest->renderTile.width = 32;
			//tileTest->renderTile.height = 32;
			tileTest->renderTile = RenderTile(0.0f, 0.0f, 1.0f, 1.0f);

			//tileTest->texture = texture;
			tileTest->texture = ImageLoader::GetTexture("data/test.png");
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
		testRender.ToggleLayerClear(0);
		testRender.ToggleLayerClear(1);
#endif //BULK_FAKE_TILE_TEST

		//Draw some stats on the screen.
		testInfo = InfoEngine::GetEngineInfo("rendered_textures");
		RenderInfo = InfoEngine::GetEngineInfo("layer_render_time");
		RenderAvgInfo = InfoEngine::GetEngineInfo("layer_render_time_avg");
		DrawCalls = InfoEngine::GetEngineInfo("ren_draw_calls");
		DrawnQuards = InfoEngine::GetEngineInfo("ren_quard_count");
		DrawVertexs = InfoEngine::GetEngineInfo("ren_vertex_count");
		BatchCount = InfoEngine::GetEngineInfo("ren_batch_count");
		BatchMemMax = InfoEngine::GetEngineInfo("ren_max_batch_mem");
		BatchMemUsed = InfoEngine::GetEngineInfo("ren_used_batch_mem");
		/*
		RenderObject ro(0.0f, 0.0f, 32.0f, 32.0f);
		ro.translateWithCamera = true;
		RenderObject ro2(64.0f, 0.0f, 32.0f, 32.0f);
		ro2.translateWithCamera = true;
		testRender.AddRenderObject(&ro);
		testRender.AddRenderObject(&ro2);
		*/
		UInt32 countedFrames = 0;
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

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL2_NewFrame(ge.p_window);
			ImGui::NewFrame();


#if 0
			{
				static float f = 0.0f;
				static int counterGUI = 0;
				static bool showBytes = false;
				static bool window_open = true;
				if (window_open) {
					ImGui::Begin("Renderer stats", &window_open);                          // Create a window called "Hello, world!" and append into it.
					/*
					ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
					//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
					//ImGui::Checkbox("Another Window", &show_another_window);

					ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
					//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

					if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
						counterGUI++;
					ImGui::SameLine();
					ImGui::Text("counter = %d", counterGUI);
					*/
					ImGui::Text("%s", EngineR.GetVersionString().c_str());
					ImGui::Text("Draw calls: %i", DrawCalls->uidata);
					ImGui::Text("Drawn vertexs: %i", DrawVertexs->uidata);
					ImGui::Text("Drawn quards: %i", DrawnQuards->uidata);
					ImGui::Text("Render batch count: %i", BatchCount->uidata);
					ImGui::Checkbox("Show Bytes", &showBytes);
					if (showBytes) {
						ImGui::Text("Render batch used mem: %iB", BatchMemUsed->uidata);
						ImGui::Text("Render batch max mem: %iB", BatchMemMax->uidata);
					}
					else {
						ImGui::Text("Render batch used mem: %.3fKB", (float)(BatchMemUsed->uidata) / 1000.0f);
						ImGui::Text("Render batch max mem: %.3fKB", (float)(BatchMemMax->uidata) / 1000.0f);
					}

					ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
					ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", frameTimeCount / frameNumber, frameRateCount);
					ImGui::Text("Application %.3f ms/frame (%.1f FPS)", thisTime, SECOND_MICRO_SECONDS / thisTime);
					static ImVec4 testColours;
					
					//ImGui::SliderFloat4("test", (float*)&testColours, 0.0f, 100.0f);
					ImGui::End();
				}
				ImGui::Begin("View Port"); 
				ImGui::Image(testRender.m_renObjFBO.GetAttachment(), ImVec2(300.0, 300.0), ImVec2(0,1), ImVec2(1,0));
				ImGui::End();
			}
#endif

			{

				static bool opt_fullscreen = true;
				static bool opt_padding = false;
				static bool p_open = true;
				static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

				// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
				// because it would be confusing to have two docking targets within each others.
				ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
				if (opt_fullscreen)
				{
					const ImGuiViewport* viewport = ImGui::GetMainViewport();
					ImGui::SetNextWindowPos(viewport->WorkPos);
					ImGui::SetNextWindowSize(viewport->WorkSize);
					ImGui::SetNextWindowViewport(viewport->ID);
					ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
					ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
					window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
					window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
				}
				else
				{
					dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
				}

				// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
				// and handle the pass-thru hole, so we ask Begin() to not render a background.
				if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
					window_flags |= ImGuiWindowFlags_NoBackground;

				// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
				// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
				// all active windows docked into it will lose their parent and become undocked.
				// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
				// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
				if (!opt_padding)
					ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
				ImGui::Begin("DockSpace", &p_open, window_flags);
				{
					if (!opt_padding)
						ImGui::PopStyleVar();

					if (opt_fullscreen)
						ImGui::PopStyleVar(2);

					// Submit the DockSpace
					ImGuiIO& io = ImGui::GetIO();
					if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
					{
						ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
						ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
					}
					else
					{
						//ShowDockingDisabledMessage();
					}
					static bool showViewPort = true;
					if (showViewPort) {
						ImGui::Begin("View Port", &showViewPort);
						//ImVec2 viewSize = ImGui::GetWindowSize();
						ImVec2 viewSize = ImGui::GetWindowSize();
						ImGui::Image(testRender.m_renObjFBO.GetAttachment(), viewSize, ImVec2(0, 1), ImVec2(1, 0));
						ImGui::End();
					}

					static bool window_open = true;
					if (ImGui::BeginMenuBar())
					{
						static bool newProject = false;
						if (ImGui::BeginMenu("File")) {
							ImGui::MenuItem("New Project", NULL, &newProject);
							ImGui::EndMenu();
						}

						if (ImGui::BeginMenu("Options"))
						{
							// Disabling fullscreen would allow the window to be moved to the front of other windows,
							// which we can't undo at the moment without finer window depth/z control.
							ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
							ImGui::MenuItem("Padding", NULL, &opt_padding);
							ImGui::MenuItem("Render Stats", NULL, &window_open);
							ImGui::MenuItem("View Port", NULL, &showViewPort);
							ImGui::Separator();

							if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
							if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
							if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
							if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
							if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
							ImGui::Separator();

							if (ImGui::MenuItem("Close", NULL, false, &p_open != NULL))
								p_open = false;
							ImGui::EndMenu();
						}
						ImGui::EndMenuBar();

						if (newProject) {
							//TODO Show new project window.
						}

					}
					static bool showBytes = false;
					if (window_open) {
						/*
						ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
						//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
						//ImGui::Checkbox("Another Window", &show_another_window);

						ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
						//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

						if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
							counterGUI++;
						ImGui::SameLine();
						ImGui::Text("counter = %d", counterGUI);
						*/
						ImGui::Begin("Renderer stats", &window_open);                          // Create a window called "Hello, world!" and append into it.
						ImGui::Text("%s", EngineR.GetVersionString().c_str());
						ImGui::Text("Draw calls: %i", DrawCalls->uidata);
						ImGui::Text("Drawn vertexs: %i", DrawVertexs->uidata);
						ImGui::Text("Drawn quards: %i", DrawnQuards->uidata);
						ImGui::Text("Render batch count: %i", BatchCount->uidata);
						ImGui::Checkbox("Show Bytes", &showBytes);
						if (showBytes) {
							ImGui::Text("Render batch used mem: %iB", BatchMemUsed->uidata);
							ImGui::Text("Render batch max mem: %iB", BatchMemMax->uidata);
						}
						else {
							ImGui::Text("Render batch used mem: %.3fKB", (float)(BatchMemUsed->uidata) / 1000.0f);
							ImGui::Text("Render batch max mem: %.3fKB", (float)(BatchMemMax->uidata) / 1000.0f);
						}
						ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
						ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", frameTimeCount / frameNumber, frameRateCount);
						ImGui::Text("Application %.3f ms/frame (%.1f FPS)", thisTime, SECOND_MICRO_SECONDS / thisTime);
						static ImVec4 testColours;

						//ImGui::SliderFloat4("test", (float*)&testColours, 0.0f, 100.0f);
						ImGui::End();
					}


				}
				ImGui::End();
			}


			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			//TODO clean this up.
			SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
			SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			SDL_GL_MakeCurrent(backup_current_window, backup_current_context);

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
				ge.EngineWait(MAX_FRAME_TIME - thisTime);
				thisTime += MAX_FRAME_TIME - thisTime;
			}

			if (frameRateCount > 1000000 | frameTimeCount > 1000000 | frameNumber > 100000) {
				frameTimeCount = 0.0f;
				frameRateCount = 0.0f;
				frameNumber = 0.0f;
			}
			frameNumber += 1.0f;
			frameTimeCount += thisTime;
			frameRateCount = SECOND_MICRO_SECONDS / (frameTimeCount / frameNumber);
			//std::cout << SECOND_MICRO_SECONDS / thisTime << "\n";
			ErrorEngine::GetInstance()->OnFatel();
		}
		//We still need clean up our objects.
		//fe.CloseFontEngine();
		ge.CloseGameEngine();
	}
	return 0;
}
