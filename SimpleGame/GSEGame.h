#pragma once
#include "Global.h"
#include "Renderer.h"
#include "GSEObjectMgr.h"
#include "Sound.h"
#include <iostream>

class GSEGame
{

public:
	GSEGame(GSEVec2 size);
	~GSEGame();
	void RenderScene();
	void UpdateObjects(GSEKeyboardMapper keyMap, float eTime);
	bool BBCollision(GSEVec3 minA, GSEVec3 maxA, GSEVec3 minB, GSEVec3 maxB);
private:
	Renderer* m_renderer = NULL;
	GSEObjectMgr* m_objectMgr = NULL;
	Sound* m_soundMgr = NULL;
	int m_heroID = -1;
	int m_heroTextureID = -1;
	int m_bulletTextureID = -1;
	int m_fireAnimTextureID = -1;
	int m_groundTextureID = -1;
	int m_bgSound = -1;
	int m_explSound = -1;
	int m_fireSound = -1;
	int m_climateParticle = -1;
	int m_fireParticle = -1;
};

