#include "stdafx.h"
#include "CGame.h"
#include "GSEObject.h"

CGame::CGame(GSEVec2 size)
{
	m_renderer = new Renderer((int)size.x, (int)size.y);
	m_objectMgr = new GSEObjectMgr();

	//test

	for(int i = 0; i < MAX_OBJECT_COUNT; i++) 
	{
		GSEVec3 objpos = { 0,0,0 };
		GSEVec3 objsize = { 100,10,10 };
		objpos.x = ((float)std::rand() / (float)RAND_MAX - 0.5f) * 2.f * 250.f;
		objpos.y = ((float)std::rand() / (float)RAND_MAX - 0.5f) * 2.f * 250.f;
		objsize.x = ((float)std::rand() / (float)RAND_MAX) * 5.f;
		m_objectMgr->AddObject(objpos, objsize);
	}
}
CGame::~CGame()
{
	if (m_renderer)
	{
		delete m_renderer;
		m_renderer = NULL;
	}
	if (m_objectMgr)
	{
		delete m_objectMgr;
		m_objectMgr = NULL;
	}
}

void CGame::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	for (int i = 0; i < MAX_OBJECT_COUNT;i++)
	{
		GSEObject temp = m_objectMgr->GetObject(i); //temp 복사가 일어남 그래서 이 함수가 끝나기 전까지는 temp값 유지
		GSEVec3 pos = temp.GetPos();
		GSEVec3 size = temp.GetSize();
		if (size.x > 0.0000001f) //float 값이 가질 수 있는 가장 작은 값 넣는 변수 넣기
		{
			m_renderer->DrawSolidRect(pos.x, pos.y, pos.z, size.x, 1, 0, 1, 1);
		}
	}
}
