#pragma once
#include "Rect.h"

struct EngineCamera
{
	EngineCamera() {
		pos = Rect();
		scale = 0.0f;
		centerPos = Rect();
	}

	EngineCamera(const int &x, const int &y, const int &width, const int &height, float scale = 1.0f) {
		pos = Rect(x,y,width, height);
		centerPos.x = pos.x + width / 2;
		centerPos.y = pos.y+ height / 2;
		this->scale = scale;
	}

	~EngineCamera() {

	}

	void MoveCamera(const Rect &pos) {
		this->pos = pos;
		centerPos.x = pos.x + pos.width / 2;
		centerPos.y = pos.y + pos.height / 2;
	}

	Rect TranslateWithCamera(const Rect &p) {
		Rect rtn;
		rtn.height = p.height;
		rtn.width = p.width;

		rtn.x = p.x - pos.x;
		rtn.y = p.y - pos.y;

		return rtn;
	}

	bool CollisionWithCamera(const Rect &rect) {

		//code taken from
		//https://stackoverflow.com/questions/6083626/box-collision-code
		// AABB 1
		int x1Min = rect.x;
		int x1Max = rect.x + rect.width;
		int y1Max = rect.y + rect.height;
		int y1Min = rect.y;

		// AABB 2
		int x2Min = pos.x;
		//Not relly sure why i have to * 2 but i do :/
		int x2Max = pos.x + (pos.width * 2);
		int y2Max = pos.y + (pos.height * 2);
		int y2Min = pos.y;

		// Collision tests
		if (x1Max < x2Min || x1Min > x2Max) return false;
		if (y1Max < y2Min || y1Min > y2Max) return false;

		return true;
	}


	Rect pos;
	Rect centerPos;
	float scale;

};