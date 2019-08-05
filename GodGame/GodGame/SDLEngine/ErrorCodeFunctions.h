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

inline std::string Err_200_RendererNoInit_strFunc(const EngineErrorMessage & err) {
	//TODO Add better error message for Renderer Init fail.
	return std::string(err.msg);
}

inline std::string Err_201_RendererNoUpdate_strFunc(const EngineErrorMessage & err) {
	//TODO Add better error message for Renderer update fail.
	return std::string(err.msg);
}

inline std::string Err_202_RendererNoDraw_strFunc(const EngineErrorMessage & err) {
	//TODO Add better error message for Renderer Draw fail.
	return std::string(err.msg);
}