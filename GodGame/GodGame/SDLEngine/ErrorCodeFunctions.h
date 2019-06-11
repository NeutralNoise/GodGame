#pragma once
#include <string>
#include "ErrorEngine.h"

inline std::string Err_150_FontFail(const EngineErrorMessage & err) {
	return std::string("SDL2_TTF Failed to load font file.\n SDL2_TTF error: " + err.msg);
}

inline std::string Err_151_FontRenderFail(const EngineErrorMessage & err) {
	return std::string("SDL2_TTF failed to render text to texture\n SDL2_TTF error: " + err.msg);
}
