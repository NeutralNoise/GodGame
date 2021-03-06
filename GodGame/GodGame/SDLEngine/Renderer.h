#pragma once
#include <vector>
#include <GLM/glm.hpp>
#include "InfoEngine.h"
#include "ImageLoader.h"
#include "EngineConfig.h"
#include "typedefs.h"
#include "Rect.h"
#include "Timer.h"

/**
* \file Renderer.h
* \version 1.0
* \author Bradley Macdonald
* \date 2019
*
*  Things needed for rendering and contains a base class renderer.
*/


struct SDL_Window;
struct EngineRendererVersion;
struct EngineRenderer;

/** \struct RenderTile
 * \brief The tile within the texture that is rendered to the LayerTile.
 * \warning this will be replaced by a sprite sheet later.
*/

struct RenderTile {
	float x = 0; //!< The x offset within the image.
	float y = 0; //!< The y offset within the image.
	float width = 32; //!< The width of the image tile.
	float height = 32; //!< The height of the image tile.
	glm::vec2 topLeft = glm::vec2(0.0f, 0.0f);
	glm::vec2 topRight = glm::vec2(1.0f, 0.0f);
	glm::vec2 bottomLeft = glm::vec2(0.0f, 1.0f);
	glm::vec2 bottomRight = glm::vec2(1.0f, 1.0f);

	RenderTile() {}

	RenderTile(const float &x, const float &y, const float &w, const float &h) {
		this->x = x;
		this->y = y;
		this->width = w;
		this->height = h;

		topLeft.x = x;
		topLeft.y = y;

		topRight.x = w;
		topRight.y = y;

		bottomLeft.x = x;
		bottomLeft.y = h;

		bottomRight.x = w;
		bottomRight.y = h;
	}

	RenderTile(const glm::vec2 &topLeft, const glm::vec2 &topRight, const glm::vec2 &bottomLeft, const glm::vec2 &bottomRight) {
		this->topLeft = topLeft;
		this->topRight = topRight;
		this->bottomLeft = bottomLeft;
		this->bottomRight = bottomRight;
	}
};

/** \struct RenderObject
 * \brief Somthing that is rendered to the screen
 * 
*/

struct RenderObject
{
	float x = 0; //!< The X position of the object.
	float y = 0; //!< The Y position of the object.

	float width = TILE_SIZE; //!< The width of the tile.
	float height = TILE_SIZE; //!< The height of the tile.
	
	//Is this an offest?
	Point pivoitPoint; //!< Point the object rotates around.

	Texture * texture; //!< The texture use to render to the object.
	RenderTile renderTile; //!< The position, width and height within the texture.

	int layer = 0; //!< What layer is this object drawn on.
	int sublayer = 0; //!< What sublayer of the layer is the object drawn on.
	// This should be in clockwise direction
	float spinAngle = 0.0; //!< Angle of rotation in radians.
	float orbitAngle = 0.0; //!< Angle of orbit rotation in radians. \warn Not used.
	int frame = 0; //!< What frame of the animeation is this object on.
	bool translateWithCamera = false; //!< Is the tile rendered in world space of tile space.
	bool doesRotate = false; //!< Does this rotate around the pivoitPoint.
	bool hasOrbit = false; //!< Does this orbit around a point. \warn Not used.

	/**
	 * \brief Construct a new RenderObject object.
	 * 
	*/

	RenderObject() {}

	/**
	 * \brief Construct a new RenderObject object.
	 * 
	 * \param x The x position of the object.
	 * \param y The x position of the object.
	 * \param w The width of the object.
	 * \param h The height of the object.
	 * 
	 * \note This sets the pivoit point at the center of the object.
	 * 
	*/

	RenderObject(const float &x, const float &y, const float &w, const float &h) {
		this->x = x;
		this->y = y;
		this->width = w;
		this->height = h;
		pivoitPoint = Point(x + (w / 2), y + (h / w));
	}

	/**
	 * \brief Construct a new RenderObject object.
	 * 
	 * \param x The x position of the object.
	 * \param y The x position of the object.
	 * \param w The width of the object.
	 * \param h The height of the object.
	 * \param px The x position of the pivoit point.
	 * \param py The y position of the pivoit point.
	*/

	RenderObject(const float &x, const float &y, const float &w, const float &h, const float &px, const float &py) {
		this->x = x;
		this->y = y;
		this->width = w;
		this->height = h;
		pivoitPoint = Point(px, py);
	}

	//Updates what part of the image to render to the screen.
	void UpdateRenderTile() {
		//TODO update the X/Y render tile.
	}

};

/** \struct RenderObjectLayer
 * \brief Decribes a render layer.
 * 
*/

struct RenderObjectLayer
{
	int id; //!< ID of this layer
	int layer; //!< The layer number. Think of this as render order. The higher the number the later it is rendered.
	std::vector<RenderObject*> lights; //!< Lights on this layer.
	std::vector<RenderObject*> renderObjects; //!< What tiles are in this layer
	std::vector<RenderObjectLayer*> objectLayer; //!< Additional layers withing this layer. \warning Not used at the moment.
	void(*Draw)() = nullptr; //!< Function pointer to a externaly defined draw function. (Lets you do things that I didn't think of)
	bool(*Sort)() = nullptr; //!< Function pointer to a externaly defined sort function. Used to sort out the RenderLayer order according to layer by defult.
	bool needsClear = true; //!< Do the tiles on this layer need to be cleared.
	int freeTile = 0; //!< Number of free tiles on this layer.
	int maxFree = 0; //!< The maximum number free tiles this layer has.
	std::vector<int> freeTileIndex; //!< Vector of free tiles on this layer.
	//Deletes sub RenderObjectLayer.

