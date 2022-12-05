#pragma once

#define MAX_OBJECT_COUNT 1000
#define GRAVITY 9.8f
#define OBJ_TYPE_NORMAL 0
#define OBJ_TYPE_BULLET 1
#define OBJ_TYPE_HERO   2

struct GSEVec2 {
	float x = 0.f, y = 0.f;
};

struct GSEVec3 {
	float x = 0.f, y = 0.f, z = 0.f;
};

struct GSEVec4 {
	float x = 0.f, y = 0.f, z = 0.f, w = 0.f;
};

struct GSEKeyboardMapper {
	bool W_Key = false;
	bool A_Key = false;
	bool S_Key = false;
	bool D_Key = false;
	bool Up_Key = false;
	bool Down_Key = false;
	bool Left_Key = false;
	bool Right_Key = false;
};