#include "stdafx.h"
#include "GSEGame.h"
#include "GSEObject.h"

GSEGame::GSEGame(GSEVec2 size)
{
	m_renderer = new Renderer((int)size.x, (int)size.y);
	m_objectMgr = new GSEObjectMgr();
	m_soundMgr = new Sound();

	//create Textures
	m_heroTextureID = m_renderer->GenPngTexture("./Textures/dd.png");
	m_bulletTextureID = m_renderer->GenPngTexture("./Textures/dd.png");
	m_fireAnimTextureID = m_renderer->GenPngTexture("./Textures/gg.png");

	//Create Sounds
	m_bgSound = m_soundMgr->CreateBGSound("./Sounds/bg.mp3");
	m_explSound = m_soundMgr->CreateShortSound("./Sounds/explosion.mp3");
	m_fireSound = m_soundMgr->CreateShortSound("./Sounds/firing.mp3");

	m_soundMgr->PlayBGSound(m_bgSound, true, 1.f);
	//Create hero object
	GSEVec3 heroobjPos = { 0,0,0 };
	GSEVec3 heroobjSize = { 120,120,40 };
	GSEVec3 heroobjVel = { 0,0,0 };
	GSEVec3 heroobjAcc = { 0,0,0 };
	float  heroobjMass = 1.f;
	int  heroHP = 1000;
	m_heroID = m_objectMgr->AddObject(heroobjPos, heroobjSize, heroobjVel, heroobjAcc, heroobjMass);
	m_objectMgr->GetObject(m_heroID)->SetType(OBJ_TYPE_HERO);
	m_objectMgr->GetObject(m_heroID)->SetHP(heroHP);
	m_objectMgr->GetObject(m_heroID)->SetMaxHP(heroHP);
	m_objectMgr->GetObject(m_heroID)->SetTextureID(m_heroTextureID);
	m_objectMgr->GetObject(m_heroID)->SetDrawGauge(true);

	//Create temp object
	GSEVec3 testobjPos = { 100,0,0 };
	GSEVec3 testobjSize = { 60, 60, 60 };
	GSEVec3 testobjVel = { 0,0,0 };
	GSEVec3 testobjAcc = { 0,0,0 };
	float  testobjMass = 1.f;
	int  testHP = 500;
	int testObjID = m_objectMgr->AddObject(testobjPos, testobjSize, testobjVel, testobjAcc, heroobjMass);
	m_objectMgr->GetObject(testObjID)->SetType(OBJ_TYPE_NORMAL);
	m_objectMgr->GetObject(testObjID)->SetHP(testHP);
	m_objectMgr->GetObject(testObjID)->SetMaxHP(testHP);
	m_objectMgr->GetObject(testObjID)->SetDrawGauge(true);
	m_objectMgr->GetObject(testObjID)->SetTextureID(m_fireAnimTextureID);

	testobjPos.x = 100;
	testobjPos.y = 100;
	testobjPos.z = 0;
	testObjID = m_objectMgr->AddObject(testobjPos, testobjSize, testobjVel, testobjAcc, heroobjMass);
	m_objectMgr->GetObject(testObjID)->SetType(OBJ_TYPE_NORMAL);
	m_objectMgr->GetObject(testObjID)->SetHP(testHP);
	m_objectMgr->GetObject(testObjID)->SetMaxHP(testHP);
	m_objectMgr->GetObject(testObjID)->SetDrawGauge(true);
	m_objectMgr->GetObject(testObjID)->SetTextureID(m_fireAnimTextureID);

	testobjPos.x = -100;
	testobjPos.y = -100;
	testobjPos.z = 0;
	testObjID = m_objectMgr->AddObject(testobjPos, testobjSize, testobjVel, testobjAcc, heroobjMass);
	m_objectMgr->GetObject(testObjID)->SetType(OBJ_TYPE_NORMAL);
	m_objectMgr->GetObject(testObjID)->SetHP(testHP);
	m_objectMgr->GetObject(testObjID)->SetMaxHP(testHP);
	m_objectMgr->GetObject(testObjID)->SetDrawGauge(true);
	m_objectMgr->GetObject(testObjID)->SetTextureID(m_fireAnimTextureID);

	//m_bulletTextureID = -1;
	
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
GSEGame::~GSEGame()
{
	if (m_renderer)
	{
		delete m_renderer;
	}
	if (m_objectMgr)
	{
		delete m_objectMgr;
	}
	if (m_heroTextureID >= 0)
	{
		m_renderer->DeleteTexture(m_heroTextureID);
	}
	if (m_bulletTextureID >= 0)
	{
		m_renderer->DeleteTexture(m_bulletTextureID);
	}
}

void GSEGame::RenderScene()
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
			GSEVec4 color = temp->GetColor();

			if (size.x > 0.0000001f) //float 값이 가질 수 있는 가장 작은 값 넣는 변수 넣기
			{
				int textureID = temp->GetTextureID();
				//m_renderer->DrawSolidRect(pos.x, pos.y, pos.z, size.x, color.x, color.y, color.z, color.w);
				if (textureID < 0)
				{
					m_renderer->DrawSolidRect(
						pos.x, pos.y, pos.z,
						size.x, size.y, size.z,
						color.x, color.y, color.z, color.w);
				}
				else if(textureID == m_fireAnimTextureID)
				{
					float age = temp->GetAge();
					float fps = 60.f;
					int currX = (int)(age * fps )% 10;
					int currY = ((int)(age * fps )/ 10.f);
					
					m_renderer->DrawTextureRectAnim(
						 pos.x, pos.y, pos.z,
						 size.x, size.y, size.z,
						 color.x, color.y, color.z, color.w,
						textureID,
						4,
						3,
						currX,
						currY, false);

				}
				else
				{
					m_renderer->DrawTextureRect(
						pos.x, pos.y, pos.z,
						size.x, size.y, size.z,
						color.x, color.y, color.z, color.w,
						textureID);
				}

			}
			bool bDrawGauge = temp->GetDrawGauge();
			if (bDrawGauge)
			{
				int maxHP = temp->GetMaxHP();
				int HP = temp->GetHP();
				float percent = 100.f*(float)HP / (float)maxHP;
				 m_renderer->DrawSolidRectGauge(
					pos.x, pos.y, pos.z,
					0,size.y/2+1,0,
					size.x, 2,10,
					1,0,0,1,
					(int)percent,false);
			}
		}
	}
}

