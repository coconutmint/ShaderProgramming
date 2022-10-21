#pragma once

#define MAX_OBJECT_COUNT 1000

struct GSEVec2 {
	float x, y;
};

struct GSEVec3 {
	float x, y, z;
};

struct GSEKeyboardMapper {
	bool W_Key = false;
	bool A_Key = false;
	bool S_Key = false;
	bool D_Key = false;
};