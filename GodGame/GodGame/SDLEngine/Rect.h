#pragma once

/** \struct Rect
 * \brief A structure representing a square/rectangle in 2D space.
 * \warning This might be replaced later with a typedef of SDL_Rect.
*/

struct Rect {
	float x; //!< The X position of the square/rectangle.
	float y; //!< The Y position of the square/rectangle.
	float width; //!< The wight of the square/rectangle in the X axis.
	float height; //!< The height of the square/rectangle in the Y axis.

	/**
	 * \brief Construct a new Rect object
	 * 
	*/

	Rect() {
		x = 0;
		y = 0;
		width = 0;
		height = 0;
	}

	/**
	 * \brief Construct a new Rect object
	 * 
	 * \param x The X position of the square/rectangle.
	 * \param y The Y position of the square/rectangle.
	 * \param width The wight of the square/rectangle in the X axis.
	 * \param height The height of the square/rectangle in the Y axis.
	*/

	Rect(const float &x, const float &y, const float &width, const float &height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

};

struct Point
{
	float x, y;

	Point() {
		x = 0;
		y = 0;
	}

	Point(const float &x, const float &y) {
		this->x = x;
		this->y = y;
	}

};