#pragma once
#include <unordered_map>
#include <vector>
#include "typedefs.h"
#include "EngineEvents.h"

/** \class Input
 * \brief Handle input from keys and mouse.
 * 
 */

class Input
{
public:

	/**
	 * \brief Construct a new Input object
	 * 
	*/

	Input();

	/**
	 * \brief Destroy the Input object
	 * 
	*/
	 
	~Input();

	
	/**
	 * \brief Checks to see if a new envent has happened.
	 * 
	*/

	void ProcessEvents();

	/**
	 * \brief Get the next event that has happened.
	 * 
	 * \return A copy of the next event. \see InputEvent
	*/

	InputEvent GetNextEvent();

	/**
	 * \brief Checks if a key is held down.
	 * 
	 * \param keyID The ID of the key. \warning currently this just uses the SDL2 IDs.
	 * \return true if the key is held down else false.
	*/

	bool IsInputDown(const UInt32 &keyID);

	/**
	 * \brief Checks if a key was pressed atlest once.
	 * 
	 * \param keyID The ID of the key. \warning currently this just uses the SDL2 IDs.
	 * \return true if a key was pressed atlest once else false.
	*/

	bool IsInputPressed(const UInt32 &keyID);

	/**
	 * \brief Updates the keymap of pressed keys.
	 * 
	*/

	void Update();

private:

	/**
	 * \brief Sets a key as pressed in the key map.
	 * 
	 * \param keyID The ID of the key to set as pressed.
	*/

	void PressedKey(const UInt32 &keyID) { m_keyMap[keyID] = true; };

	/**
	 * \brief Sets a key as released in the key map.
	 * 
	 * \param keyID The ID of the key to set as released.
	*/

	void ReleasedKey(const UInt32 &keyID) { m_keyMap[keyID] = false; };

	/**
	 * \brief Checks if a key was pressed in the last update or not.
	 * 
	 * \param keyID The ID of the key to check.
	 * \return true if the key was pressed in the last update.
	*/

	bool WasInputDown(unsigned int keyID);

	std::unordered_map<UInt32, bool> m_keyMap; //!< Keys pressed this update.
	std::unordered_map<UInt32, bool> m_previousKeyMap; //!< keys pressed in the last update.
	std::vector<InputEvent> m_events; //!< The events that have came in. First in First Out
};

