#pragma once
#include <vector>
#include "../GameEngine.h"
#include "../ImageLoader.h"

struct LayerTile
{
	int x;
	int y;

	int width;
	int height;

	//Texture
	int frame = 0; //!< For tile mapping
	Texture * texture;
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