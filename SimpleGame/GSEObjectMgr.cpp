#include "stdafx.h"
#include "GSEObjectMgr.h"
#include <iostream>

GSEObjectMgr::GSEObjectMgr()
{
	//init object list
	for (int i = 0; i < MAX_OBJECT_COUNT; ++i)
	{
		m_objects[i] = NULL;
	}
}

GSEObjectMgr::~GSEObjectMgr()
{
	for (int i = 0; i < MAX_OBJECT_COUNT; ++i)
	{
		DeleteObject(i);
	}
}

int GSEObjectMgr::AddObject(GSEVec3 pos, GSEVec3 size, GSEVec3 vel, GSEVec3 acc, float mass)
{
	//find empty slot
	int index = FindEmptySlot();

	if (index < 0)
	{
		std::cout << "No more empty object slot" << std::endl;
		return -1;
	}

	m_objects[index] = new GSEObject(pos, size, vel, acc, mass);
	return index;
}

GSEObject GSEObjectMgr::GetObject(int index)
{
	GSEVec3 pos = {0,0,0};
	GSEVec3 size = { 0,0,0 };
	GSEVec3 vel = { 0,0,0 };
	GSEVec3 acc = { 0,0,0 };
	float mass = 0;
	GSEObject temp = GSEObject(pos, size, vel, acc, mass);

	if (m_objects[index] != NULL)
		//return m_objects[index];
	{
		memcpy(&temp, m_objects[index], sizeof(GSEObject));
	}
	else
	{
		//log
	}
	//return NULL;
	return temp;
	
}

bool GSEObjectMgr::DeleteObject(int index) //GSO매니저의 소멸자에서만 사용했다
{
	if (m_objects[index])
	{
		delete m_objects[index];
		m_objects[index] = NULL;
		return true;
	}

	return false;
}

int GSEObjectMgr::FindEmptySlot()
{
	for (int i = 0; i < MAX_OBJECT_COUNT; ++i)
	{
		if (m_objects[i] == NULL)
		{
			return i;
		}
	}

	//Fail to find empty slot
	return -1;
}

void GSEObjectMgr::UpdateObjects(float eTime)
{
	for (int i = 0; i < MAX_OBJECT_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			m_objects[i]->Update(eTime);
		}
	}
}

void GSEObjectMgr::AddForce(int index, GSEVec3 force, float eTime)
{
	if (m_objects[index] != NULL)
	{
		m_objects[index]->AddForce(force, eTime);
	}
}
