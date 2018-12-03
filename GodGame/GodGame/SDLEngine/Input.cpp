#include "Input.h"
#include <SDL2/SDL.h>

Input::Input()
{
}


Input::~Input()
{
}

void Input::ProcessEvents() {

	SDL_Event m_e;
	while (SDL_PollEvent(&m_e) != 0) {

		switch (m_e.type)
		{
		case::SDL_QUIT:
			m_events.push_back(InputEvent(m_e.type));
			return;
		case SDL_MOUSEMOTION:
			break;
		case SDL_KEYDOWN:
			PressedKey(m_e.key.keysym.sym);
			{
				bool pressed = false;
				if (IsInputDown(m_e.key.keysym.sym)) {
					pressed = true;
				}
				m_events.push_back(InputEvent(m_e.type, m_e.key.keysym.sym, pressed));
			}
			break;
		case SDL_KEYUP:
			ReleasedKey(m_e.key.keysym.sym);
			m_events.push_back(InputEvent(m_e.type, m_e.key.keysym.sym));
			break;
		default:
			break;
		}
	}
}

InputEvent Input::GetNextEvent() {

	if (m_events.size() != 0) {
		InputEvent rtn = m_events[0];
		m_events.erase(m_events.begin());
		return rtn;
	}
	return InputEvent();
}

bool Input::IsInputDown(const UInt32 &keyID) {
	const auto iter = m_keyMap.find(keyID);

	if (iter != m_keyMap.end()) {
		return iter->second;
	}
	return false;
}

bool Input::IsInputPressed(const UInt32 &keyID) {
	if (IsInputDown(keyID) && !WasInputDown(keyID)) {
		return true;
	}
	return false;
}

void Input::Update() {
	for (auto iter = m_keyMap.begin(); iter != m_keyMap.end(); iter++) {
		m_previousKeyMap[iter->first] = iter->second;
	}
}


bool Input::WasInputDown(unsigned int keyID) {
	std::unordered_map<unsigned int, bool>::const_iterator iter = m_previousKeyMap.find(keyID);

	if (iter != m_previousKeyMap.end()) {
		return iter->second;
	}
	else {
		return false;
	}

}