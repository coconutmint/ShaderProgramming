#pragma once
#include "Global.h"
#include "Renderer.h"
#include "GSEObjectMgr.h"
#include <iostream>

class CGame
{

public:
	CGame(GSEVec2 size);
	~CGame();
	void RenderScene();
	void UpdateObjects(GSEKeyboardMapper keyMap, float eTime);

private:
	Renderer* m_renderer = NULL;
	GSEObjectMgr* m_objectMgr = NULL;
	int m_heroID = -1;
};

