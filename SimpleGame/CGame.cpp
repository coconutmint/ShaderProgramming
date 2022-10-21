#include "stdafx.h"
#include "CGame.h"
#include "GSEObject.h"

CGame::CGame(GSEVec2 size)
{
	m_renderer = new Renderer((int)size.x, (int)size.y);
	m_objectMgr = new GSEObjectMgr();

	//Create hero object
	GSEVec3 heroobjPos = { 0,0,0 };
	GSEVec3 heroobjSize = { 100,10,10 };
	GSEVec3 heroobjVel = { 0,0,0 };
	GSEVec3 heroobjAcc = { 0,0,0 };
	float  heroobjMass = 1.f;
	m_heroID = m_objectMgr->AddObject(heroobjPos, heroobjSize, heroobjVel, heroobjAcc, heroobjMass);
	//test

	for(int i = 0; i < MAX_OBJECT_COUNT; i++) 
	{
		GSEVec3 objPos = { 0,0,0 };
		GSEVec3 objSize = { 100,10,10 };
		GSEVec3 objVel = { 100,10,10 };
		GSEVec3 objAcc = { 100,10,10 };
		float objMass = 1.f;
		objPos.x = ((float)std::rand() / (float)RAND_MAX - 0.5f) * 2.f * 250.f;
		objPos.y = ((float)std::rand() / (float)RAND_MAX - 0.5f) * 2.f * 250.f;
		objSize.x = ((float)std::rand() / (float)RAND_MAX) * 5.f;
	
		objVel.x = ((float)std::rand() / (float)RAND_MAX - 0.5f) * 2.f * 3.f;
		objVel.y = ((float)std::rand() / (float)RAND_MAX - 0.5f) * 2.f * 3.f;
		objVel.z = 0.f;

		m_objectMgr->AddObject(objPos, objSize, objVel, objAcc, objMass);
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
		GSEObject temp = m_objectMgr->GetObject(i); //temp ���簡 �Ͼ �׷��� �� �Լ��� ������ �������� temp�� ����
		GSEVec3 pos = temp.GetPos();
		GSEVec3 size = temp.GetSize();
		if (size.x > 0.0000001f) //float ���� ���� �� �ִ� ���� ���� �� �ִ� ���� �ֱ�
		{
			m_renderer->DrawSolidRect(pos.x, pos.y, pos.z, size.x, 1, 0, 1, 1);
		}
	}
}

void CGame::UpdateObjects(GSEKeyboardMapper keyMap, float eTime)
{
	if (m_objectMgr != NULL)
	{
		m_objectMgr->UpdateObjects(eTime);
	}
	else
	{
		//������ �װ��ϴ� asset�߰��غ���
		std::cout << "m_objectMgr is NULL" << std::endl;
	}
}
