#pragma once

//TODO Change to static or write class to load from file and store config values.

#define SECOND_MICRO_SECONDS 1000		//!< Microsecond to second convertion.

const int TILE_SIZE = 32; //!< The size of each tile in pixels.
const int WINDOW_WIDTH = 600; //!< The width of the window.
const int WINDOW_HEIGHT = 600; //!< The height of the window.
const int MAX_FPS = 60; //!< The max frame rate to get too.
const float MAX_FRAME_TIME = (SECOND_MICRO_SECONDS / MAX_FPS); //!< The max time each frame should take.

const unsigned int MAX_RENDER_OBJECTS = 10000; //!< The maximum number of RenderObjects in one batch.
const unsigned int MAX_BATCH_VERTICES = 4 * MAX_RENDER_OBJECTS; //!< The maximum number of vertices to be rendered.
const unsigned int NUM_BATCH_INDICES_PER_QUARD = 6; //!< Number of indices that make up quard.
const unsigned int MAX_BATCH_INDICES = NUM_BATCH_INDICES_PER_QUARD * MAX_RENDER_OBJECTS; //!< The maximum number of indices.
const unsigned int MAX_TEXTURE_UNITS = 32;