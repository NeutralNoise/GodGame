#pragma once
#include <sstream>
#include "Rect.h"
#include "ImageLoader.h"
#include "EngineCamera.h"
#include "Renderer.h"

struct SDL_Window;
struct SDL_Surface;
struct SDL_Renderer;

struct EngineRendererVersion {
	int major;
	int minor;
	int patch;
	//NOTE May put a string here too but its not needed now.
};

/** \struct EngineRenderer
 * \brief A structure representing rendering state.
 * 
 */

struct EngineRenderer {
	Renderer * renderer; //!< The new renderer.
	SDL_Renderer * sdl_renderer; //!< A structure representing rendering state. From SDL2
	int window_height; //!< The height of the window
	int window_width;  //!< The width of the window
	EngineCamera * camera;	//!< Camera used to draw too.
	UInt32 flags;
	EngineRendererVersion version; //!< The version of this renderer.
	//Stats
	float fps; //!< Number of frames per second
	//We can add some more information here later.

	/**
	 * \brief Construct a new EngineRenderer object
	 * 
	 */

	EngineRenderer() {
		sdl_renderer = nullptr;
		camera = nullptr;
		window_height = 0;
		window_width = 0;
		fps = 0.0f;
	}

	/**
	 * \brief Construct a new EngineRenderer object
	 * 
	 * \param renderer Pointer to a Renderer to use. \see Renderer
	 * \param wh Height of the window.
	 * \param ww Width of the window.
	 * \param flags What flags does this renderer have active.
	 */

	EngineRenderer(Renderer * renderer, const int &wh, const int &ww, const UInt32 &flags) {
		this->renderer = renderer;
		window_height = wh;
		window_width = ww;
		camera = new EngineCamera(0, 0, ww, wh);
		fps = 0.0f;
		this->flags = flags;
	}

	bool InitRenderer(SDL_Window * win) {
		return renderer->OnInit(win, flags, this);
	}

	const std::string GetVersionString() {
		std::stringstream rtn;
		rtn << renderer->GetRenderName();
		rtn << ": ";
		rtn << version.major;
		rtn << ".";
		rtn << version.minor;
		rtn << ".";
		rtn << version.patch;
		return rtn.str();
	}

};

/** \class GameEngine
 * \brief Holds everything together. What else should I say here?
 * 
 */

class GameEngine
{
public:

	/**
	 * \brief Construct a new GameEngine object
	 * 
	 */

	GameEngine();

	/**
	 * \brief Destroy the GameEngine object
	 * 
	 */

	~GameEngine();

	/**
	 * \brief Starts up the engine.
	 * 
	 * Creates a new window.
	 * 
	 * \return true if engine started else false.
	 */

	bool InitGameEngine();

	/**
	 * \brief Starts up the engine.
	 * 
	 * Creates a new window.
	 * 
	 * \param appName The text to be displayed in the title bar of the window.
	 * \param winWidth The width of the window.
	 * \param winHeight The height of the window.
	 * \param flags SDL2 window flags to use. \warning flags may change later but the SDL2 ones should still work.
	 * \return true if engine is started else false.
	 */

	bool InitGameEngine(const char * appName, EngineRenderer * renderer, const UInt32 &flags);

	/**
	 * \brief Cleans up the engine for closeing.
	 * 
	 */

	void CloseGameEngine();


	void Draw();


	/**
	 * \brief Renders the given texture to the screen.
	 * 
	 * \param tex The texture to render.
	 * \param rect The position and the amount of the text to copy.
	 * \param winRect The position within screen space to render the texture.
	 */

	void RenderCopy(Texture * tex, const Rect *rect = nullptr, const Rect *winRect = nullptr);

	/**
	 * \brief Clears the screen.
	 * 
	 */

	void ClearScreen();

	/**
	 * \brief Updates the screen with the rendered textures.
	 * 
	 */

	void UpdateWindow();

	/**
	 * \brief Makes the engine wait.
	 * 
	 * \param delay number of milliseconds to wait.
	 */

	void EngineWait(const int &delay);

	/**
	 * \brief Get the IsRunning object
	 * 
	 * \return true if engine is running.
	 */

	static const bool GetIsRunning() { return m_isRunning; };

	/**
	 * \brief Get the EngineRenderer object.
	 * 
	 * \return Pointer to the EngineRenderer. \see EngineRenderer 
	 */

	static EngineRenderer *GetRenderer() { return p_renderer; };

	static void SetRenderer(Renderer * renderer);

private:
	//TODO Make these not static.
	static SDL_Window * p_window; //!< SDL2 window.
	static EngineRenderer * p_renderer; //!< Used to render the current state of the engine.
	//
	static bool m_isRunning; //!< Used by the engine to make if it is not longer running. \note Read-only
	static bool m_createdRenderer; //!< If the game engine created the renderer true.
};

