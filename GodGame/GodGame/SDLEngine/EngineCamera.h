#pragma once
#include "Rect.h"

struct EngineCamera
{	
	/**
	 * \brief Construct a new EngineCamera object
	 * 
	 */
	EngineCamera() {
		pos = Rect();
		scale = 0.0f;
		centerPos = Rect();
	}

	/**
	 * \brief Construct a new EngineCamera object
	 * 
	 * \param x The X position in world space.
	 * \param y The Y position in world space.
	 * \param width The width of the camera. \note Make sure its the same as the window size.
	 * \param height The width of the camera. \note Make sure its the same as the window size.
	 * \param scale the zoom of the camera. \warning not currently used.
	 */

	EngineCamera(const int &x, const int &y, const int &width, const int &height, float scale = 1.0f) {
		pos = Rect(x,y,width, height);
		centerPos.x = pos.x + width / 2;
		centerPos.y = pos.y+ height / 2;
		this->scale = scale;
	}

	/**
	 * \brief Destroy the EngineCamera object
	 * 
	 */

	~EngineCamera() {

	}

	/**
	 * \brief Move the camera to a given position.
	 * 
	 * \param pos The position in world space to move the camera.
	 */

	void MoveCamera(const Rect &pos) {
		this->pos = pos;
		centerPos.x = pos.x + pos.width / 2;
		centerPos.y = pos.y + pos.height / 2;
	}

	/**
	 * \brief Translates the worldspace with camera space.
	 * 
	 * Not sure how to explain this. Basicly it just makes sure something in world space is displayed at the right spot in screen space.
	 * 
	 * \param p The position to translate.
	 * \return The new position as a Rect. \see Rect
	 */

	Rect TranslateWithCamera(const Rect &p) {
		Rect rtn;
		rtn.height = p.height;
		rtn.width = p.width;

		rtn.x = p.x - pos.x;
		rtn.y = p.y - pos.y;

		return rtn;
	}

	/**
	 * \brief Checks if the given position is within the cameras bounds.
	 * 
	 * \param rect The position to check.
	 * \return true if a collision is detected else false.
	 */

	bool CollisionWithCamera(const Rect &rect) {

		//code taken from
		//https://stackoverflow.com/questions/6083626/box-collision-code
		// AABB 1
		int x1Min = rect.x;
		int x1Max = rect.x + rect.width;
		int y1Max = rect.y + rect.height;
		int y1Min = rect.y;

		// AABB 2
		//Whats with this.
		int x2Min = pos.x - 32;
		//Not relly sure why i have to * 2 but i do :/
		int x2Max = pos.x + (pos.width * 2);
		int y2Max = pos.y + (pos.height * 2);
		int y2Min = pos.y - 32;

		// Collision tests
		if (x1Max < x2Min || x1Min > x2Max) return false;
		if (y1Max < y2Min || y1Min > y2Max) return false;

		return true;
	}


	Rect pos;	//!< The position of the camera in world space.
	Rect centerPos; //!< The center of the camera in world space.
	float scale; //!< Used for zoom. \warning not currently used.

};