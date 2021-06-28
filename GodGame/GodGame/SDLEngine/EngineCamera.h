#pragma once
#include "Rect.h"
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

/** \struct EngineCamera
 * \brief A structure representing a camera.
 * 
 */

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
		projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f);
		scale = 1.0f;
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

	EngineCamera(const float &x, const float &y, const float &width, const float &height, float scale = 1.0f) {
		pos = Rect(x,y,width, height);
		halfWidth = width / 2;
		halfHeight = height / 2;
		centerPos.x = pos.x + halfWidth;
		centerPos.y = pos.y+ halfHeight;
		this->scale = scale;
		projection = glm::ortho(0.0f, width, height, 0.0f);
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
		centerPos.x = pos.x + halfWidth;
		centerPos.y = pos.y + halfHeight;
		glm::vec3 translate(-pos.x + centerPos.x, -pos.y + centerPos.y, 0.0f);
		cameraMatrix = glm::translate(projection, translate);

		//scale the camera.
		glm::vec3 newScale(scale, scale, 0.0f);
		cameraMatrix = glm::scale(glm::mat4(1.0f), newScale) * cameraMatrix;
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
		float x1Min = rect.x - rect.width;
		float x1Max = rect.x + rect.width;
		float y1Max = rect.y + rect.height;
		float y1Min = rect.y - rect.height;

		// AABB 2		
		/*
		float x2Min = pos.x - rect.width;
		float x2Max = pos.x + pos.width;
		float y2Max = pos.y + pos.height;
		float y2Min = pos.y - rect.height;
		*/

		float x2Min = (pos.x - halfWidth);
		float x2Max = (pos.x + halfWidth);
		float y2Max = (pos.y + halfHeight);
		float y2Min = (pos.y - halfHeight);

		// Collision tests
		if (x1Max < x2Min || x1Min > x2Max) return false;
		if (y1Max < y2Min || y1Min > y2Max) return false;

		return true;
	}

	glm::mat4 projection; //!< The cameras projection matrix.
	glm::mat4 cameraMatrix;	//!< The cameras view matrix.
	Rect pos;	//!< The position of the camera in world space.
	Rect centerPos; //!< The center of the camera in world space.
	float scale; //!< Used for zoom. \warning not currently used.

	float halfWidth = 0;
	float halfHeight = 0;
};