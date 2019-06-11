#pragma once
#include <string>
#include "ErrorEngine.h"

inline EngineErrorMessage Err_150_FontFail_onAdd(const std::string & msg) {
	return EngineErrorMessage(150, EngineErrorTypes::ERR_TYPE_FATEL, msg);
}

inline std::string Err_150_FontFail_strFunc(const EngineErrorMessage & err) {
	return std::string("SDL2_TTF Failed to load font file.\nSDL2_TTF error: " + err.msg);
}

inline EngineErrorMessage Err_151_FontRenderFail_onAdd(const std::string & msg) {
	return EngineErrorMessage(151, EngineErrorTypes::ERR_TYPE_FATEL, msg);
}

inline std::string Err_151_FontRenderFail_strFunc(const EngineErrorMessage & err) {
	return std::string("SDL2_TTF failed to render text to texture\nSDL2_TTF error: " + err.msg);
}
