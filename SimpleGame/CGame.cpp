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
	m_objectMgr->GetObject(m_heroID)->SetType(OBJ_TYPE_HERO);

	//test
	/*for (int i = 0; i < MAX_OBJECT_COUNT; i++)
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
	}*/
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
		GSEObject *temp = m_objectMgr->GetObject(i); //temp 복사가 일어남 그래서 이 함수가 끝나기 전까지는 temp값 유지
		if (temp != NULL)
		{
			GSEVec3 pos = temp->GetPos();
			GSEVec3 size = temp->GetSize();
			if (size.x > 0.0000001f) //float 값이 가질 수 있는 가장 작은 값 넣는 변수 넣기
			{
				m_renderer->DrawSolidRect(pos.x, pos.y, pos.z, size.x, 1, 0, 1, 1);
			}
		}
	}
}

void CGame::UpdateObjects(GSEKeyboardMapper keyMap, float eTime)
{
	//add force
	if (keyMap.W_Key || keyMap.A_Key || keyMap.S_Key || keyMap.D_Key)
	{
	float movingHeroForce = 1500.f;
	GSEVec3 heroForceDirection;
	if (keyMap.W_Key)
	{
		heroForceDirection.y += 1.f;
	}
	if (keyMap.A_Key)
	{
		heroForceDirection.x -= 1.f;
	}
	if (keyMap.S_Key)
	{
		heroForceDirection.y -= 1.f;
	}
	if (keyMap.D_Key)
	{
		heroForceDirection.x += 1.f;
	}
	heroForceDirection.x *= movingHeroForce;
	heroForceDirection.y *= movingHeroForce;
	heroForceDirection.z *= movingHeroForce;
	m_objectMgr->AddForce(m_heroID, heroForceDirection, eTime);
	}

	//Fire bullet
	if (keyMap.Up_Key || keyMap.Down_Key || keyMap.Left_Key || keyMap.Right_Key)
	{

		float firingBulletForce = 1000.f;
		GSEVec3 bulletForceDirection;
		if (keyMap.Up_Key)
		{
			bulletForceDirection.y += 1.f;
		}
		if (keyMap.Left_Key)
		{
			bulletForceDirection.x -= 1.f;
		}
		if (keyMap.Down_Key)
		{
			bulletForceDirection.y -= 1.f;
		}
		if (keyMap.Right_Key)
		{
			bulletForceDirection.x += 1.f;
		}
		bulletForceDirection.x *= firingBulletForce;
		bulletForceDirection.y *= firingBulletForce;
		bulletForceDirection.z *= firingBulletForce;
		if (FLT_EPSILON < std::fabs(bulletForceDirection.x) + std::fabs(bulletForceDirection.y)
			+ std::fabs(bulletForceDirection.z))
		{
			GSEVec3 bulletobjPos = { 0,0,0 };
			GSEVec3 bulletobjSize = { 10,10,10 };
			GSEVec3 bulletobjVel = { 0,0,0 };
			GSEVec3 bulletobjAcc = { 0,0,0 };
			float  bulletobjMass = 0.1f;
			int bulletID = m_objectMgr->AddObject(bulletobjPos, bulletobjSize, bulletobjVel, bulletobjAcc, bulletobjMass);

			if (bulletID >= 0)
			{
				GSEVec3 heroPos;
				heroPos = m_objectMgr->GetObject(m_heroID)->GetPos();
				m_objectMgr->GetObject(bulletID)->SetPos(heroPos);
				m_objectMgr->GetObject(bulletID)->SetFricCoef(2.f);
				m_objectMgr->GetObject(bulletID)->SetType(OBJ_TYPE_BULLET);
				m_objectMgr->AddForce(bulletID, bulletForceDirection, 0.1f);
			}
		}
			
		
		
	}
	//Update
	if (m_objectMgr != NULL)
	{
		m_objectMgr->UpdateObjects(eTime);
	}
	else
	{
		//강제로 죽게하는 asset추가해보기
		std::cout << "m_objectMgr is NULL" << std::endl;
	}
	m_objectMgr->DoGarbageCollect();
}
