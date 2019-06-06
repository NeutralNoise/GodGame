#pragma once
#include <vector>
#include "../GameEngine.h"
#include "../ImageLoader.h"

struct LayerTile
{
	int x = 0; //!< X position in the world.
	int y = 0; //!< Y position in the world.

	int width = 32; //!< The width of the tile
	int height = 32; //!< The height of the tile

	//Texture
	int frame = 0; //!< For tile mapping
	Texture * texture = nullptr; //!< What texture does this tile use.
	bool translateWithCamera = false; //!< Is the tile rendered in world space of tile space.
	bool checkCameraCollision = true; //!< Does the engine have to check if this is within screen space. If if false it will always be drawn.
};

struct RenderLayer
{
	int id; //!< ID of this layer
	int layer; //!< The layer number. Think of this as render order. The higher the number the later it is rendered.
	std::vector<LayerTile*> tiles; //!< What tiles are in this layer
	std::vector<RenderLayer*> tileLayer; //!< Additional layers withing this layer. \warning Not used at the moment.
	void (* Draw)() = nullptr; //!< Function pointer to a externaly defined draw function. (Lets you do things that I didn't think of)
	bool(*Sort)() = nullptr; //!< Function pointer to a externaly defined sort function. Used to sort out the RenderLayer order according to layer by defult.
	int data; // not used for anything.
	int refCount = 0; // not used.

};

class RenderEngine {
public:

	/**
	 * \brief Construct a new RenderEngine object
	 * 
	 */

	RenderEngine();

	/**
	 * \brief Destroy the RenderEngine object
	 * 
	 */

	~RenderEngine();

	/**
	 * \brief Sets the GameEngine object thats used for drawing.
	 * 
	 * \param ge Pointer to a GameEngine object.
	 * \return true if GameEngine is valid else false.
	 */

	static bool InitRenderImage(GameEngine * ge);
	
	/**
	 * \brief Adds a layer to the render.
	 * 
	 * \param layer The layer to add.
	 * \see RenderLayer
	 */

	void AddLayer(RenderLayer * layer);

	/**
	 * \brief Remove the given layer.
	 * 
	 * \param id The ID of the layer to remove.
	 */

	void RemoveLayer(const int &id);

	/**
	 * \brief Updates the layers.
	 * 
	 *  Removes any nullptrs and sorts the layers into order using Sort.
	 * 
	 */

	void Update();

	/**
	 * \brief Draws all the layers.
	 * 
	 */

	void DrawLayers();

	/**
	 * \brief Draws a single layer.
	 * 
	 * \param layer The layer to be drawn.
	 */

	void DrawLayer(RenderLayer * layer);


private:

	std::vector<RenderLayer*> m_layers; //!< Layers to be drawn.
	static GameEngine * p_gameEngine; //!< Pointer to the GameEngine that is used.

};