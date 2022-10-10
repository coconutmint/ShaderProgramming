#pragma once
#include "Global.h"
#include "Renderer.h"
#include "GSEObjectMgr.h"

class CGame
{

public:
	CGame(GSEVec2 size);
	~CGame();
	void RenderScene();

private:
	Renderer* m_renderer = NULL;
	GSEObjectMgr* m_objectMgr = NULL;
};

