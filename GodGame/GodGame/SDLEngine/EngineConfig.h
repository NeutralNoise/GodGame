#pragma once

//TODO Change to static or write class to load from file and store config values.

#define SECOND_MICRO_SECONDS 1000		//!< Microsecond to second convertion.

const int TILE_SIZE = 32; //!< The size of each tile in pixels.
const int WINDOW_WIDTH = 600; //!< The width of the window.
const int WINDOW_HEIGHT = 600; //!< The height of the window.
const int MAX_FPS = 60; //!< The max frame rate to get too.
const float MAX_FRAME_TIME = (SECOND_MICRO_SECONDS / MAX_FPS); //!< The max time each frame should take.
