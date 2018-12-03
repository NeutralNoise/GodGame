#pragma once
#include <unordered_map>
#include <vector>
#include "typedefs.h"
#include "EngineEvents.h"

class Input
{
public:
	Input();
	~Input();

	
	void ProcessEvents();
	InputEvent GetNextEvent();
	bool IsInputDown(const UInt32 &keyID);
	bool IsInputPressed(const UInt32 &keyID);
	void Update();

private:
	void PressedKey(const UInt32 &keyID) { m_keyMap[keyID] = true; };
	void ReleasedKey(const UInt32 &keyID) { m_keyMap[keyID] = false; };
	bool WasInputDown(unsigned int keyID);

	std::unordered_map<UInt32, bool> m_keyMap;
	std::unordered_map<UInt32, bool> m_previousKeyMap;
	std::vector<InputEvent> m_events;
};

