# Error message codes.

## 100 > 199 Main Engine/SDL2

* 100 SDL2 failed to start.
* 101 SDL2 failed to create a window.
* 102 SDL2 failed to create a renderer.
* 103 SDL2_Image failed to start.
* 104 SDL_TTF failed to start.
* 105 > 110 Resurved for other sytem start ups.
* 111 SDL2 Unable to create surface from texture.
* 150 SDL2_TTF failed to load font file.
* 151 SDL2_TTF failed to render text to texture.

## 200 > 299 Render Engine
* 200 RenderEngine can not be passed a nullptr.

## 300 > 399 FontEngine/InfoEngine
* 300 InfoEngine can not add given info. Because it is already there.
* 301 Unable to find InfoEngine with the given name.
* 302 > 305 Resurved
* 306 Unable to load new font because memory issue.

## 900 > 999 MISC

* 900 Failed to create new EngineFont cause memory:
* 901 Failed to create new Texture cause memory.