	/**
	 * \brief Cleans up the layer. Deletes any allocated memory.
	 * 
	*/

	void CleanUp() {
		for (size_t i = 0; i < renderObjects.size(); i++) {
			if (renderObjects[i] != nullptr) {
				renderObjects[i] = nullptr;
			}
		}

		for (size_t i = 0; i < objectLayer.size(); i++) {
			if (objectLayer[i] != nullptr) {
				objectLayer[i]->CleanUp();
				//We do this because we take the memory.
				delete objectLayer[i];
				objectLayer[i] = nullptr;
			}
		}
	}

	/**
	 * \brief Clears the Render layer to be filled again.
	 * 
	*/

	void Clear() {
		if (needsClear == true) {
			size_t renObjectsSize = renderObjects.size();
			for (size_t i = 0; i < renObjectsSize; i++) {
				renderObjects[i] = nullptr;
				if (renObjectsSize > (size_t)maxFree) {
					maxFree++;
				}
				
			}
			if (maxFree != 0) {
				freeTile = 0;
			}
		}
		for (size_t i = 0; i < objectLayer.size(); i++) {
			if (objectLayer[i] != nullptr) {
				objectLayer[i]->Clear();
			}
		}

		for (size_t i = 0; i < lights.size(); i++) {
			lights[i] = nullptr;
		}

	}
};

/** \class Render
 * \brief Describes a renderer.
 * 
 * \note This is a virtual class and all other renderers inherit this.
 * 
*/

class Renderer {

public:
	/**
	 * \brief Starts the renderer.
	 * 
	 * \param win The SDL window that will be rendered to.
	 * \param flags Flags needed for the renderer.
	 * \return Returns true if everything is ok.
	 * 
	 * \warning This is a virtual function and will return false and add an engine error code.
	 * 
	*/

	virtual bool OnInit(SDL_Window * win, const UInt32 &flags, EngineRenderer * info);

	//TODO is this needed.
	virtual void OnUpdate();

	/**
	 * \brief Called once a frame and is used to draw RenderObjects to the screen.
	 * \see RenderObject
	 * \warning This is a virtual function and will return false and add an engine error code.
	 * 
	*/

	virtual void OnDraw();

	/**
	 * \brief Cleans up the renderer and is called when the program is closed.
	 * \warning This is a virtual function and will return false and add an engine error code. 
	 * 
	*/

	virtual void OnCleanUp();

	/**
	 * \brief Added a RenderObject to be rendered.
	 * 
	 * \param renderObject A pointer to a RenderObject to add.
	 * \see RenderObject
	*/

	void AddRenderObject(RenderObject * renderObject);

	/**
	 * \brief Added a light RenderObject.
	 * 
	 * \param renderObject A pointer to a light RenderObject to add.
	 * \see RenderObject
	*/

	void AddLightRenderObject(RenderObject * renderObject);

	/**
	 * \brief Clear all RenderObjects from the renderer.
	 *
	*/

	void ClearRenderObjects();

	/**
	 * \brief Change if a RenderObjectLayer needs to be cleared or not.
	 * 
	 * \param layer The layer that needs the layer clear toggled on.
	*/

	void ToggleLayerClear(const UInt32 &layer);
	
	/**
	 * \brief Compiles a fragment shader and a vertex shader into a shader program.
	 * 
	 * \param frag File path to the fragment shader sourcecode.
	 * \param vert File path to the vertex shader sourcecode.
	 * \return bool Returns true if compiled and id will be set to the program ID. If not returns false and id set to 0.
	*/

	virtual bool CompileShader(const std::string &frag, const std::string &vert);
	
	const EngineRendererVersion * GetVersion();
	std::string GetRenderName() const&;

protected:

	/**
	 * \brief Sets up the timers for profiling.
	 * \note This should be called by the inheriting class in OnInit().
	*/

	void InitRendererInfo();
	std::vector<RenderObjectLayer*> m_layers; //!< Layers to be drawn.
	static EngineInfo * p_layerRenderTime; //!< Used to store the time taken to render the layers.
	static EngineInfo * p_layerRenderTimeAvg; //!< Used to store the average time taken to render the layers.
	static EngineInfo * p_drawCalls; //!< Counts the number of draw calls each frame.
	SimpleTimer m_layerAvgTimer; //!< Timer used to time the time taken to render the layer.
	SimpleTimer m_layerTimer; //!< Timer used to time the time taken to render the layer.
	SDL_Window * p_SDLwin; //!< Copy of the SDL2 window that is being used.
	std::string m_renName = "Unknown Renderer";
	EngineRendererVersion *p_version;
private:

	/**
	 * \brief Finds an empty tile in layer specified.
	 * 
	 * \param layer The layer to check for an empty tile.
	 * \return int Returns the index of the empty tile or -1 if nothing found.
	*/

	int FindEmptyTile(const int &layer);

	/**
	 * \brief Finds an empty tile in the gived layer.
	 * 
	 * \param layer A pointer to a RenderObjectLayer check for an empty tile.
	 * \return int Returns the index of the empty tile or -1 if nothing found.
	 * \see RenderObjectLayer
	*/

	int FindEmptyTile(RenderObjectLayer * layer);

	/**
	 * \brief Added a new layer that is empty.
	 * 
	*/

	void AddEmptyLayer();

	/**
	 * \brief Adds a new sublayer to the specified layer.
	 * 
	 * \param layer The layer to add the empty sublayer too.
	*/

	void AddEmptySublayer(const int &layer);
};
