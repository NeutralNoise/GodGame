#pragma once

/** \struct Rect
 * \brief A structure representing a square/rectangle in 2D space.
 * \warning This might be replaced later with a typedef of SDL_Rect.
*/

struct Rect {
	int x; //!< The X position of the square/rectangle.
	int y; //!< The Y position of the square/rectangle.
	int width; //!< The wight of the square/rectangle in the X axis.
	int height; //!< The height of the square/rectangle in the Y axis.

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

	Rect(const int &x, const int &y, const int &width, const int &height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

};