void GSEGame::UpdateObjects(GSEKeyboardMapper keyMap, float eTime)
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
	bool b_canFire = m_objectMgr->GetObject(m_heroID)->CanFire();
	if ((keyMap.Up_Key || keyMap.Down_Key || keyMap.Left_Key || keyMap.Right_Key) && b_canFire)
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
				m_objectMgr->GetObject(bulletID)->SetParent(m_objectMgr->GetObject(m_heroID));
				m_objectMgr->GetObject(bulletID)->SetHP(200);
				m_objectMgr->GetObject(bulletID)->SetMaxHP(200);
				m_objectMgr->GetObject(bulletID)->SetTextureID(m_bulletTextureID);
				m_objectMgr->GetObject(m_heroID)->ResetCoolTime();
			
			}
		}
	}
	//collision test
	bool testResult[MAX_OBJECT_COUNT];
	memset(testResult, 0, sizeof(bool) * MAX_OBJECT_COUNT);

	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		for (int j = i + 1; j < MAX_OBJECT_COUNT; j++)
		{
			if (m_objectMgr->GetObject(i) == NULL || m_objectMgr->GetObject(j) == NULL)
			{
				continue;
			}

			//get min, max value of object
			GSEVec3 objASize = m_objectMgr->GetObject(i)->GetSize();
			GSEVec3 objAPos = m_objectMgr->GetObject(i)->GetPos();
			GSEVec3 objAMin = {objAPos.x - objASize.x / 2.f, objAPos.y - objASize.y / 2.f, objAPos.z - objASize.z / 2.f};
			GSEVec3 objAMax = {objAPos.x + objASize.x / 2.f, objAPos.y + objASize.y / 2.f, objAPos.z + objASize.z / 2.f};
			GSEVec3 objBSize = m_objectMgr->GetObject(j)->GetSize();
			GSEVec3 objBPos = m_objectMgr->GetObject(j)->GetPos();
			GSEVec3 objBMin = { objBPos.x - objBSize.x / 2.f, objBPos.y - objBSize.y / 2.f, objBPos.z - objBSize.z / 2.f };
			GSEVec3 objBMax = { objBPos.x + objBSize.x / 2.f, objBPos.y + objBSize.y / 2.f, objBPos.z + objBSize.z / 2.f };

			bool isCollide = BBCollision(objAMin, objAMax, objBMin, objBMax);
			bool isParent = m_objectMgr->GetObject(i)->IsAncester(m_objectMgr->GetObject(j)) ||
							m_objectMgr->GetObject(j)->IsAncester(m_objectMgr->GetObject(i));
			if (isCollide && !isParent)
			{
				GSEObject* A1 = m_objectMgr->GetObject(i);
				GSEObject* A2 = m_objectMgr->GetObject(j);
				float m1 = A1->GetMass();
				float m2 = A2->GetMass();
				GSEVec3 vel1 = A1->GetVel();
				GSEVec3 vel2 = A2->GetVel();
				float finalVelX1 = ((m1 - m2) / (m1 + m2)) * vel1.x + ((2.f*m2)/(m1+m2))*vel2.x;
				float finalVelY1 = ((m1 - m2) / (m1 + m2)) * vel1.y + ((2.f*m2)/(m1+m2))*vel2.y;
				float finalVelX2 = ((2.f*m1) / (m1 + m2)) * vel1.x + ((m2-m1) / (m1 + m2)) * vel2.x;
				float finalVelY2 = ((2.f * m1) / (m1 + m2)) * vel1.y + ((m2 - m1) / (m1 + m2)) * vel2.y;
				GSEVec3 temp = { finalVelX1, finalVelY1, vel1.z };
				A1->SetVel(temp); 
				GSEVec3 temp1 = { finalVelX2, finalVelY2, vel2.z };
				A2->SetVel(temp);

				int HP1 = A1->GetHP();
				int HP2 = A2->GetHP();
				A1->SetHP(HP1 - HP2);
				A2->SetHP(HP2 - HP1);

				testResult[i] = true;
				testResult[j] = true;
			}
		}
	}
	for (int i = 0; i < MAX_OBJECT_COUNT; i++) 
	{
		if (m_objectMgr->GetObject(i) != NULL)
		{
			if (testResult[i])
			{
				GSEVec4 colColor = { 1,0,0,1 };
				m_objectMgr->GetObject(i)->SetColor(colColor);
			}
			else
			{
				GSEVec4 colColor = { 1,1,1,1 };
				m_objectMgr->GetObject(i)->SetColor(colColor);
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

bool GSEGame::BBCollision(GSEVec3 minA, GSEVec3 maxA, GSEVec3 minB, GSEVec3 maxB)
{
	if (minA.x > maxB.x)
		return false;
	if (maxA.x < minB.x)
		return false;
	if (minA.y > maxB.y)
		return false;
	if (maxA.y < minB.y)
		return false;
	if (minA.z > maxB.z)
		return false;
	if (maxA.z < minB.z)
		return false;

	return true;
}
