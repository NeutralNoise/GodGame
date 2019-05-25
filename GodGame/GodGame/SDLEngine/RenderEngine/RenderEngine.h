#pragma once
#include <vector>
#include "../GameEngine.h"
#include "../ImageLoader.h"

struct LayerTile
{
	int x = 0;
	int y = 0;

	int width = 32;
	int height = 32;

	//Texture
	int frame = 0; //!< For tile mapping
	Texture * texture = nullptr; //!< What texture does this tile use.
	bool translateWithCamera = false; //!< Is the tile rendered in world space of tile space.
	bool checkCameraCollision = true; //!< Does the engine have to check if this is within screen space. If if false it will always be drawn.
};

struct RenderLayer
{
	int id;
	int layer;
	std::vector<LayerTile*> tiles;
	std::vector<RenderLayer*> tileLayer;
	void (* Draw)() = nullptr;
	bool(*Sort)() = nullptr;
	int data; // not used for anything.
	int refCount = 0;

};

class RenderEngine {
public:
	RenderEngine();
	~RenderEngine();

	static bool InitRenderImage(GameEngine * ge);

	void AddLayer(RenderLayer * layer);

	void RemoveLayer(const int &id);

	void Update();

	void DrawLayers();

	void DrawLayer(RenderLayer * layer);


private:

	std::vector<RenderLayer*> m_layers;
	static GameEngine * p_gameEngine;

};