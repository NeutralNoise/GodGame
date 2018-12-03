#pragma once

struct Rect {
	int x;
	int y;
	int width;
	int height;

	Rect() {
		x = 0;
		y = 0;
		width = 0;
		height = 0;
	}


	Rect(const int &x, const int &y, const int &width, const int &height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

};