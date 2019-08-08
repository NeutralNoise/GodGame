#pragma once

//TODO Change to static or write class to load from file and store config values.

#define SECOND_MICRO_SECONDS 1000		//!< Microsecond to second convertion.

const int TILE_SIZE = 32;
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const int MAX_FPS = 60;
const float MAX_FRAME_TIME = (SECOND_MICRO_SECONDS / MAX_FPS);
