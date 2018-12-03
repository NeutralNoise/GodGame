#pragma once

//This is a strait copy from SDL2 SDL_events.h
//This way i can use these or the sdl ones which ever i like and it makes it more mapable to other systems later.
enum EngineEventType
{
	EE_FIRSTEEVNT = 0, /**< Unused (do not remove) */
	/* Application events */
	EE_QUIT = 0x100, /**< User-requested quit */

	/* These application events have special meaning on iOS, see README-ios.md for details */
	EE_APP_TERMINATING,        /**< The application is being terminated by the OS
									 Called on iOS in applicationWillTerminate()
									 Called on Android in onDestroy()
								*/
	EE_APP_LOWMEMORY,          /**< The application is low on memory, free memory if possible.
									 Called on iOS in applicationDidReceiveMemoryWarning()
									 Called on Android in onLowMemory()
								*/
	EE_APP_WILLENTERBACKGROUND, /**< The application is about to enter the background
									 Called on iOS in applicationWillResignActive()
									 Called on Android in onPause()
								*/
	EE_APP_DIDENTERBACKGROUND, /**< The application did enter the background and may not get CPU for some time
									 Called on iOS in applicationDidEnterBackground()
									 Called on Android in onPause()
								*/
	EE_APP_WILLENTERFOREGROUND, /**< The application is about to enter the foreground
									 Called on iOS in applicationWillEnterForeground()
									 Called on Android in onResume()
								*/
	EE_APP_DIDENTERFOREGROUND, /**< The application is now interactive
									 Called on iOS in applicationDidBecomeActive()
									 Called on Android in onResume()
								*/

	/* Display events */
	EE_DISPLAYEVENT = 0x150,  /**< Display state change */

	/* Window events */
	EE_WINDOWEVENT = 0x200, /**< Window state change */
	EE_SYSWMEVENT,             /**< System specific event */

	/* Keyboard events */
	EE_KEYDOWN = 0x300, /**< Key pressed */
	EE_KEYUP,                  /**< Key released */
	EE_TEXTEDITING,            /**< Keyboard text editing (composition) */
	EE_TEXTINPUT,              /**< Keyboard text input */
	EE_KEYMAPCHANGED,          /**< Keymap changed due to a system event such as an
										input language or keyboard layout change.
								*/

	/* Mouse events */
	EE_MOUSEMOTION = 0x400, /**< Mouse moved */
	EE_MOUSEBUTTONDOWN,        /**< Mouse button pressed */
	EE_MOUSEBUTTONUP,          /**< Mouse button released */
	EE_MOUSEWHEEL,             /**< Mouse wheel motion */

	/* Joystick events */
	EE_JOYAXISMOTION = 0x600, /**< Joystick axis motion */
	EE_JOYBALLMOTION,          /**< Joystick trackball motion */
	EE_JOYHATMOTION,           /**< Joystick hat position change */
	EE_JOYBUTTONDOWN,          /**< Joystick button pressed */
	EE_JOYBUTTONUP,            /**< Joystick button released */
	EE_JOYDEVICEADDED,         /**< A new joystick has been inserted into the system */
	EE_JOYDEVICEREMOVED,       /**< An opened joystick has been removed */

	/* Game controller events */
	EE_CONTROLLERAXISMOTION = 0x650, /**< Game controller axis motion */
	EE_CONTROLLERBUTTONDOWN,          /**< Game controller button pressed */
	EE_CONTROLLERBUTTONUP,            /**< Game controller button released */
	EE_CONTROLLERDEVICEADDED,         /**< A new Game controller has been inserted into the system */
	EE_CONTROLLERDEVICEREMOVED,       /**< An opened Game controller has been removed */
	EE_CONTROLLERDEVICEREMAPPED,      /**< The controller mapping was updated */

	/* Touch events */
	EE_FINGERDOWN = 0x700,
	EE_FINGERUP,
	EE_FINGERMOTION,

	/* Gesture events */
	EE_DOLLARGESTURE = 0x800,
	EE_DOLLARRECORD,
	EE_MULTIGESTURE,

	/* Clipboard events */
	EE_CLIPBOARDUPDATE = 0x900, /**< The clipboard changed */

	/* Drag and drop events */
	EE_DROPFILE = 0x1000, /**< The system requests a file open */
	EE_DROPTEXT,                 /**< text/plain drag-and-drop event */
	EE_DROPBEGIN,                /**< A new set of drops is beginning (NULL filename) */
	EE_DROPCOMPLETE,             /**< Current set of drops is now complete (NULL filename) */

	/* Audio hotplug events */
	EE_AUDIODEVICEADDED = 0x1100, /**< A new audio device is available */
	EE_AUDIODEVICEREMOVED,        /**< An audio device has been removed. */

	/* Sensor events */
	EE_SENSORUPDATE = 0x1200,     /**< A sensor was updated */

	/* Render events */
	EE_RENDER_TARGETS_RESET = 0x2000, /**< The render targets have been reset and their contents need to be updated */
	EE_RENDER_DEVICE_RESET, /**< The device has been reset and all textures need to be recreated */

	/** Events ::SDL_USEREVENT through ::SDL_LASTEVENT are for your use,
		*  and should be allocated with SDL_RegisterEvents()
		*/
	EE_USEREVENT = 0x8000,

	/**
	 *  This last event is only for bounding internal arrays
	 */
	EE_LASTEVENT = 0xFFFF
};

struct InputEvent
{
	int type = -1;
	unsigned int keyID = 0;
	bool isHeld = false;

	InputEvent() {

	}

	InputEvent(const int &type, const UInt32 &keyID = 0, const bool &isHeld = false) {
		this->type = type;
		this->keyID = keyID;
		this->isHeld = isHeld;
	}

};