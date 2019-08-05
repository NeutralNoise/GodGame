#pragma once
#include <vector>
#include "InfoEngine.h"
#include "ImageLoader.h"
#include "EngineConfig.h"
#include "typedefs.h"
#include "Rect.h"
#include "Timer.h"

struct SDL_Window;

/** \struct RenderTile
 * \brief The tile within the texture that is rendered to the LayerTile.
 * \warning this will be replaced by a sprite sheet later.
*/

struct RenderTile {
	int x = 0; //!< The x offset within the image.
	int y = 0; //!< The y offset within the image.
	int width = 32; //!< The width of the image tile.
	int height = 32; //!< The height of the image tile.

	RenderTile() {}

	RenderTile(const int &x, const int &y, const int &w, const int &h) {
		this->x = x;
		this->y = y;
		this->width = w;
		this->height = h;
	}
};

struct RenderObject
{
	int x = 0;
	int y = 0;

	int width = TILE_SIZE;
	int height = TILE_SIZE;
	
	Point pivoitPoint;

	Texture * texture;
	RenderTile renderTile;

	int layer = 0;
	int sublayer = 0;
	// This should be in clockwise direction
	double angle = 0.0; //!< Angle of rotation in degrees.
	int frame = 0;
	bool translateWithCamera = false; //!< Is the tile rendered in world space of tile space.

	RenderObject() {}
	RenderObject(const int &x, const int &y, const int &w, const int &h) {
		this->x = x;
		this->y = y;
		this->width = w;
		this->height = h;
		pivoitPoint = Point(x + (w / 2), y + (h / w));
	}
	RenderObject(const int &x, const int &y, const int &w, const int &h, const int &px, const int &py) {
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

struct RenderObjectLayer
{
	int id; //!< ID of this layer
	int layer; //!< The layer number. Think of this as render order. The higher the number the later it is rendered.
	std::vector<RenderObject*> renderObjects; //!< What tiles are in this layer
	std::vector<RenderObjectLayer*> objectLayer; //!< Additional layers withing this layer. \warning Not used at the moment.
	void(*Draw)() = nullptr; //!< Function pointer to a externaly defined draw function. (Lets you do things that I didn't think of)
	bool(*Sort)() = nullptr; //!< Function pointer to a externaly defined sort function. Used to sort out the RenderLayer order according to layer by defult.
	bool needsClear = true;
	int freeTile = 0;
	int maxFree = 0;
	std::vector<int> freeTileIndex;
	//Deletes sub RenderObjectLayer.
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
	}
};

class Renderer {

public:
	//Take some args
	virtual bool OnInit(SDL_Window * win, const UInt32 &flags);

	virtual void OnUpdate();

	virtual void OnDraw();

	virtual void OnCleanUp();

	void AddRenderObject(RenderObject * renderObject);

	void ClearRenderObjects();

	void ToggleLayerClear(const UInt32 &layer);

protected:

	void InitRendererInfo();
	std::vector<RenderObjectLayer*> m_layers; //!< Layers to be drawn.
	static EngineInfo * p_layerRenderTime; //!< Used to store the time taken to render the layers.
	static EngineInfo * p_layerRenderTimeAvg; //!< Used to store the average time taken to render the layers.
	static EngineInfo * p_drawCalls; //!< Counts the number of draw calls each frame.
	SimpleTimer m_layerAvgTimer; //!< Timer used to time the time taken to render the layer.
	SimpleTimer m_layerTimer; //!< Timer used to time the time taken to render the layer.

private:

	int FindEmptyTile(const int &layer);
	int FindEmptyTile(RenderObjectLayer * layer);
	void AddEmptyLayer();
	void AddEmptySublayer(const int &layer);
};